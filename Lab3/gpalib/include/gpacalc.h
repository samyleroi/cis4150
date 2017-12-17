#ifndef	__GPA_CALCULATOR_HEADER__
#define	__GPA_CALCULATOR_HEADER__

#ifndef         lint
/**
 ** PROTOTYPES
 **/

# if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
# endif

#define	GPA_A_PLUS		0x00
#define	GPA_A			0x01
#define	GPA_A_MINUS		0x02
#define	GPA_B_PLUS		0x03
#define	GPA_B			0x04
#define	GPA_B_MINUS		0x05
#define	GPA_C_PLUS		0x06
#define	GPA_C			0x07
#define	GPA_C_MINUS		0x08
#define	GPA_D_PLUS		0x09
#define	GPA_D			0x10
#define	GPA_D_MINUS		0x11
#define	GPA_F			0x12

#define	GPA_NUM_GRADE_RANGES		13

#define GPA_MAX_COURSES_PER_TERM	6
#define GPA_MAX_TERMS_PER_STUDENT	32


typedef struct GPAInfoTerm {
	char *term;
	int nCourses;
	const char *letterGrades[GPA_MAX_COURSES_PER_TERM];
} GPAInfoTerm;

typedef struct StudentGPAInfo {
	char *studentName;
	char *studentID;
	int nTerms;
	GPAInfoTerm term[GPA_MAX_TERMS_PER_STUDENT];
} StudentGPAInfo;

StudentGPAInfo *gpaCalcInit(const char *studentname, const char *studentID);

void gpaCalcDelete(StudentGPAInfo *info);

int gpaCalcAddLetterGrade(
		StudentGPAInfo *info,
		const char *term,
		const char *lettergrade);

int gpaCalcAddNumericGrade(
		StudentGPAInfo *info,
		const char *term,
		int percentageGrade);

float getTermGPA(StudentGPAInfo *info, const char *term);
float getOverallGPA(StudentGPAInfo *info);

const char * getLetterForNumericGrade(int percentageGrade);
float getGPAforNumericGrade(int percentageGrade);
float getGPAforLetterGrade(const char *letterGrade);
float getGPAforLetterIndex(int letterIndex);

# if defined(__cplusplus) || defined(c_plusplus)
}
# endif
#endif

#endif /*	__GPA_CALCULATOR_HEADER__ */
