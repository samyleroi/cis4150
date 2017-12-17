#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "gpacalc.h"

/**
 * initialize our grade calculation structure
 */
StudentGPAInfo *
gpaCalcInit(const char *studentName, const char *studentID)
{
	StudentGPAInfo *info;

	info = (StudentGPAInfo *) malloc(sizeof(StudentGPAInfo));
	bzero(info, sizeof(StudentGPAInfo));

	info->studentName = strdup(studentName);
	info->studentID = strdup(studentID);

	return info;
}

/**
 * Clean up our grade calculation structure
 */
void gpaCalcDelete(StudentGPAInfo *info)
{
	int i;

	for (i = 0; i < info->nTerms; i++)
	{
		if (info->term[i].term != NULL) free(info->term[i].term);
	}
	if (info->studentName != NULL) free(info->studentName);
	if (info->studentID != NULL) free(info->studentID);
}

/**
 * Add a letter grade to the list
 */
int gpaCalcAddLetterGrade(
		StudentGPAInfo *info,
		const char *term,
		const char *lettergrade)
{
	int i, found = (-1);

	/** search for other uses of this term */
	for (i = 0 ; i < GPA_MAX_TERMS_PER_STUDENT && i < info->nTerms; i++)
	{
		if (strcmp(info->term[i].term, term) == 0)
		{
			found = i;
			break;
		}
	}

	/** if this term is new, add it */
	if (found < 0)
	{
		if (info->nTerms >= GPA_MAX_TERMS_PER_STUDENT)
		{
			return -1;
		}
		found = info->nTerms++;
		info->term[found].term = strdup(term);
	}

	/** we have now found the right term, so add the course */
	info->term[found].letterGrades[ info->term[found].nCourses++ ] = lettergrade;

	return found;
}

/**
 * Add a numeric grade to the list
 */
int
gpaCalcAddNumericGrade(
		StudentGPAInfo *info,
		const char *term,
		int percentageGrade)
{
	const char *letterGrade;

	letterGrade = getLetterForNumericGrade(percentageGrade);

	return ( gpaCalcAddLetterGrade(info, term, letterGrade) );
}

/*
 * get the GPA for a term
 */
float
getTermGPA(StudentGPAInfo *info, const char *term)
{
	int i, found = (-1);
	float gpaSummation;

	/** search for other uses of this term */
	for (i = 0 ; i < info->nTerms; i++)
	{
		if (strcmp(info->term[i].term, term) == 0)
		{
			found = i;
			break;
		}
	}

	/** if this term is not found, GPA is negative infinity */
	if (found < 0)
	{
		return ((float) log(0));
	}

	/** calculate the average over this term */
	gpaSummation = getGPAforLetterGrade( info->term[found].letterGrades[0] );
	for (i = 1; i< info->term[found].nCourses; i++)
	{
		gpaSummation += getGPAforLetterGrade( info->term[found].letterGrades[i] );
	}

	return gpaSummation / (float) info->term[found].nCourses;
}

/*
 * Calculate overall GPA
 */
float
getOverallGPA(StudentGPAInfo *info)
{
	float gpaSummation;
	int i;

	gpaSummation = getTermGPA(info, info->term[0].term);
	for (i = 1; i < info->nTerms; i++)
	{
		gpaSummation += getTermGPA(info, info->term[i].term);
	}
	return gpaSummation / (float) info->nTerms;
}

