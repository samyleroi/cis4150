#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "gpacalc.h"

static struct {
	const char * desc;
	float gpa;
	const char *letter;
	int lo;
	int hi;
} sGradeConversions[]= {
	/*	Description		GPA			Letter		Low	High	*/
	{	"Outstanding",		4.3,	"A+",		90,	100	},
	{	"Excellent",		4.0,	"A",		85,	89	},
	{	"Very Good",		3.7,	"A-",		80,	84	},
	{	"Good",				3.3,	"B+",		77,	79	},
	{	"Good",				3.0,	"B",		73,	76	},
	{	"Good",				2.7,	"B-",		70,	72	},
	{	"Satisfactory",		2.3,	"C+",		67,	69	},
	{	"Satisfactory",		2.0,	"C",		63,	66	},
	{	"Satisfactory",		1.7,	"C-",		60,	62	},
	{	"Marginal Pass",	1.3,	"D+",		57,	59	},
	{	"Marginal Pass",	1.0,	"D",		53,	56	},
	{	"Marginal Pass",	0.7,	"D-",		50,	52	},
	{	"Failure",			0.0,	"F",		0,	49	}
};


/**
 * convert a percentage to a letter grade using the above table
 */
const char *
getLetterForNumericGrade(int percentageGrade)
{
	int i;

	if (percentageGrade < 0 || percentageGrade > 100)
		return NULL;

	for (i = 0; i < GPA_NUM_GRADE_RANGES; i++)
	{
		if (sGradeConversions[i].lo < percentageGrade && percentageGrade <= sGradeConversions[i].hi)
			return sGradeConversions[i].letter;
	}

	/* we should never get here */
	fprintf(stderr, "No letter available for percentage %d\n", percentageGrade);
	assert(0);
}

/**
 * convert a letter grade to GPA using the above table
 */
float
getGPAforLetterGrade(const char *letterGrade)
{
	int i;

	for (i = 0; i < GPA_NUM_GRADE_RANGES; i++)
	{
		if (sGradeConversions[i].letter == letterGrade)
			return sGradeConversions[i].gpa;
	}

	/* we got an invalid letter grade */
	fprintf(stderr, "Letter grade '%s' not an allowable grade\n", letterGrade);
	return (float) log(0);
}

/**
 * convert a letter grade to GPA using direct indexing into the above table
 */
float
getGPAforLetterIndex(int letterIndex)
{
	return sGradeConversions[letterIndex].gpa;
}

/**
 * convert a letter grade to GPA using direct indexing into the above table
 */
float
getGPAforNumericGrade(int percentageGrade)
{
	return getGPAforLetterGrade(getLetterForNumericGrade(percentageGrade));
}

