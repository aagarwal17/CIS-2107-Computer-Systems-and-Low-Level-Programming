/* rmcmt.c Mark Dolan, CIS 2107, Comment Remover 091614 */

#include <stdio.h>

#define OUT 0
#define IN 1
#define MAYBE_IN 2
#define MAYBE_OUT 3
#define IN_QUOTE 4

int main(int argc, char **argv) {
	int state=OUT;
	int cur;
	int temp;
	int lines = 0;
	int lineError = 0;
  
while ((cur=getchar())!=EOF) {
	if (state == OUT && cur=='/'){
		state = MAYBE_IN;
		temp = cur;
	}else if (state == OUT && cur =='\"' || cur == '\'') {
		putchar(cur);
		state = IN_QUOTE;
		lineError = lines;
	}else if(state == OUT){
	putchar(cur);
	}else if(state == MAYBE_IN && cur == '*'){
		state = IN;
		lineError = lines;
	}else if(state == MAYBE_IN && cur=='\"' || cur=='\''){
		putchar(temp);
		putchar(cur);
		state = IN_QUOTE;
		lineError = lines;
	}else if(state == MAYBE_IN){
		putchar(temp);
		putchar(cur);
		state = OUT;
	}else if(state == IN && cur == '*'){
		state = MAYBE_OUT;
		lineError = lines;
	}else if(state == IN){;
	}
	else if(state == MAYBE_OUT && cur=='/'){
		state = OUT;
	}else if(state == MAYBE_OUT){
		state = IN;
	}else if(state == IN_QUOTE && cur=='\"' || cur == '\''){
		putchar(cur);
		state = OUT;
	}else if(state == IN_QUOTE){
		putchar(cur);
	}

	if(cur == '\n'){
		lines++;
	}
}//End While

if(state == IN){
	printf("A comment was not properly closed on line %d\n", lineError);
	return 1;
}else if(state == IN_QUOTE){
	printf("No terminating quotation mark found on line %d\n", lineError);
	return 1;
}else{
	printf("program decommented successfully\n");
	return 0;
}

}//End Main
