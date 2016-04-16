#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

clock_t time_start, time_stop, run_time;



/* ***************************************************************
*					  FUNCTION DECLARATIONS						 *
*************************************************************** */


int max_sum_subArray_4(int* array);
int* parseArray(char* line);
void getLine(FILE* file);
FILE* openFile(const char* filname);



/* ***************************************************************
*						  MAIN FUNCTION							 *
*************************************************************** */


 int main(){
 
	const char* fileIn = "MSS_TestProblems.txt";
	const char* fileOut = "MSS_TestResults.txt";
	FILE *fpIn, *fpOut;
	
	if (fpIn = openFile(fileIn)){
		printf("\nSuccessfully return pointer to %s: %p\n", fileIn, fpIn);
	}
	
	if (fpOut = openFile(fileOut)){
		printf("\nSuccessfully return pointer to %s: %p\n", fileOut, fpOut);
	}
	
	getLine(fpIn);
	
	fclose(fpIn);
	fclose(fpOut);
   
   return 0;
}



/* ***************************************************************
*						SUPPLEMENTAL FUNCTION					 *
*************************************************************** */
 

int max_sum_subArray_4(int* array){
	
	int size = sizeof(array);
	int min = 32767;
	
	int temp_max, current_max, combo = 0;
 
	for (int i = 0; i < size; i++){
		min = min < array[i] ? min : array[i];
		current_max = array[i] > (current_max + array[i]) ? array[i] : (current_max + array[i]);
		temp_max = temp_max > current_max ? temp_max : current_max;
	}
	return temp_max;
}


int* parseArray(char* passedLine){
	
	char* token;
	char line[256];
	int nextNum, i = 0;
	int* parsedArray = malloc(256);
	
	memcpy(&line, passedLine, 256);
	line[0] = ' ';
	token = strtok(line, ",");
	
	while(token != NULL){
		sscanf(token, "%d", &nextNum);
		printf("\nNumber: %d", nextNum);
		parsedArray[i] = nextNum;
		i++;
		token = strtok(NULL,",");
	}
	printf("\nDone parseArray\n");
	return parsedArray;
}


void getLine(FILE* file){
//void getLine(FILE* inFile, FILE* outFile){
	
	char lineIn[256];
	int* parsedArray;
	while ( fgets(lineIn, sizeof(lineIn), file) != NULL ){
		
		parsedArray = parseArray(lineIn);
		time_start = clock();
		int max = max_sum_subArray_4(parsedArray);
		time_stop = clock();
		run_time = ((double)(time_start - time_stop));
		
		printf("\nThe max of the array is: %d\nComputed in %d seconds\n", max, run_time);
	}
	free(parsedArray);
	
}


FILE* openFile(const char* filename){
	
	FILE *file = fopen(filename, "a+");
	
	if(file != NULL){
		return file;
	}
	else{
		printf("\nFailed to open %s", filename);
	}	
}


