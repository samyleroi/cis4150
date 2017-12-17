#ifndef __CMU_LOOKUP_HEADER__
#define __CMU_LOOKUP_HEADER__

#define	CMU_TAG_LENGTH		32
#define	CMU_ENTRY_LENGTH	128

#define CMU_MAX_RECORDS		150000


#define CMU_OPTION_SINGLE	0x01

typedef struct CMU_record {
	char tag[CMU_TAG_LENGTH];
	char entry[CMU_ENTRY_LENGTH];
} CMU_record;

typedef struct CMUDict {
	long nEntries;
	CMU_record *list;
} CMUDict;


/**
 * Prototypes
 */
CMUDict *loadDictionary(const char *filename, int verbosity);
int processLookupsFromFP(FILE *ofp, FILE *ifp, const CMUDict *dict, int options, int verb);
int processLookupsFromFile(FILE *ofp, const char *name, const CMUDict *dict, int options, int verb);

#endif /* __CMU_LOOKUP_HEADER__ */
