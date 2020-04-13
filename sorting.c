#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

#define SMALL_NUM 30

//headers
static int partition1(long *array, int lb, int ub);
static void qSortTR(long * array, int lb, int ub);
static void insertion(long * array, int size);

/****************************************
* START OF quick sort SORT STUFF
*
***************************************/

//static int m3dian(long * array, int ind1, int ind2, int ind3);

/****************************************
* NAME: 
* PARAMETERS:
* RETURN:
* DESCRIPTION: 
*
***************************************/
void Quick_Sort(long *Array, int Size){
    int lb = 0;
    int ub = 0;
    printf("\n size received - %d", Size);
    if(Size != 0){
        ub = Size - 1;
    }
    
    qSortTR(Array,lb,ub);
    insertion(Array,Size);

    
}

/****************************************
* NAME: partition1
* PARAMETERS: long *, int lb and ub
* RETURN:
* DESCRIPTION: 
*
***************************************/
static int partition1(long *array, int lb, int ub){
    //use the median of 3 method
    //int pivotInd = m3dian(array, lb, (lb + ub)/2, ub);

    int tempi = 0;
    int ind1 = lb;
    int ind2 = (lb + ub) /2;
    int ind3 = ub;

    if (array[ind2] < array[ind1]){
        tempi = ind2;
        ind2 = ind1;
        ind1 = tempi;
    }
    if(array[ind3] < array[ind2]){
        if(array[3] < array[1]){
            tempi = ind3;
            ind3 = ind2;
            ind2 = ind1;
            ind1 = tempi;
        }
        else{
            tempi = ind3;
            ind3 = ind2;
            ind2 = tempi;
        }
    }

    long pivotInd = ind2; 
    long pivot = array[pivotInd];

    int downPos = lb;
    int upPos = ub;

    long temp = 0;

    temp = array[pivotInd];
    array[pivotInd] = array[lb];
    array[lb] = temp;

    while (downPos < upPos){
        while((array[downPos] <= pivot) && (downPos < ub)){
            downPos ++;
        }
        while(array[upPos] > pivot){
            upPos --;
        }
        if(downPos < upPos){
            temp = array[upPos];
            array[upPos] = array[downPos];
            array[downPos] = temp;
        }
    }
    
    array[lb] = array[upPos]; 
    array[upPos] = pivot;
    return upPos; 

}

/****************************************
* NAME: qSortTR
* PARAMETERS:long * array, ints lb and ub
* RETURN:
* DESCRIPTION: 
*
***************************************/
static void qSortTR(long * array, int lb, int ub ){
    int pivotInd = 0;

    while((ub - lb) > SMALL_NUM){
        pivotInd = partition1(array,lb,ub);
        if(pivotInd < (lb + ub)/2){
            qSortTR(array, lb, pivotInd -1);
            lb = pivotInd + 1;
        }
        else{
            qSortTR(array, pivotInd + 1, ub);
            ub = pivotInd -1;
        }    
    }
    
}

/****************************************
* NAME: m3dian
* PARAMETERS: array, 3 indices
* RETURN: index of median
* DESCRIPTION: 
*
****************************************/
//  static int m3dian(long * array, int ind1, int ind2, int ind3){

//     //could optimize this process
//     int temp = 0;

//     if (array[ind2] < array[ind1]){
//         temp = ind2;
//         ind2 = ind1;
//         ind1 = temp;
//     }
//     if(array[ind3] < array[ind2]){
//         if(array[3] < array[1]){
//             temp = ind3;
//             ind3 = ind2;
//             ind2 = ind1;
//             ind1 = temp;
//         }
//         else{
//             temp = ind3;
//             ind3 = ind2;
//             ind2 = temp;
//         }
//     }

  
//     return ind2;
//  }

/****************************************
* NAME: insertion
* PARAMETERS: long * array
* RETURN: void
* DESCRIPTION: basic insertion sort
*
***************************************/

static void insertion(long * array, int size){
    int i = 1;
    int j =0;
    long val = 0;

    while( i < size){
        val = array[i];
        j = i - 1;
        while( j>= 0 && val < array[j] ){
            array[j + 1] = array[j];
            j--;
        }
        
        array[1 + j] = val;
    i++;
    }

}

/****************************************
* START OF MERGE SORT STUFF
*
***************************************/
int findEnd(long * array, int size, int start);



void Merge_Sort(long *Array, int Size){
    int runs;
    
    long * tempArray = malloc(sizeof(long) * Size));
    memcpy(tempArray, Array, )
    do{
        runs = 0;

        int i = 0;
        while(i = 0){
            runs++;
            
            //end of left non descending array
            int endLeft = findEnd(array,Size, i);

            //check if there is a right subarray 
            if(endLeft + 1 < size){
                int endRight = findEnd(Array,size,endLeft + 1);
                merge(array, tempArray, i,endLeft, endRight);
                i = endRight + 1; //index of next left sub array
            }
            else{
                break;
            }
        }

    }while(runs > 1);
}
/****************************************
* NAME: findEnd
* PARAMETERS: long * array, int size, int start
* RETURN: int end
* DESCRIPTION: runs through the array to find ascending
* elements 
*
***************************************/
int findEnd(long * array, int size, int start){

    int end = start;
    while(((end + 1) < size) && array[end] <= array[end+ 1]){ 
        end++; //increments the index while the next value is greater than the previous

    }

    return end;
}

/****************************************
* NAME: merge
* PARAMETERS: long * array, long * temp, int size, int start
* RETURN: void 
* DESCRIPTION: merges the temp into the array
*
***************************************/

void(long * array, long * toMerge, int lb, int mid, int ub){


}