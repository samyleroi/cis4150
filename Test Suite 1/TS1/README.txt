SAMUEL UCHE 0871392

/***********************************************
COMPILE WITH:
************************************************/
gcc -Wall -std=c99 -o runtests runtests.c

/************************************************
EXECUTION:
*************************************************/
-To test all Test Cases use: ./run
-To test specific test case use ./run testcases/testcase<number>

-Example: ./run testcases/testcase12

/***********************************************
FILES INCLUDED:
************************************************/
-runtests.c is used to test the cmu program with test cases
-testcase files
-An EXPECTED file (ALL EXPECTED OUTPUTS ARE FOUND IN THE FILE NAMED : "EXPECTED")

/***********************************************
HOW COMPLETE IS THE ASSIGNMENT:
************************************************/
-Did not test for multiple pronounciations of a word.

/************************************************
ADDITIONAL INFO
*************************************************/
-testcase15 consists of 1 empty line. The test Fails however a segmentation fault 
message is peinted instead.
-A test is PASSED if it prints out the expected output and FAILS otherwise
