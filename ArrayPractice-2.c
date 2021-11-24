//Arun Agarwal CIS 2107 Assignment 1 Code
#include <stdio.h>

#define LEN_A 10

/* function declarations */
void print_array(int[], int);
void reverse(int[], int);
double average(int[], int);
void insert(int[], int, int, int);
int less_than_average(int[], int);
void rotate_right(int[], int, int);
void array_copy(int[], int[], int);
void initialize(int[], int, int);
void evens_on_left(int[], int);
int find(int A[], int len, int x);
int find_last(int A[], int len, int x);
int contains_dup(int A[], int len);

int main(int argc, char **argv)
{
  int A[] = {9, 505, 321, 117, 27, 64, 13, 9, 12, 208};
  int B[LEN_A+1];
  int newValue=505;

  printf("A[] is:\n");
  print_array(A, LEN_A);

  initialize(B, LEN_A+1, 0);
  printf("B[] is:\n");
  print_array(B, LEN_A+1);

  array_copy(B, A, LEN_A);
  printf("but now it's\n");
  print_array(B, LEN_A+1);

  insert(B, newValue, 0, LEN_A);
  printf("and after inserting %d at the beginning it's\n", newValue);
  print_array(B, LEN_A+1);

  printf("The average of A[] is %f\n", average(A,LEN_A));
  printf("There are %d items in A[] less than this.\n", less_than_average(A,LEN_A));

  reverse(A, LEN_A);
  print_array(A, LEN_A);

  rotate_right(A, LEN_A, 3);
  print_array(A, LEN_A);

  evens_on_left(A, LEN_A);
  print_array(A, LEN_A);

  printf("The index of the first occurrence of %d is %d.\n", 9, find(A, LEN_A, 9));
  printf("The index of the last occurrence of %d is %d.\n", 9, find_last(A, LEN_A, 9));

  if (contains_dup(A, LEN_A))
    printf("A[] contains a dup\n");
  else
    printf("A[] doesn't contain a dup\n");

  if (contains_dup(B, LEN_A+1))
    printf("B[] contains a dup\n");
  else
    printf("B[] doesn't contain a dup\n");

  return 0;
}

/* functions implementation */

/* prints A[] inside parentheses with each value separated
   by commas to stdout (which will be the screen). */
void print_array(int A[], int length) 
{
  int i;
  printf("(");

  //the for loop prints out each element of the array
  for(i=0; i<length; i++)
  {
    if(i != (length - 1))
    {
      printf("%d, ", A[i]);
    }

    //when we reach the last element, we need to also print a closing parenthesis
    else
    {
      printf("%d)\n", A[i]);
    }
  }
}

/* returns the average of the items in A[] or 0.0 if A is empty */
double average(int A[], int length) 
{
  /* for now return 1.0 as a placeholder.  We do this just so that the program
     compiles without warning until we've finished */
  int i;
  double total;
  double average;
  
  if(length == 0)
  {
    return 0.0;
  }
  //this for loop sums the elements in the array A so that the average can be computed later
  for (i = 0; i < length; i++)
  {
    total += A[i];
  }

  average = (total/length);
  return average;
}

/* returns the number of items in A that are less than the
   average of the items in A */
int less_than_average(int A[], int length) 
{
  /* for now return 0 as a placeholder.  We do this just so that the program
     compiles without warning until we've finished */

  //calling the average method written to determine the average of A
  double averageOfArray = average(A, length);
  int i;
  int belowAverage = 0;
  //iterating through the elements of the array A, and if the element has a value smaller than the value for the average of the array (averageOfArray), then we increase the count of belowAverage
  for (i = 0; i < length; i++)
  {
    if (A[i] < averageOfArray)
    {
      belowAverage++;
    }
  }
  return belowAverage;
}

/* Reverses the values in A[].  For example, if before the function,
   A[] contained [1,2,3,4,5], after the function, A[] contains
   [5,4,3,2,1] */
void reverse(int A[], int length) 
{
  int reversedArray[length];
  int i;
  int j = 0;

  //common way to reverse an array is to start from the end and iterate through
  for (i = length - 1; i >= 0; i--)
  {
    reversedArray[j] = A[i];
    j++;
  }
  array_copy(A, reversedArray, length);
  //print_array(A, length);
}

/* returns the second largest item in A[], or -1 if len < 2 */
int secondLargest(int A[], int length) 
{
  /* for now return 0 as a placeholder.  We do this just so that the program
     compiles without warning until we've finished */
  int i;
  double max = A[0] - 1;
  int j;
  int secondBiggest = A[0] - 1;

  //as desired, the method will return -1 if the length of the array is less than two
  if (length < 2)
  {
    return -1;
  }
  //starting from the second element in the array A, iterate through and if the element is greater than the max, set that value as the max and j as the index of where the max value is
  for (i = 1; i < length; i++)
  {
    if(A[i] > max)
    {
      max = A[i];
      j = i;
    }
  }

  //starting from the first element in the array A, iterate through and if the element is not the max but is greater than the value set for secondBiggest, update the secondBiggest value
  for (i = 0; i < length; i++)
  {
    if (A[i] != max)
    {
      if(A[i] > secondBiggest)
      {
        secondBiggest = A[i];
      }
    }
  }
  return secondBiggest;
}

