#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <string.h>

typedef struct {
    int * coins;
	int num;
} tTuple;

tTuple changeslow(int * a, int v, int n, tTuple result)
{
	int soln = -1;
	int coins[n];
	tTuple test_soln;
	
	
	//Base condition
	if(v == 0)
	{
		result.coins[n] = 0;
		result.num = 0;
		return result;
	}
	
	//Fail condition
	if (n==0)
	{
		result.coins[n] = 0;
		result.num = -1;
		return result;
	}
	
	int i = n-1;
	int stop = v/a[i];

	if(a[i] * stop == v)
	{	
		result.num = stop;
		result.coins[i] = stop;
		return result;
	}
	
	for(int j=0;j<=stop;j++)
	{
		int v2 = v - (j * a[i]);
		test_soln = changeslow(a,v2,n-1,result);
		
		if(test_soln.num >=0)
		{
			if(soln == -1 || test_soln.num + j< soln)
			{
				result.coins[i] = j;
				soln = test_soln.num + j;
			}
		}
	}
	
	result.coins = coins;
	result.num = soln;
	return result;
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

tTuple timeF(int * a, int v, int n,tTuple result)
{
	struct timeval t0, t1,tr;
	
	gettimeofday(&t0, 0);
	result = changeslow(a,v,n,result);
	gettimeofday(&t1, 0);
	
	//timersub(&t1, &t0, &tr);
	int microseconds = (t1.tv_sec - t0.tv_sec) * 1000000 + ((int)t1.tv_usec - (int)t0.tv_usec);
	tr.tv_sec = microseconds/1000000;
	tr.tv_usec = microseconds%1000000;
	printf("Computed in %ld.%06ld\n", (long int)tr.tv_sec, (long int)tr.tv_usec);
	return result;
}

int main()
{
	int size = 256;
	char line[size];
	int nums[size];
	int i;
	char * temp;
	int val;
	tTuple result;
	tTuple result2;
	

	
	FILE* file = fopen("coins.txt", "r");
	if (file == NULL)
    {
        printf("Error Reading File\n");
        exit (0);
    }
	
	FILE* output = fopen("coins_result.txt","a");
	if (output == NULL)
    {
        printf("Error Writing File\n");
        exit (0);
    }
	
	fprintf(output,"Algorithm changeslow\n");
	
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
		val = atoi(fgets(line,sizeof(line),file));
		int coins[i-2];
		for(int q=0;q<i-1;q++)
			coins[q] = 0;
		result.coins = coins;
		result.num = 0;
		//print the answer + subarray
		result2 = changeslow(nums,val,i-2,result);
		printArray(0,i-2,result.coins, output);
		fprintf(output,"%d\n",result2.num);
	}
}
