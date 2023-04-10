/*
 * msort.c -- Merge Sort an array of elements
 *
 * This program sorts an array of elements
 *
 */

#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include "msort.h"

void **merge (void **array, void **emptyar, int start1, int start2, int end, 
              int (*compare)());
/* Merge the two sorted arrays */

/* int (*compare)(void *element1, void *element2) */
/* ------------------------------------------------------------------------ */

void **mergesort_work (void **unsorted, void **emptyar, int start, int end, 
                       int (*compare)())
/* Mergesort the strings */
{
/* Basic plan:
    If the array is one element long then it is sorted, return it.
    Otherwise, sort each half of it, and then merge the two sorted halves.
 */
  int mid;

  if (end-start>1) {
    mid = ((end-start)/2)+start;
    (void) mergesort_work (unsorted,emptyar,start,mid,compare);
    (void) mergesort_work (unsorted,emptyar,mid,end,compare);
    (void) merge (unsorted, emptyar, start, mid, end, compare);
    return unsorted;
  }
  else return unsorted; /* 1 element is always sorted */
}

void **mergesort (void **unsorted, int numelements, int (*compare)())
/* Mergesort the strings */
{
  void **emptyar;

  emptyar = (void**) malloc (sizeof(void*) * numelements);
  mergesort_work (unsorted, emptyar, 0, numelements, compare);
  free (emptyar);
  return unsorted;
}

void **merge (void **array, void **emptyar, int start1, int start2, int end, 
              int (*compare)())
/* Merge the two sorted arrays */
{
  int s1, s2, j;

  for (j=s1=start1, s2=start2; !((s1==start2)&&(s2==end)) ; j++) {
    if ((s1==start2)&&(s2!=end)) 
      emptyar[j]=array[s2++];
    else if ((s1!=start2)&&(s2==end)) 
      emptyar[j]=array[s1++];
    else {
      if ((*compare)(array[s1],array[s2])<=0) emptyar[j]=array[s1++];
      else emptyar[j]=array[s2++];
    }
  }  
  for (j=start1; j<end; j++)
    array[j]=emptyar[j];
  return array;
} /* merge */


