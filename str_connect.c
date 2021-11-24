#include <stdlib.h>
#include <stdio.h>

/**********************************************************************
char *str_connect(char **strs, int n, char c)

Returns a string consisting of the first n strings in strs with the
character c used as a separator. For example, if strs contains the
strings {"Washington", "Adams", "Jefferson"}, n is 3, and c is '+',
the function returns the string "Washington+Adams+Jefferson"
**********************************************************************/
char *str_connect(char **strs, int n, char c) {
  char *temp;
  int i;

  /*Iterate and calculate length of each string in the array*/
  //for ()

  // For now, I'm being lazy and allocating an arbitrary amount of
  // space that's big enough.
  char *ret_str = (char *) malloc(1000);
  char *actual_ret = ret_str;

  /* Iterate through each string in strs array */
  for (i = 0; i < n; i++){
    temp = strs[i]; // for i = 0 temp is "Washington" in the example
    int j;
    int len = str_len(temp);
    
    for (j = 0; j < len; j++) {
      *ret_str = *temp;
      ret_str++;
      temp++;
    }
    
    if (i != n-1) {
      *ret_str = c;
      ret_str++;
    }
  }

  *ret_str = '\0';

  return actual_ret;
}

/**********************************************************************
NOTE: Only the str_connect function should be defined in this file
      when you submit it. You should have another file for str_len
      (str_len.c), and your testing of this function should occur in
      your C program that you wrote to test all of your functions in
      your string lbrary. Also, you should include a declaration for
      str_connect (and all other functions in your string library) in
      your library's header file.
**********************************************************************/
int str_len(char *s)
{
   char *t=s;

   while (*t!='\0')
      t++;
   return t-s;
}

int main(void) {
  char *s[3] = {"Washington", "Adams", "Jefferson"};
  char *str = str_connect(s, 3, '+');

  printf("%s\n", str);
}
