#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define TERM_BG 0

typedef struct {
	unsigned char fg;
	unsigned char bg;
} colorinfo;

typedef struct ps1 {
	colorinfo colors;
	char * text;
	struct ps1 * next;
} ps1;

bool is_non_null_color(colorinfo info) {
	return info.fg | info.bg;
}

void echo_ps1 (ps1 * ll) {
	while(ll != NULL) {
		if (ll -> text != NULL) {
			if (is_non_null_color(ll -> colors)) {
				printf("\e[38;5;%im", ll -> colors.fg);
				printf("\e[48;5;%im", ll -> colors.bg);
			}
			printf(" %s \e[21m", ll -> text);
			printf("\e[38;5;%im", ll -> colors.bg);
			if (ll -> next != NULL && is_non_null_color(ll -> next -> colors)) {
				printf("\e[48;5;%im", ll -> next -> colors.bg);
			} else {
				printf("\e[48;5;%im", TERM_BG);
			}
			printf("⮀");
		}
		ll = ll -> next;
	}
	printf("\e[0m");
}

char * git_module() {
	FILE * git_info = popen("/bin/bash /home/ted/.config/psg/git.sh", "r");
	if (git_info == NULL) {
		return NULL;
	}

	char * branch = malloc(64);
	int pos = 0; char c = 0;
	while((c = fgetc(git_info)) != '\n' && pos < 64) {
		if (c != '\\') {
			branch[pos++] = c;
		} else {
			char n = fgetc(git_info);
			if (n == 'e') {
				branch[pos++] = '\e';
			}
		}
	}
	fclose(git_info);

	return branch;
}

char * cwd_module() {
	char * cwd = malloc(1024);
    if (getcwd(cwd, 1024) != NULL) {
    	char * home = getenv("HOME");
    	int home_len = strlen(home);
    	char * pos = strstr(cwd, home);
    	if (pos == NULL) {
    		return cwd;
    	} else {
    		cwd += home_len-1;
    		cwd[0] = '~';
    		return cwd;
    	}
    }
    return NULL;
}

char * userhost_module() {
	char * user = getenv("USER");
	char * host = malloc(64);
	gethostname(host, 64);

	char * result = malloc(1024);
	memset(result, 0, 1024);
	snprintf(result, 1024, "\e[1m%s@%s", user, host);
	return result;
}

ps1 * reverse_list (ps1 * n) {
	ps1 * res = 0;
	while(n) {
		ps1 * tmp = n -> next;
		n -> next = res;
		res = n;
		n = tmp;
	}
	return res;
}

ps1 * gen_from_config() {
	FILE * fp = fopen("/home/ted/.config/psg/psgrc", "r");
	if (fp == NULL) {
		return NULL;
	}

	ps1 * result = NULL;

	char * strrd = malloc(64);
	int fg, bg;
	while(fscanf(fp, "%s\n%i\n%i\n\n", strrd, &fg, &bg) > 0) {
		ps1 * z = malloc(sizeof(ps1));
		if (strncmp (strrd, "$git", 4) == 0) {
			z -> text = git_module();
		}

		if (strncmp (strrd, "$userhost", 9) == 0) {
			z -> text = userhost_module();
		}

		if (strncmp (strrd, "$path", 5) == 0) {
			z -> text = cwd_module();
		}

		z -> next = result;
		z -> colors.fg = fg;
		z -> colors.bg = bg;

		result = z;
	}
	free(strrd);

	return reverse_list(result);
	
}



int main() {

	echo_ps1(gen_from_config());

	return 0;
}