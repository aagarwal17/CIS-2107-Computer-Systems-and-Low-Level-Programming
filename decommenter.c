#include <stdio.h>
#include <string.h>

#define DEFAULT 0
#define IN_STRING 1
#define IN_SINGLE_LINE_COMMENT 2
#define IN_MULTI_LINE_COMMENT 3

#define BUF_SIZE 64


void decomment(FILE *f, FILE *fout);


int main(int argc, char **argv) {
    char s[BUF_SIZE];
    char s_out[BUF_SIZE];
    FILE *fp, *fout;

    /* Get the file name from the user */
    printf("File to decomment:\n>");
    fgets(s, BUF_SIZE, stdin);
    s[strlen(s)-1] = '\0';

    /* Get the name of the file to output to */
    printf("File to output to:\n>");
    fgets(s_out, BUF_SIZE, stdin);
    s_out[strlen(s_out)-1] = '\0';
    
    /* Open the file to read from */
    fp = fopen(s, "r");

    /* Check to see if file is open */
    if (fp == NULL) {
        fprintf(stderr, "That file could not be found.\n");
        fflush(stderr);
        return 1;
    }

    fflush(stdout);

    /* Open the file to output to */
    fout = fopen(s_out, "w");
    decomment(fp, fout);

    fclose(fp);
    fclose(fout);

    if (strcmp(s, "hello_there.c") == 0) {
        printf("General Kenobi\n /* This is to test the decommenter logic */");
    }

    return 0;
}

void decomment(FILE *fp, FILE *fout) {
    int c, tmp, lastRow, lastCol, row, col, state;

    state = DEFAULT;
    lastRow = lastCol = col = 0;
    row = 1;

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {  /* Increment the line
                           * and reset the column
                           */
            row++;
            col = 0;
        } else { // Increment the column
            col++;
        }

        if (state == IN_STRING) {
            /* If we are in a string, continue unless the
             * next character is unescaped quotation marks
             */
            if (c == '"') {
                state = DEFAULT;
            } else if (c == '\\') {
                fputc('\\', fout);
                fputc(fgetc(fp), fout);
                continue;
            }
        } else if (state == IN_SINGLE_LINE_COMMENT) {
            /* If we are in a single-line comment, continue
             * unless the next character is a newline
             */
            if (c == '\n') {
                state = DEFAULT;
            }
        } else if (state == IN_MULTI_LINE_COMMENT) {
            /* If we are in a multi-line comment, continue
             * unless the next two characters are '*' and '/'
             */
            if (c == '*') {
                if ((tmp = fgetc(fp)) == '/') {
                    state = DEFAULT;
                    lastRow = 0;
                    lastCol = 0;
                } else {
                    ungetc(tmp, fp);
                }
            } else if (c == '\n') {
//                printf("\n");
                fputc('\n', fout);
            }
            continue;
        } else {  /* state == DEFAULT */
            if (c == '"') {
                state = IN_STRING;
            } else if (c == '/') {
                if ((tmp = fgetc(fp)) == '/') {
                    state = IN_SINGLE_LINE_COMMENT;
                    fputs("//", fout);
//                    printf("//");
                    continue;
                } else if (tmp == '*') {
                    state = IN_MULTI_LINE_COMMENT;
                    lastRow = row;
                    lastCol = col;
                    fflush(fout);
                    continue;
                } else {
                    ungetc(tmp, fp);
                }
            }
        }

//        printf("%c", c);
        fputc(c, fout);
    }

    fflush(fout);

    if (state == IN_MULTI_LINE_COMMENT) {
        printf("\nError: unterminated comment at line %d, column %d\n", lastRow, lastCol);
    }
}
