// This program counts the number of characters, words and lines
// This program is based on the counting program in 'The C Programming Lang
// -uage.
#include<stdio.h>

int main() {

	int c, line, word, ch;

    line = word = ch = 0;

    while((c = getchar()) != EOF) {
        ch++;
        if (c == ' ' || c == '\t')
            word++;
        else if (c == '\n') {
            word++;
            line++;
        }
    }

    printf("characters: %d\nwords: %d\nline: %d\n", ch, word, line);

	return 0;

}
