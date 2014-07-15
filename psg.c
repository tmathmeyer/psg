#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
			printf("%s ", ll -> text);
			printf("\e[38;5;%im", ll -> colors.bg);
			if (ll -> next != NULL && is_non_null_color(ll -> next -> colors)) {
				printf("\e[48;5;%im", ll -> next -> colors.bg);
			} else {
				printf("\e[48;5;%im", TERM_BG);
			}
			printf("⮀ ");
		}
		ll = ll -> next;
	}
}

ps1 * git_module(FILE * fp) {
	
}

ps1 * gen_from_config() {
	FILE * fp = fopen("/home/ted/.config/psg/psgrc", "r");
	if (fp == NULL) {
		perror("kek");
		return NULL;
	}

	char * strrd = malloc(100);
	while(fgets(strrd, 100, fp)) {
		puts(strrd);
		int fg, bg;
		fscanf(fp, "%i\n%i", &fg, &bg);
	}

	return NULL;
	
}

int main() {
	ps1 * a = malloc(sizeof(ps1));
	ps1 * b = malloc(sizeof(ps1));
	ps1 * c = malloc(sizeof(ps1));

	a -> next = b;
	b -> next = c;
	c -> next = NULL;

	colorinfo x = {15, 1};
	colorinfo y = {64, 67};
	colorinfo z = {33, 77};

	a -> colors = x;
	b -> colors = y;
	c -> colors = z;

	a -> text = "ted";
	b -> text = "is";
	c -> text = "the best";

	echo_ps1(a);
	gen_from_config();

	return 0;
}