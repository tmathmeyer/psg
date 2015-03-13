all: psg demo

psg:
	gcc -Wextra -Wall psg.c -o psg

demo:
	gcc -Wextra -Wall colors.c -o colors

install: all
	cp psg /usr/local/bin/psg

clean:
	rm psg colors
