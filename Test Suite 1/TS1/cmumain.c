#include <stdio.h>
#include <errno.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

/**
 ** Include our header file
 **/
#include "cmulookup.h"


/**
 * Command line help
 */
static void printHelp()
{
	printf("cmulookup <databasefile> <keyfile> [ ... ]\n");
	printf("\n");
	printf("Options:\n");
	printf("-o <file> : direct output to <file>\n");
	printf("-v        : verbosely list activity\n");
	printf("-1        : when a list of results are available, print only the first\n");
	printf("-h        : print this help\n");
}

int
main(int argc, char **argv)
{
	FILE *ofp = stdout;
	char optionChar;
	int i, nLookups = 0;
	int verbosity = 0;
	int options = 0;
	CMUDict *dictionary;


	/** use getopt(3) to parse up any option flags we may have */
	while ((optionChar = getopt(argc, argv, "o:hv1")) != -1) {
		switch (optionChar) {

		case 'o':
			/* override the standard output destination */
			ofp = fopen(optarg, "w");
			if (ofp == NULL)
			{
				/*
				 * if we couldn't open the file, use strerror(3)
				 * to let the user know why
				 */
				fprintf(stderr,
						"Cannot open file '%s' : %s\n",
						optarg, strerror(errno));
				exit(1);
			}
			break;

		case 'v':
			verbosity++;
			break;

		case '1':
			options |= CMU_OPTION_SINGLE;
			break;

		case 'h':
		case '?':
		default:
			/* 
			 * use fall-through to get here with any of these
			 * three options
			 */
			printHelp();
			exit (1);
		}
	}

	/* skip past the arguments processed by getopt(3) */
	argc -= optind;
	argv += optind;

	/* at this point, argv should point at a list of names
	 * of files that is argc entries long
	 */
	if (argc < 1)
	{
		/* so if not, issue an error and stop */
		fprintf(stderr, "Invalid command line syntax.\n");
		fprintf(stderr, "Database name are required; selection key files optional.\n\n");
		printHelp();
		exit (1);
	}

	dictionary = loadDictionary(argv[0], verbosity);
	if (dictionary == NULL)
	{
		fprintf(stderr, "Failed loading dictionary\n");
		exit (-1);
	}

	if (argc > 1)
	{
		int nThisRound = 0;
		int i;
		
		for (i = 1 ; i < argc; i++)
		{
			nThisRound = processLookupsFromFile(ofp, argv[i], dictionary, options, verbosity - 1);
			if (nThisRound < 0)
			{
				fprintf(stderr, "Failed processing '%s'\n", argv[i]);
				exit (-1);
			}
			nLookups += nThisRound;
			printf("===== (%d)\n", nThisRound);
		}
	} else {
		nLookups = processLookupsFromFP(ofp, stdin, dictionary, options, verbosity - 1);
		if (nLookups < 0)
		{
			fprintf(stderr, "Failed processing standard input\n");
			exit(-1);
		}
	}

	printf("DONE! (%d lookups)\n", nLookups);

	return 0;
}

