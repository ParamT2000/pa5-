#include <stdio.h>
#include <stdlib.h>

int compareInt(const void *p1, const void *p2);

long *Array_Load_From_File(char *filename, int *size);
int Array_Save_To_File(char *filename, long *array, int size);

int main(int argc, char * argv[]){
    int size;
    long * data = Array_Load_From_File(argv[1],&size);
    qsort(data,size,sizeof(long),compareInt);
    int sizeSaved = Array_Save_To_File(argv[2],data,size);

    if(size != sizeSaved){
        printf("\nfailed");
        return EXIT_FAILURE;
    }


return EXIT_SUCCESS;
}


int compareInt(const void *p1, const void *p2){
    long a = *((long*) p1);
    long b = *((long*) p2);

    if(a > b){
        return 1;
    }
    if(b > a){
        return -1;
    }
    
	return 0;
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
	
	FILE * output = fopen(filename, "w");
	int val = fwrite(array, sizeof(long), size, output);
	fclose(output);
	return val;
}
