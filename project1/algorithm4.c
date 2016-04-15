#include <stdio.h>

int max_sum_subArray_4(int array[])
{
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
 
 
/* Driver program to test maxSubArraySum */
int main(){
	
   int array[] =  {-2, -3, 4, -1, -2, 1, 5, -3};
   //array = readin(file);
   int max_sum = max_sum_subArray_4(array);
   printf("\nThe maximum contiguous sum is: %d\n\n", max_sum);
   
   return 0;
}
