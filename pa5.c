#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sorting.h"



long *Array_Load_From_File(char *filename, int *size);
int Array_Save_To_File(char *filename, long *array, int size);

int main(int argc, char * argv[]){
    //should not do anything other than read/save files and call the merge and quicksort functions

    int size = 0;
    long * data = Array_Load_From_File(argv[2], &size);

	// printf("\n\n ORIGINAL: \n");
    // for(int count = 0; count < size; count ++){
	// 	printf("\n%ld", data[count]);
	// }
	// printf("\n");

    if(strcmp("-q",argv[1])== 0){
        Quick_Sort(data,size);
    }
    else if(strcmp("-m",argv[1]) == 0){
        Merge_Sort(data, size);

    }
	else{
		return EXIT_FAILURE;
	}
    
    int sizeSaved = Array_Save_To_File(argv[3],data,size);

	printf(" Size loaded = %d and size saved = %d\n",size, sizeSaved);

	// printf("\n\n SORTED: \n");

	// for(int count = 0; count < size; count ++){
	// 	printf("\n%ld", data[count]);
	// }
	// printf("\n");


    free(data);




    return EXIT_SUCCESS;
}



long *Array_Load_From_File(char *filename, int *size){

	FILE * dataFile = fopen(filename, "rb");
	long * retAdd = NULL;
	

	if(dataFile == NULL){
		
		return retAdd;
	}

	fseek(dataFile, 0, SEEK_END);
	unsigned long numBytes = (unsigned long)ftell(dataFile);
	fseek(dataFile, 0, SEEK_SET);
	*size = numBytes / (sizeof(long));
		
	retAdd = malloc(*size * sizeof(long));
	if(retAdd == NULL){
		return NULL;
	}
	
	fread(retAdd, sizeof(long), *size, dataFile);
	
	fclose(dataFile);
	
	
	return retAdd;

}

int Array_Save_To_File(char *filename, long *array, int size){
	
	FILE * output = fopen(filename, "wb");
	int val = fwrite(array, sizeof(long), size, output);
	fclose(output);
	return val;
}


