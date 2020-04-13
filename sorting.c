#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include <string.h>
#include <stdbool.h>

#define SMALL_NUM 30

#define DEBUG 0

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
int findEndA(long * array, int size, int start);
int findEndD(long * array, int size, int start);
void merge(long * toMerge, long*, int lb, int mid, int ub);
void newMergeA(long * toMerge, long * getMerged, int lb, int ub);
void newMergeD(long * toMerge, long * getMerged, int lb, int ub);
long * mergeSortRec(long* toMerge, long * getMerged, int lb, int ub, bool dir);


void Merge_Sort(long *Array, int Size){
    
    
    long * tempArray = malloc(sizeof(long) * Size);

    if(tempArray == NULL){
        printf("\n MALLOC RETURNS NULL");
        return;

    }

    memcpy(tempArray, Array, (sizeof(long) * Size));
    long * swap = NULL;
    long * origAdd = Array; //saves the address given in the original call

    Array = mergeSortRec(tempArray, Array, 0, Size - 1, 1);

    if(Array != origAdd){
        memcpy(origAdd, Array, sizeof(long) * Size);
        free(Array);
    }
    else{
        free(tempArray);
    }

    

}
 /****************************************
* NAME: mergeSortRec
* PARAMETERS: long * array, int size, int start
* RETURN: int end
* DESCRIPTION: runs through the array to find ascending
* elements 
*
***************************************/
long * mergeSortRec(long* toMerge, long * getMerged, int lb, int ub, bool dir){

    if(ub - lb == 0){
        #if DEBUG
        printf("\nreturned");
        #endif
        return NULL;
    }
    int mid = (lb + ub) / 2;

    //swaps them so that the roles are flipped on the next run
    long * swap = toMerge;
    toMerge = getMerged;
    getMerged = swap;

    long * temp = NULL;

    temp = mergeSortRec(toMerge, getMerged, lb, mid, dir); //left call is in the same direcrtion
    #if DEBUG 
        printf("\nran left, moving to right"); 
    #endif
    temp = mergeSortRec(toMerge, getMerged, mid + 1, ub,(!dir)); // right is opposite direction

    

   
    if(dir){
        newMergeA(toMerge,getMerged, lb,ub);
    }
    else{
        newMergeD(toMerge,getMerged, lb,ub);
    }

    return getMerged;

}



/****************************************
* NAME: findEnd
* PARAMETERS: long * array, int size, int start
* RETURN: int end
* DESCRIPTION: runs through the array to find ascending
* elements 
*
***************************************/
int findEndA(long * array, int size, int start){

    int end = start;
    while(((end + 1) < size) && array[end] <= array[end+ 1]){ 
        end++; //increments the index while the next value is greater than the previous

    }

    return end;
}

/****************************************
* NAME: findEndD
* PARAMETERS: long * array, int size, int start
* RETURN: int end
* DESCRIPTION: runs through the array to find descending
* elements 
*
***************************************/
int findEndD(long * array, int size, int start){

    int end = start;
    while(((end + 1) < size) && array[end] >= array[end+ 1]){ 
        end++; //increments the index while the next value is less than the previous

    }

    return end;
}


/***************************************
*NAME: New merge
*The right subarray shoudl be sorted in descending order
* this eliminates the need to have many comparisons
* Also prevents the merge from going out of bounds
**************************************/
void newMergeA(long * toMerge, long * getMerged, int lb, int ub){
   
    int getMerInd = 0; //index of the array where values are being placed
    int i = lb; //index of left sub array
    int j = ub; //index of right sub array going in reverse. might  need the -1

    #if DEBUG
    printf("\n lb = %d, ub = %d", lb ,ub);
    printf("\ntoMerge= %p", (void*)toMerge);
    #endif

    for(getMerInd = lb; getMerInd <= ub; getMerInd++ ){ //merge from toMerge to getMerged
        //the bounds might not need the +1
        #if DEBUG
        printf("\n toMerge[%d]= %ld, toMerge[%d] %ld", i,toMerge[i],j, toMerge[j]);
        #endif
        if(toMerge[i] < toMerge[j]){
        #if DEBUG
            printf("\npicked i");
        #endif

            getMerged[getMerInd] = toMerge[i++];
        }
        else{
            #if DEBUG
            printf("\npicked j");
            #endif
            getMerged[getMerInd] = toMerge[j--];
        }
        
    }
    #if DEBUG
        printf("\nRan mergeA placed in %p\n", (void*)getMerged);
        for(i = lb; i <= ub; i++){
            printf("% ld ", getMerged[i]);
        }
        printf("\n\n");
    #endif

}

