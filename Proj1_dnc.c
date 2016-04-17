#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <string.h>

typedef struct {
    int start;
	int end;
	int value;
} tTuple;

tTuple maxCrossingSum(int * a, int l, int m, int r)
{
	tTuple result;
	//left side
	int sum = 0;
	int left_sum = INT_MIN;
	for (int i = m; i >= l; i--)
	{
		sum += a[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			result.start = i;
		}
	}

	//right side
	sum = 0;
	int right_sum = INT_MIN;
	for (int i = m+1; i <= r; i++)
	{
		sum += a[i];
		if (sum > right_sum)
		{
			right_sum = sum;
			result.end = i;
		}
	}
	
	result.value = left_sum + right_sum;
	return result;
}


tTuple maxSubArraySum(int * a, int l, int r)
{
	tTuple left;
	tTuple right;
	tTuple mid;
	
	tTuple temp;
	
	if (l == r)
	{
		temp.start = l;
		temp.end = r;
		temp.value = a[l];
		return temp;
	}
	//mid
	int m = (l + r)/2;

	left = maxSubArraySum(a, l, m);
	mid = maxCrossingSum(a, l, m, r);
	right = maxSubArraySum(a, m+1, r);
	
	if(left.value >= right.value && left.value >= mid.value)
		return left;
	else if(right.value >= left.value && right.value >= mid.value)
		return right;
	else
		return mid;
}

void printArray(int s, int e, int * a, FILE* f)
{
	fprintf(f,"[");
	for(int i = s;i<e;i++)
	{
		fprintf(f,"%d, ", a[i]);
	}
	fprintf(f,"%d]\n", a[e]);
}

tTuple timeF(int * a, int s, int e)
{
	struct timeval t0, t1,tr;
	
	gettimeofday(&t0, 0);
	tTuple result = maxSubArraySum(a,s,e);
	gettimeofday(&t1, 0);
	
	//timersub(&t1, &t0, &tr);
	int microseconds = (t1.tv_sec - t0.tv_sec) * 1000000 + ((int)t1.tv_usec - (int)t0.tv_usec);
	tr.tv_sec = microseconds/1000000;
	tr.tv_usec = microseconds%1000000;
	printf("Computed in %ld.%06ld\n", (long int)tr.tv_sec, (long int)tr.tv_usec);
	return result;
}

int* randomArray(int size)
{
	
	int i, random;
	int* randArray = malloc(size*10);
	
	for(i = 0; i < size; i++){
		random = rand() % 200 - 100;
		randArray[i] = random;
	}
	return randArray;
}

int main()
{
	int size = 256;
	char line[size];
	int nums[size];
	int i;
	char * temp;
	tTuple result;
	int n[10] = {250, 500, 1000, 2500, 5000, 10000, 15000, 35000, 50000, 100000};
	
	
	FILE* file = fopen("MSS_TestProblems.txt", "r");
	if (file == NULL)
    {
        printf("Error Reading File\n");
        exit (0);
    }
	
	FILE* output = fopen("MSS_TestResults.txt","w");
	if (output == NULL)
    {
        printf("Error Writing File\n");
        exit (0);
    }
	
	while (fgets(line, sizeof(line), file))
	{
		i=0;
		temp = strtok(line," ,[]");
		//formats the input
		while(temp!=NULL)
		{
			nums[i] = atoi(temp);
			i++;
			temp = strtok(NULL," ,[]");
		}
		
		//print the answer + subarray
		result = maxSubArraySum(nums,0,i-2);
		printArray(0,i-2,nums, output);
		printArray(result.start, result.end, nums, output);
		fprintf(output,"%d\n", result.value);
		fprintf(output, "\n");		
	}
	
	//time functions
	int * temp2;
	for(int i=0;i<10;i++)
	{
		temp2 = randomArray(n[i]);
		printf("n: %d\n", n[i]);
		timeF(temp2,0,n[i]);
		printf("\n");
	}
	
	
	
}
