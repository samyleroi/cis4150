#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

/**
 ** Include our header file
 **/
#include "cmulookup.h"



/** load the dictionary structure */
CMUDict *loadDictionary(const char *filename, int verbosity)
{
	CMUDict *dictionary;
	char linebuffer[BUFSIZ], *delim;
	int status, taglen;
	FILE *fp;

	dictionary = malloc(sizeof(CMUDict));
	if (dictionary == NULL)
		return NULL;

	dictionary->list = malloc(sizeof(CMU_record) * CMU_MAX_RECORDS);
	if (dictionary->list == NULL)
		return NULL;

	dictionary->nEntries = 0;


	if ((fp = fopen(filename, "rb")) == NULL)
	{
		fprintf(stderr, "Cannot open dictionary file '%s' : %s\n",
				filename, strerror(errno));
		return NULL;
	}

	while (fgets(linebuffer, BUFSIZ, fp) != NULL)
	{
		/** skip comments */
		if (strncmp(linebuffer, ";;;", 3) != 0) {

			/** trim '\n' */
			linebuffer[strlen(linebuffer)-1] = 0;

			delim = strstr(linebuffer, "  ");
			if (delim == NULL)
			{
				fprintf(stderr, "Entry %ld is invalid: [%s]\n",
						dictionary->nEntries,
						linebuffer);
			}

			taglen = delim - linebuffer;
			strncpy(dictionary->list[dictionary->nEntries].tag,
					linebuffer, taglen);
			dictionary->list[dictionary->nEntries].tag[taglen] = 0;

			/** trim any numbers */
			if (dictionary->list[dictionary->nEntries].tag[taglen - 3] == '('
					&& dictionary->list[dictionary->nEntries].tag[taglen - 1] == ')'
					&& isdigit(dictionary->list[dictionary->nEntries].tag[taglen - 2]))
				dictionary->list[dictionary->nEntries].tag[taglen - 3] = 0;


			/** copy in the entry portion */
			strcpy(dictionary->list[dictionary->nEntries].entry,
					&linebuffer[taglen + 2]);

			if (verbosity > 0)
				printf("%5ld : \"%s\" -> \"%s\"\n",
						dictionary->nEntries,
						dictionary->list[dictionary->nEntries].tag,
						dictionary->list[dictionary->nEntries].entry);

			dictionary->nEntries++;
		}
	}

	fclose(fp);

	return dictionary;
}

static int comparator(const void *v1, const void *v2)
{
	const CMU_record *r1;
	const CMU_record *r2;

	r1 = (const CMU_record *) v1;
	r2 = (const CMU_record *) v2;

	return strcmp(r1->tag, r2->tag);
}

int lookupEntryLocation(const CMUDict *dictionary, const char* key)
{
	CMU_record *searchResult;
	int resultIndex;

	searchResult = (CMU_record *) bsearch(key,
			dictionary->list, dictionary->nEntries,
			sizeof(CMU_record), comparator);

	if (searchResult == NULL)
		return -1;

	resultIndex = (int) (searchResult - dictionary->list);
	while (resultIndex > 0 &&
			strcmp(key, dictionary->list[resultIndex-1].tag) == 0)
		resultIndex--;

	return resultIndex;
}

/**
 * Process an open stream, reading keys one per line and printing results
 */
int processLookupsFromFP(
		FILE *ofp,
		FILE *ifp,
		const CMUDict *dictionary,
		int options,
		int verbosity
	)
{
	char linebuffer[BUFSIZ];
	int nLookups = 0;
	long entryIndex;

	while (fgets(linebuffer, BUFSIZ, ifp) != NULL)
	{
		/** skip comments */
		if (strcmp(linebuffer, ";;;") != 0) {

			/** trim '\n' */
			linebuffer[strlen(linebuffer)-1] = 0;
			entryIndex = lookupEntryLocation(dictionary, linebuffer);

			if (entryIndex < 0)
			{
				printf("?????\n");
			} else {
				if (options & CMU_OPTION_SINGLE)
				{
					if (verbosity > 0)
					{
						fprintf(ofp, "FOUND %3ld (%s) [%s] (first of multiple)\n",
							entryIndex,
							dictionary->list[entryIndex].tag,
							dictionary->list[entryIndex].entry);
						} else {
							fputs(dictionary->list[entryIndex].entry, ofp);
							fputc('\n', ofp);
						}
						entryIndex++;
				} else {
					while (strcmp(linebuffer, dictionary->list[entryIndex].tag) == 0)
					{
						if (verbosity > 0)
						{
							fprintf(ofp, "FOUND %3ld (%s) [%s]\n",
								entryIndex,
								dictionary->list[entryIndex].tag,
								dictionary->list[entryIndex].entry);
						} else {
							fputs(dictionary->list[entryIndex].entry, ofp);
							fputc('\n', ofp);
						}
						entryIndex++;
					}
				}
				nLookups++;
			}
		}
	}

	return nLookups;
}


/**
 * Open and process the file, by calling the above function
 */
int
processLookupsFromFile(
		FILE *ofp,
		const char *filename,
		const CMUDict *dictionary,
		int options,
		int verbosity
	)
{
	FILE *ifp;
	int nLookups;

	if ((ifp = fopen(filename, "rb")) == NULL)
	{
		fprintf(stderr, "Cannot open lookup keys file '%s' : %s\n",
				filename, strerror(errno));
		return -1;
	}

	nLookups = processLookupsFromFP(ofp, ifp, dictionary, options, verbosity);

	fclose(ifp);

	return nLookups;
}


