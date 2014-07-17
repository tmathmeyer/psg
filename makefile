all:
	gcc -Wall psg.c -o psg

install: all
	cp psg /usr/local/bin/psg

clean:
	rm psg
