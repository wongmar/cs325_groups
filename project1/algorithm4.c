#include <stdio.h>
#include <time.h>

clock_t time_start, time_stop, run_time;



/* ***************************************************************
*		  	    MAIN FUNCTION			 *
*************************************************************** */


 int main(){
	 
	//int array[] =  {-2, -3, 4, -1, -2, 1, 5, -3};
	//array = readin(file);
	int max_sum = max_sum_subArray_4(array);
	printf("\nThe maximum contiguous sum is: %d\n\n", max_sum);
   
   return 0;
}



/* ***************************************************************
*			SUPPLEMENTAL FUNCTION			 *
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


int* parseArray(char* line){
	
	char c;
	int* array = malloc(256);
	
}


int getLine(FILE* file){
	
	char* lineIn = malloc(256);
	int* parsedArray = malloc(256);
	while ( fgets(line, sizeof(line), file) != NULL ){
		
		int* parsedArray = parseArray(line);
		time_start = clock();
		int max = max_sum_subArray_4(parseArray);
		time_stop = clock();
		run_time = ((double)(time_start - time_stop);
		
		printf("\nThe max of the array is: %d\nComputed in %d seconds\n", max, run_time);
	}
	free(parsedArray);
	free(lineIn);
	fclose(file);
}


FILE* openFile(){
	
	static const char filename[] = "MSS_TestProblems.txt";
	FILE *file = fopen(filename, "r");
	
	if(file != NULL){
		return file;
	}
	else{
		printf("\nFailed to open %s", filename);
	}	
}


