#include<stdio.h>
#include <stdlib.h>
#include<stdlib.h>
#include <time.h>

void radixSort(int * array, int * b, int * c ,int size, int large)
{
  int i;
  int *semiSorted,*bsort,*csort;
  
  semiSorted =(int*) calloc ( 2*size,sizeof(int));
  bsort=(int*) calloc ( 2*size,sizeof(int));
  csort=(int*) calloc ( 2*size,sizeof(int));
  int significantDigit = 1;
  int largestNum = large;
  
  // Loop until we reach the largest significant digit
  while (largestNum / significantDigit > 0)
  {
    
    int bucket[10] = { 0 };
    
    // Counts the number of "keys" or digits that will go into each bucket
    for (i = 0; i < size; i++)
      bucket[(array[i] / significantDigit) % 10]++;
    
    /*
     * Add the count of the previous buckets,
     * Acquires the indexes after the end of each bucket location in the array
		 * Works similar to the count sort algorithm
     */
    for (i = 1; i < 10; i++)
	{
      bucket[i] += bucket[i - 1];}
    // Use the bucket to fill a "semiSorted" array
    for (i = size - 1; i >= 0; i--)
	{ int l = --bucket[(array[i] / significantDigit) % 10];
	  semiSorted[l] = array[i];
      bsort[l]=b[i];
	  csort[l]=c[i];
	
    }
	
	for (i = 0; i < size; i++)
    {array[i] = semiSorted[i];
      b[i] = bsort[i];
      c[i] = csort[i];
    }
    // Move to next significant digit
    significantDigit *= 10;
	
	
	}
	free(semiSorted);
	free(bsort);
    free(csort);
}

void main(int argc, char *argv[])
{ char *inFileString, *outFileString;
  time_t seconds,seconds1;
  seconds = time(NULL); 
  FILE*infile;
  int i=0,n,m;
  inFileString = argv[1];
  outFileString = argv[2];
  infile=fopen(inFileString,"r");
    if (infile == NULL) {
        fprintf(stderr, "Error! Could not open file.\n");
    }
    fscanf(infile,"%d",&n);
	printf("%d \n",n);
	fscanf(infile,"%d",&m);
	printf("%d \n",m);
	int *a,*b,*c,*stack,*track,*t;
	a = (int*) calloc ( 2*n,sizeof(int));
	b = (int*) calloc ( 2*n,sizeof(int));
	c = (int*) calloc ( 2*n,sizeof(int));
	stack = (int*) calloc ( n,sizeof(int));
	track = (int*) calloc ( n,sizeof(int));
    while (i<2*n) 
	{       fscanf(infile,"%d",&a[i]);
			i++;}
	fclose(infile);
	
	for (i=0;i<2*n;i++) // Assign alternating 0’s and 1’s to array B[2n]
    {if (i%2==0) b[i]=0;
    else b[i]=1;}
	int j=1;
	
	for (i=0;i<2*n;i=i+2)// Put the interval number corresponding to the endpoints in array C[2n]
      {c[i]=j;
       c[i+1]=c[i];
       j=j+1;}

    stack[0]=n; // Initialize a stack using array with 1 to n track numbers from right to left.
    for (i=1;i<n;i++)
      stack[i]=stack[i-1]-1;

  int mintop=0;  
  //Sorting
  radixSort(b, a , c , 2*n , 1);
  radixSort(a, b , c , 2*n , m);
  // Stack
	int top = n-1;
	
	for(i=0;i<2*n;i++)
	  {   if (b[i]==0)
	    { track[c[i]]=stack[top];	
	     top=top-1;}
	    
		if (b[i]==1)
	    { top=top+1;
	      stack[top]=track[c[i]];}
	   }
	  
	   free(stack);
	   free(b);
	
	t = (int*) calloc ( 2*n,sizeof(int));
	for(i=0; i<2*n; i++)
	{ t[i]=track[c[i]];
	}
	radixSort(t, a , c , 2*n , n+1);
	
	mintop=t[2*n-1];
	printf("%d \n",mintop); 
   //writing back to the file	
	FILE*fp1;
    fp1 =fopen(outFileString, "w+");
    i=1;
    fprintf(fp1,"%s%d","T",i);
    free(c);
	free(track);
	for(i=0;i<((2*n)-1);i++)
	{ fprintf(fp1, " %ld",a[i]);
	
	  if (t[i]!=t[i+1])
	     fprintf(fp1, "\n%s%ld","T",t[i+1]);}
		 
	fprintf(fp1," %ld",a[2*n-1]);
	fclose(fp1);
	free(a);
	free(t);
	seconds1 = time(NULL);
	printf("%ld \n",seconds);
	printf("%ld \n",seconds1);
	printf("%ld \n",seconds1-seconds);
	}