void newMergeD(long * toMerge, long * getMerged, int lb, int ub){
   
    int getMerInd = 0; //index of the array where values are being placed
    int i = lb; //index of left sub array
    int j = ub; //index of right sub array going in reverse

    #if DEBUG
    printf("\n lb = %d, ub = %d", lb ,ub);
    printf("\ntoMerge= %p", (void*)toMerge);
    #endif

    for(getMerInd = lb; getMerInd <= ub; getMerInd++ ){ //merge from toMerge to getMerged
        //the bounds might not need the +1
        #if DEBUG
        printf("\n toMerge[%d]= %ld, toMerge[%d] %ld", i,toMerge[i], j,toMerge[j]);
        #endif

        if(toMerge[i] >= toMerge[j]){
            #if DEBUG
            printf("\npicked i");
            #endif
            getMerged[getMerInd] = toMerge[i++];
        }
        else{
            #if DEBUG
            printf("\npicked j");
            #endif

            getMerged[getMerInd] = toMerge[j--];
        }

    }
    #if DEBUG
        printf("\nRan mergeD place in %p\n", (void*)getMerged);
        for(i = lb; i <= ub; i++){
            printf("% ld ", getMerged[i]);
        }
        printf("\n\n");
    #endif
        
    
}
/****************************************
* NAME: merge
* PARAMETERS: long * array, long * temp, int size, int start
* RETURN: void 
* DESCRIPTION: merges the temp into the array
* 
*
***************************************/
void merge(long * toMerge, long * getMerged, int lb, int mid, int ub){
    //printf("\n\nMERGING WITH lb = %d mid = %d and ub = %d\n", lb,mid,ub);
    
    int m = lb; //index of getMerged
    int i = lb;
    int j = mid + 1;

    while((i <= mid) && (j <= ub)){
        if ( toMerge [j] < toMerge [i]) { 
            getMerged[m++] = toMerge[j++]; 
        }
        else {
            getMerged[m++] = toMerge [i++]; 
        }
    }
    while(i++ <= mid){
        getMerged[m++] = toMerge [i++];
    }
    while(j++ <= ub){
        getMerged[m++] = toMerge[i++];
    }

}


/************************
*NAME: past attempts
*
*
*************************/

//void Merge_Sort(long *Array, int Size){
//     int runs;
    
//     long * tempArray = malloc(sizeof(long) * Size);

//     if(tempArray == NULL){
//         printf("\n MALLOC RETURNS NULL");
//         return;

//     }

//     memcpy(tempArray, Array, (sizeof(long) * Size));
//     long * swap = NULL;

//     long * origArray = Array;

//     //int deb = 2;

//     // #ifdef DEBUG
//     // printf("\nORIGINAL ARRAY");
//     // for(int c = 0; c < Size; c++){
//     //     printf("\nindex %d, value =%ld",c,Array[c]);
//     // }
//     // #endif

//     do{
//         runs = 0;
//         //printf("\n big while\n");
//         int i = 0;

//         while(i < Size){
//             //printf("\n i= %d", i);
//             runs++;
            
//             //end of left non descending array
//             int endLeft = findEndA(tempArray,Size, i);
//             //printf("\nendleft = %d", endLeft);

//             //check if there is a right subarray 
//             if(endLeft + 1 < Size){
//                 int endRight = findEndA(tempArray,Size,endLeft + 1); //right one is descending 
//                 //printf("\nendright = %d", endRight);
//                 merge(tempArray, Array, i, endLeft, endRight);

//                 // #ifdef DEBUG
//                 // printf("\nintermediate array");
//                 // for(int c = 0; c < Size; c++){
//                 //     printf("\nindex %d, value =%ld",c,Array[c]);
//                 // }
//                 // #endif

//                 i = endRight + 1; //index of next left sub array
 
//             } else if(endLeft == Size - 1) {
//                 merge(tempArray, Array, i, i, endLeft);
//                 i++;
//             }

//             else{
//                 break;
//             }
//         }
//         //swaps them so that the roles are flipped on the next run
//         swap = Array;
//         Array = tempArray;
//         tempArray = swap;
    
    

//     }while(runs > 1);

//     if(tempArray != origArray){
//         memcpy(origArray, tempArray, sizeof(long) * Size);
//         free(tempArray);
//     }
//     else{
//         free(Array);
//     }
    
    
//     // #ifdef DEBUG
//     // printf("\nNEW ARRAY");
//     // for(int c = 0; c < Size; c++){
//     //     printf("\nindex %d, value =%ld",c,origArray[c]);
//     // }
//     // #endif

    
    

// }