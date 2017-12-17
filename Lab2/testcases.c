#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> 
#include "gpacalc.h"

const int MAX_THREADS = 64;

/* Global variable:  accessible to all threads */
void* runTests(void* rank);
void evaluateTestCase(char* expectedOut, char* out, int type);

int main(int argc, char* argv[]) {

	char output[100];

	long       thread;
	pthread_t* thread_handles;

	thread_handles = malloc (6*sizeof(pthread_t));


	for (thread = 0; thread < 6; thread++)
	  pthread_create(&thread_handles[thread], NULL,
	      runTests, (void*) thread);

	for (thread = 0; thread < 6; thread++)
	{
	  pthread_join(thread_handles[thread], NULL);
	}

	return 0;
}

void* runTests(void* rank)
{
    long caseNumber = (long) rank;
    char output[100];

    if (caseNumber == 0)
    {
		printf("\nTest Case 1\nValue: 2\n");
		strcpy(output,getLetterForNumericGrade(2));
		printf("Output: %s\n",output);
		evaluateTestCase("F",output,0);
    }
    else if (caseNumber == 1)
    {
		printf("Test Case 2\nValue: 97\n");
		strcpy(output,getLetterForNumericGrade(97));
		printf("Output: %s\n",output);
		evaluateTestCase("A+",output,0);
    }
    else if (caseNumber == 2)
    {
		printf("Test Case 3\nValue: 51\n");
		strcpy(output,getLetterForNumericGrade(51));
		printf("Output: %s\n",output);
		evaluateTestCase("D-",output,0);
    }
    else if (caseNumber == 5)
    {
		printf("Test Case 4\nValue: 71\n");
		strcpy(output,getLetterForNumericGrade(71));
		printf("Output: %s\n",output);
		evaluateTestCase("B-",output,1);
    }
    else if (caseNumber  == 4)
    {
		printf("Test Case 5\nValue: -1\n");
		if (getLetterForNumericGrade(-1) == NULL)
		{
			printf("Output: NULL\n");
			evaluateTestCase("NULL","NULL",2);
		}
		else
		{
			strcpy(output,getLetterForNumericGrade(-1));
			printf("Output: %s\n",output);
			evaluateTestCase("F","output",2);
		}
    }
    else if (caseNumber == 3)
    {
		printf("Test Case 6\nValue: 101\n");
		if (getLetterForNumericGrade(101) == NULL)
		{
			printf("Output: NULL\n");
			evaluateTestCase("NULL","NULL",2);
		}
		else
		{
			strcpy(output,getLetterForNumericGrade(101));
			printf("Output: %s\n",output);
			evaluateTestCase("F","output",2);
		}
    }
    return NULL;
}

void evaluateTestCase(char* expectedOut, char* out, int type)
{
	if (strcmp(expectedOut,out) == 0)
	{
		printf("PASS: ");
	}
	else
	{
		printf("FAIL: ");
	}

	if (type == 0)
	{
		printf("Nominal value in equivalence class\n");
	}
	else if (type = 1)
	{
		printf("Value on boundary of equivalence class\n");
	}
	else if(type = 2)
	{
		printf("Value outside of class range\n");
	}
}