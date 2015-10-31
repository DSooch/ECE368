#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "sorting.h"

long * Load_File (char * filename, int * Size)
{
	long int N;
	long int count, currentNum;

	FILE * fp = fopen(filename, "r");
	//saves elements into an array from the file, starting with the size of the array
	fscanf(fp, "%ld", &N);
	long int * list = malloc((N) * sizeof(long int));

	for(count = 0; fscanf(fp, "%ld", &currentNum) == 1; ++count)
	{
		list[count] = currentNum;
	}

	fclose(fp);

	*Size = N;
	return(list);
}

int Save_File (char * filename, long * array, int Size)
{
	int count, saved;

	FILE * fp = fopen(filename, "w");
	//writes contents of array into file, starting with the size of the array
	for(count = 0, saved = 0; count <= Size; ++count)
	{
		if (count == 0)
		{
			fprintf(fp, "%d\n", Size);
		} else if(!feof(fp))
		{
			fprintf(fp, "%ld\n", array[count - 1]);
			++saved;			
		}
	}

	fclose(fp);
	return(saved);
}

void Shell_Insertion_Sort (long * array, int Size, double * NComp, double * NMove)
{
	long * sequence = malloc(Size * sizeof(long));
	long length, p, q, index, indexFront, indexRear;
	long temp;

	//make sequence 1
	for (p = 0, q = 0, index = 0; pow(2,p) < Size; ++p)
	{
		for (q = 0; pow(2,p)*pow(3,q) < Size; ++q)
		{
			if (index != 0 && pow(2,p)*pow(3,q) == sequence[index-1])
			{
				;
			} else
			{
				sequence[index] = (pow(2,p)*pow(3,q));
				++index;
			}
		}
	}

	//sort sequence (ascending)
	length = index;
	qsort(sequence, length, sizeof(long), cmpfunc);

	//reverse sequence (to descending)
	for (indexFront = 0, indexRear = length - 1; indexFront < length/2; ++indexFront, --indexRear)
	{
		temp = sequence[indexFront];
		sequence[indexFront] = sequence[indexRear];
		sequence[indexRear] = temp;
	}

	//sort array
	long gap, val;
	int gapIndex, index1, inner;

	for (gapIndex = 0; gapIndex < length; ++gapIndex)
	{ //exits when we have used every gap in the sequence
		gap = sequence[gapIndex];
		for (index1 = gap; index1 < Size; ++index1)
		{ //starting at gap, stops when the starting index exceeds the size of the array, incrementing by 1
			val = array[index1]; //saves the value at gap (or some increments past gap) for reference
			++*NMove;
			++*NComp;
			for (inner = index1; (inner >= gap) && (array[inner - gap] > val); inner -= gap)
        	{ //swaps values if the lower value (index of inner - gap) is greater than val stored from an index of gap, decrementing inner by gap
            	array[inner] = array[inner - gap];
            	++*NMove;
        	}
        	array[inner] = val; //sets the index just swapped from, or the value not swapped back to val
        	++*NMove;
		}
	}

	free(sequence);

	return;
}

void Improved_Bubble_Sort (long * array, int Size, double * NComp, double * NMove)
{
	//sort array
	long gap, temp;
	int madeswap = 1, index;

	for (gap = floor(Size/1.3); gap >= 1 || madeswap; gap = floor(gap/1.3))
	{ //for loop handles creating sequence 2, with gap value checks below where gap cannot be 9, 10, or less than 1
		if (gap == 9 || gap == 10)
		{
			gap = 11;
		}

		if (gap < 1)
		{
			gap = 1;
		}
		//for every gap size, preforms a bubble sort between values 1 gap apart starting at 0 and shifts right
		for (index = 0, madeswap = 0; (index + gap) < Size; index++)
		{ //madeswap keeps track of whether or not we made a switch, allowing us to exit after we are sorted and gap == 1
			if (array[index] > array[index + gap])
			{ //swap values if not ascending
				temp = array[index];
				array[index] = array[index + gap];
				array[index + gap] = temp;
				madeswap = 1; //made a swap (not finished sorting)
				*NMove += 3;
			}
			++*NComp;
		}
	}

	return;
}

void Save_Seq1 (char * filename, int N)
{
	long * sequence = malloc(N * sizeof(long));
	int length, p, q, index, count;

	//make sequence 1 (will be randomized)
	for (p = 0, q = 0, index = 0; pow(2,p) < N; ++p)
	{ //controls power of 2 term until we are done
		for (q = 0; pow(2,p)*pow(3,q) < N; ++q)
		{ //controls power of 3 term until we need to go to the next power of 2
			if (index != 0 && pow(2,p)*pow(3,q) == sequence[index-1])
			{ //if its a duplicate, skip it
				;
			} else
			{ //if not save it in and increment the array
				sequence[index] = (pow(2,p)*pow(3,q));
				++index;
			}
		}
	}

	//sort sequence (ascending)
	length = index;
	qsort(sequence, length, sizeof(long), cmpfunc);

	//write sequence to file
	FILE * fp = fopen(filename, "w");

	for(count = 0; count < length; ++count)
	{
		if(!feof(fp))
		{
			fprintf(fp, "%ld\n", sequence[count]);		
		}
	}

	fclose(fp);
	return;
}

void Save_Seq2 (char * filename, int N)
{
	long * sequence = malloc(N * sizeof(long));
	int length, index, count, power;

	//make sequence 2 (will be in descending order)
	for (power = 1, index = 0; floor(N/(pow(1.3, power))) > 0; ++power)
	{ //outer control which stops when gap goes below 1
		if (index != 0 && floor(N/(pow(1.3, power))) == sequence[index - 1])
		{ //to prevent duplicates
			;
		} else if (floor(N/(pow(1.3, power))) == 9 || floor(N/(pow(1.3, power))) == 10)
		{ //if it is not a duplicate, and its either 9 or 10, save 11 instead
			if (sequence[index - 1] != 11)
			{ //to prevent a second 11
				sequence[index] = 11;
				++index;
			}
		} else
		{ //if it is not a duplicate and not 9 or 10, save the gap into the array
			sequence[index] = floor(N/(pow(1.3, power)));
			++index;
		}
	}

	//sort sequence (ascending)
	length = index;
	qsort(sequence, length, sizeof(long), cmpfunc);

	//write sequence to file
	FILE * fp = fopen(filename, "w");

	for(count = 0; count < length; ++count)
	{
		if(!feof(fp))
		{
			fprintf(fp, "%ld\n", sequence[count]);		
		}
	}

	fclose(fp);
	return;
}

int cmpfunc(const void * a, const void * b)
{ //used for qsort (for efficiently sorting the sequences)
	return ( *(int*)a - *(int*)b );
}

int check_sorted(long * array, int n)
{ //used for debugging
	int counter;
	int numincorrect = 0;
	//counts number of elements which are out of order and returns it
	for (counter = 0; counter < n - 1; ++counter)
	{
		if (array[counter] > array[counter + 1])
		{
			++numincorrect;
		}
	}
	return (numincorrect);
}