/* rotates the values in the array numPlaces to the right */
/* for example, if A[] is initially 10,20,30,40,50, and numPlaces=2 */
/* after the function finishes, A[] would be 40,50,10,20,30 */
void rotate_right(int A[], int length, int numPlaces) 
{
  /*int rotatedArray[length];
  int i;

  array_copy(rotatedArray, A, length);

  //Using mod function to wrap around and get correct indicies for rotation
  for (i = numPlaces; i < (length + numPlaces); i++)
  {
    A[i % length] = rotatedArray[i - numPlaces];
  }
}
*/
  int l = 0;
  int i;
  int temp = 0;

  //while loop runs for each number of spaces the values need to rotate
  while(l<numPlaces)
  {
    l++;
    
  //I am copying the value of the last element so that its data is not lost
    temp=A[length-1];

  //Run through the loop starting at the last element and pull each element to the right by one
    for(i=length;i>0;i--)
    {
      A[i]=A[i-1];
    }
      
  //Set the first element equal the the temp which holds the last element that was overwritten
      A[0]=temp;
  }
}
/* inserts the value n in A[] at the given index and shifts
   all other values up one position.  A[] contains length items.

   It is up to the caller to make sure that there is enough space
   in A[] to accomodate the new item, and that the index is valid. */
void insert(int A[], int n, int index, int length) 
{
  int i;
  int newArray[length];
  
  //calling one of our methods to make a copy of the values in A and place them in the created temp array newArray
  array_copy(newArray, A, length);

  //starting at the desired index (specified with the parameter 'index'), we set the value at the next index of A as the value of the index in newArray
  for (i = index; i < length; i++)
  {
    A[i+1] = newArray[i];
  }
  //with the values shifted, n can be added at index 'index' in A
  A[index] = n;
}

/* copies the first numItems from S to D. */
void array_copy(int D[], int S[], int numItems) 
{
  int i;

  //self explanatory: copies the first numItems from S into D
  for (i = 0; i < numItems; i++)
  {
    D[i] = S[i];
  }
}

/* sets the first len elements of A to initialValue */
void initialize(int A[], int len, int initialValue) 
{
  int i;

  //self explanatory: sets the first 'len' items of A to initialValue
  for (i = 0; i < len; i++)
  {
    A[i] = initialValue;
  }
}

/* shuffles the values in A so that the even values
   are all to the left of the odd values */
void evens_on_left(int A[], int len) 
{
  /*int evens[len];
  int odds[len];
  int i;
  int even = 0;
  int odd = 0;
  int numberEven = 0;
  int numberOdd = 0;

  //if the number mod 2 equals 0, it is even, so we add to even array. If not, we add to odd array
  for (i = 0; i < len + 1; i++)
  {
    if (A[i] % 2 == 0)
    {
      evens[even] = A[i];
      even++;
    }
    else
    {
      odds[odd] = A[i];
      odd++;
    }
  }
  //we first set the even values in array A, then the odd values
  for (i = 0; i < len + 1; i++)
  {
    if (i <= even)
    {
      A[i] = evens[numberEven];
      numberEven++;
    }
    else
    {
      A[i] = odds[numberOdd];
      numberOdd++;
    }
  }*/

  int i;
  int j;
  int C[len];
  j=0;

    //Running through the entire array and copying over the even numbers to a new array C[]
    for(i=0; i<len; i++) 
    {
      
      if(A[i]%2 == 0)
      {
        C[j] = A[i];
        j++;
      }
    }

    //Running through the entire array again and copying over the odd numbers to the array C[]
    for(i=0; i<len; i++)
    {
      if(A[i]%2 != 0)
      {
        C[j] = A[i];
        j++;
      }
    }

    //Calling our copy method to copy the elements from C into A up to length len:
    array_copy(A,C,len);
}  

/* returns the index of the first occurrence of
 * x in A[] or -1 if x doesn't exist in A[] */
int find(int A[], int len, int x) 
{
  int i;

  //as we iterate through the array A, if the value at a certain index matches with x, then return that index
  for (i = 0; i < len; i++)
  {
    if (A[i] == x)
    {
      return i;
    }
  }
  return -1;
}

/* returns the index of the last occurrence of
 * x in A[] or -1 if x doesn't exist in A[] */
int find_last(int A[], int len, int x) 
{
  int i;
  int j;
  int noneFoundIndex = 0;

  //as we iterate through array A, if we find the value x in it, we let j equal the index i
  //if the value is not found, the value of noneFoundIndex is increased
  for (i = 0; i < len; i++)
  {
    if(A[i] == x)
    {
      j = i;
    }
    else
    {
      noneFoundIndex++;
    }
  }

  //if it goes through this loop, that means x did not exist in the array and we return -1
  if (noneFoundIndex == len)
  {
    return -1;
  }  
  return j;
}

/* returns 1 if there is at least one element in A[]
   that is contained elsewhere in A[], or 0 if there isn't */
int contains_dup(int A[], int len) 
{
  int i;
  int j;
  int m;

  //we need a double for loop so that we can compare each element in the array to every other element in the array
  for (i = 0; i < len; i++)
  {
    for (j = 0; j < len; j++)
    {
      if (j != i)
      {
        if (A[i] == A[j])
        {
          return 1;
        }
      }
    }
  }
  return 0;
}
