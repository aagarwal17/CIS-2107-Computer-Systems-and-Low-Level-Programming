#include <stdio.h>

unsigned int add(unsigned int, unsigned int);
unsigned int sub(unsigned int, unsigned int);
unsigned int mul(unsigned int, unsigned int);
unsigned int lt(unsigned int, unsigned int);
unsigned int gt(unsigned int, unsigned int);
unsigned int getByte(unsigned int, unsigned int);

int main(int argc, char **argv)
{

 unsigned int i, j;

 printf("Enter an integer ");

 scanf("%u", &i);
 printf("\nEnter another integer ");
 scanf("%u", &j);
 printf("\ni + j = %u\n", add(i,j));
 printf("\ni - j = %u\n", sub(i,j));
 printf("\ni * j = %u\n", mul(i,j));
 printf("i > j = %s\n", (gt(i,j) ? "TRUE" : "FALSE"));
 printf("i < j = %s\n", (lt(i,j) ? "TRUE" : "FALSE"));
 printf("jth byte of i = %ux\n", getByte(i,j));

 return 0;
}

unsigned int add(unsigned int i, unsigned int j)
{
    /* can be done in a total of 7 lines, including one to declare an unsigned int, */
    /* two for a while loop, and one for the return */
    unsigned int c;
    while (j != 0)
    {
        c = i & j; //c contains common
        i = i ^ j; //Sum of bits of i and j but at least one is not set
        j = c << 1; // c is shifted to give required sum
    }
    return i;
}

unsigned int sub(unsigned int i, unsigned int j)
{
    /* Similar 7 lines, although there is a shorter way */
    unsigned int b;
    while (j != 0)
    {
        b = (~i) & j; // b contains common of ~i and j
        i = i ^ j; // subtraction of bits but at least one is not set
        j = b << 1; // b is shifted to give required subtration
    }
    return i;
}

unsigned int mul(unsigned int i, unsigned int j)
{
    /* can be done in a total of 8 lines including one to declare unsigned ints */
    /* two for a for loop, and one for the return */
    unsigned int res = 0;
    unsigned int t = 1;
    for (t; t <= j; t=add(t, 1))
    {
        res = add(res, i); //we are just adding our number i 'j' times, because that is really what multiplication is
    }
    return res;
}

/* returns non-zero if i is less than j or zero otherwise */
unsigned int lt(unsigned int i, unsigned int j)
{
    /*unsigned int t = j ^ ((i ^ j) & -(i < j)); //this will product either i or j
    if (t == i) //if t is equal to i, that means i is less than j
        return 1;
    else //if t does not equal i, that means it equals j and j is either equal to i or less than i
        return 0;*/

    if (i == j)
    {
        return 0; //they are the same number, so we just return 0
    }

    while (i != 0 && j!= 0) //if they are both nonzero, then...
    {
        i = sub(i,1);
        j = sub(j,1);
    }

    if (i == 0 & j != 0) //bitwise operation
    {
        return 1; //since we are going by bit by bit, with the most significant digit first, if it comes across i equaling 0 when j equals 1, that means j is a larger number, or i < j
    }

    else
    {
        return 0; //otherwise, i > j so return 0
    }
    
}

/* returns non-zero if i is greater than j or zero otherwise */
unsigned int gt(unsigned int i, unsigned int j)
{
    /*unsigned int t = j ^ ((i ^ j) & -(i < j)); //same thing as the previous function, t will either be i or j
    if (t == j) //now, we want t to be equal to j to result in j being less than i (or i to be greater than j)
        return 1;
    else //otherwise, t equals i and i is either less than j or equal to j
        return 0;*/

    if (i == j)
    {
        return 0; //they are the same number, so we just return 0
    }

    while (i != 0 && j!= 0) //if they are both nonzero, then...
    {
        i = sub(i,1);
        j = sub(j,1);
    }

    if (i != 0 & j == 0) //bitwise operation
    {
        return 1; //since we are going by bit by bit, with the most significant digit first, if it comes across i equaling 1 when j equals 0, that means i is a larger number, or i > j
    }

    else
    {
        return 0; //otherwise, i < j so return 0
    }

    
}

/* returns the jth byte of i */
unsigned int getByte(unsigned int i, unsigned int j)
{
    //from right to left
    //we do the bit shift once the byte is in the best position
    //we take the original integer & binary/hexadecimal
    unsigned int y = (i >> (mul(8,sub(j,1)))) & 0xff; //maybe supposed to be &255
    return y;
}