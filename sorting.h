#ifndef __sorting_h_
#define __sorting_h_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Constant Definitions

/* Return/Error Codes */
#define OK               (  0 )  // No errors, everything as should be
#define ERROR            ( -1 ) // Generic error

// structures
  
/* Function Prototypes */
long *Load_File(char *Filename, int *Size);
int Save_File(char *Filename, long *Array, int Size);
void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
void Improved_Bubble_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
int cmpfunc(const void * a, const void * b);
int check_sorted(long * array, int n);
void Save_Seq1 (char * filename, int N);
void Save_Seq2 (char * filename, int N);

#endif  // __sorting_h_ 

