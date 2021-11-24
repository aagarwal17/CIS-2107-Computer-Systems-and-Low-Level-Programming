//Arun Agarwal
//CIS 2107 Assignment 2: Comment Remover 2/24/2021

#include <stdio.h>
#include <string.h>

//These will be the states I will use
#define OUT 0
#define IN 1
#define MAYBE_IN 2
#define MAYBE_OUT 3
#define IN_QUOTE 4

//As provided in the instructions
#define BUF_SIZE 64


void decomment(FILE *f, FILE *fout);

int main(int argc, char **argv) 
{
    char s[BUF_SIZE];
    char s_out[BUF_SIZE];
    FILE *fp;   //file pointer to keep track of the file being accessed
    FILE *fout; //we are taking the output environment path and passing that to the object of output stream

    /*First, I prompt the user to type in the name of the file to decomment */
    printf("Name of file to decomment: ");
    fgets(s, BUF_SIZE, stdin);  //fgets() reads a line from the specified stream and stores it into the string pointed to by s
    s[strlen(s)-1] = '\0';    //'\0' is used to signify the end of a string. In this case, we are 'appending' the null character.
    //It reads BUF SIZE-1 chars so that there’s space left for the null character. 


    /*Next, I am getting the user to type in the name of the file to output to */
    printf("Name of file to output to: ");
    fgets(s_out, BUF_SIZE, stdin); //same idea as above but for s_out
    s_out[strlen(s_out)-1] = '\0';  //same idea as above but for s_out
    
    /*We now open our file s to read it*/
    fp = fopen(s, "r"); //fopen() is our IO function to do such

    /*We now check to see if the file is actually opened (error checking) */
    if (fp == NULL) 
    {
        fprintf(stderr, "That file could not be found.\n"); //Stderr is the standard error message that is used to print the output on the screen or windows terminal
        fflush(stderr); //Since there was an error, we are using the IO function to clear (or flush) the output buffer
        return 1;
    }

    fflush(stdout); //This releases/flushes the current contents of the output buffer to the system for whatever processing the system has for it. 

    /* We finally open the output file to which we will write to */
    fout = fopen(s_out, "w");
    decomment(fp, fout); //we want our decomment method to decomment fp and write it to fout

    fclose(fp); //we must use the fclose method on fp to delete all buffers associated with the stream before closing it
    fclose(fout); //similar to above with fp

    return 0; //from my understanding, this is something that we just do at the end of main (because our main is a function that is supposed to return an int, so we return 0, identifying success)
}
//Our actual decomment method
void decomment(FILE *fp, FILE *fout) 
{
    int state = OUT;  //Setting the state as out to begin
	int current;    //variable we will use for current character
	int temp;       //a temp used to store the current character when we are put into "Maybe" states
	int lines = 0;  //a count for the number of lines, necessary to output the line number of the error
	int lineError = 0;

    //While we are not at the end of the file (EOF):
    //(Overall, we will be outputting characters to our output file if we are IN_QUOTE or OUT states)  
    while ((current = fgetc(fp)) != EOF) 
    {
        //If the current state is out of a comment and the current character is a /, then we may be in a comment
        if (state == OUT && current=='/')
        {
            state = MAYBE_IN;
            temp = current;
        }
        
        //else if you are in the out state and the current character is \" or \', you are in a quote!
        else if (state == OUT && current =='\"' || current == '\'')
        {
            fputc(current, fout);
            state = IN_QUOTE;
            lineError = lines; //lineError will occur at whatever the current line is
        }
        
        //else if you are in the out state, you are not in a comment, so just put the character to the output file
        else if(state == OUT)
        {
            fputc(current, fout);
        }
        
        //else if you are maybe in a comment and the current character is a star, that means you are in a comment!
        else if(state == MAYBE_IN && current == '*')
        {
            state = IN;
            lineError = lines; //lineError will occur at whatever the current line is
        }
        
        //else if you are maybe in a comment and the current character is a slash in quotes, then continue to put the char to the output file and change the state to in quote
        else if(state == MAYBE_IN && current=='\"' || current=='\'')
        {
            fputc(temp, fout); //because we were actually in a quote, we put the previously stored temp into the output file
            fputc(current, fout);
            state = IN_QUOTE;
            lineError = lines; //lineError will occur at whatever the current line is
        }
        
        //else if we are in the MAYBE_IN state but the current character is not an asterik or we are not in quotes, then we are not in a comment
        else if(state == MAYBE_IN)
        {
            fputc(temp, fout); //similar reasoning to the last else if block, because we were never in a comment, we need to output the previously stored temp to the output file
            fputc(current, fout);
            state = OUT; //Since we now confirmed we are not in comment, we update the state to out
        }
        
        //else if we are currently in comment and the current character is an asterik, we might be going out of state, so we change the state
        else if(state == IN && current == '*')
        {
            state = MAYBE_OUT;
            lineError = lines; //lineError will occur at whatever the current line is
        }
        
        //this needed to be added for some errors. Basically if the state is in but none of the other conditions is meant, don't output anything to the output file and don't change the state
        else if(state == IN)
        {;}

        //else if the state is maybe out of the comment and the current character is /, then we are going out of a comment
        else if(state == MAYBE_OUT && current =='/')
        {
            state = OUT;
        }
        
        //else if the state is maybe out of the comment but the next character was not the slash (/), that means we are still in the comment, and change the state back to IN
        else if(state == MAYBE_OUT)
        {
            state = IN;
        }
        
        //else if the state is in a quote and the current character is a \ followed by a single quote or double quote, we are then leaving the quote so we change the state to out of comment
        else if(state == IN_QUOTE && current =='\"' || current == '\'')
        {
            fputc(current, fout);
            state = OUT;
        }
        
        //else if we are still in the quote, we continue to output characters to the output file
        else if(state == IN_QUOTE)
        {
            fputc(current, fout);
        }

        //this if statement is keeping track of the line count. Whenever it encounters the \n or new line character, the lines variable is incremented by 1
        if(current == '\n')
        {
            lines++;
        }
    } 

    fflush(fout);

    //Error Handling with line numbers:

    //If we are currently in a comment, the error is the comment was not properly closed
    if(state == IN)
    {
        printf("You did not correctly close a comment on line %d\n", lineError);
    }

    //If we are currently in a quote, the error is there was no terminating quotation mark
    else if(state == IN_QUOTE)
    {
        printf("There was no second/closing/terminating quotation mark found on line %d\n", lineError);
    }

    //Otherwise, there should be no errors with our program, so we print that the program decommented succesfully
    else
    {
        printf("Congratulations! The program has been decommented successfully.\n");
    }

}