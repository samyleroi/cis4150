#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 300
void runAllTests();
void runTest(int);
int parse(char * cmd, int tag);
void rmLine(char * line);

int main(int argc, char ** argv){
  if(argc ==1){
    runAllTests();
  }else if (argc ==2){
    argv[1] += 18;
    int num = atoi(argv[1]);
    runTest(num);    
  }else{
    return 0;
  }
  return 0;
}

void runAllTests(){
  printf("\nTestcase 1: Line Length=29, Tag Length=29");
  parse("echo \"SUPERCALIFRAGILISTICEXPIALIDOCI\" | ./cmulookup testcases/testcase1",1);
  printf("\nTestcase 2: Line Length=47,Tag Length=33");
  parse("echo \"HONEYQWERTYUIOPASDFGHJKLZXCVBNMQW\" | ./cmulookup testcases/testcase2",2);
  printf("\nTestcase 3: Line Length =64, Tag Length=16");
  parse("echo \"HONNNEYYYYMOONNNNERS\" | ./cmulookup testcases/testcase3",3);
  printf("\nTestcase 4: Line Length=40, Tag Length=16");
  parse("echo \"HOOONEEEYMOOONS\" | ./cmulookup testcases/testcase4",4);
  printf("\nTestcase 5: Line Length=129, Tag Length=33");
  parse("echo \"HONEHONEHONEHONEHONEHONEHONEHONE\" | ./cmulookup testcases/testcase5",5);
  printf("\nTestcase 6: Line Length=0, Tag Length=0, Phoneme Length =0");
  parse("echo \" \" | ./cmulookup testcases/testcase6",6);
  printf("\nTestcase 7: Number of Lines=75000");
  parse("echo \"AROMA\" | ./cmulookup testcases/testcase7",7);
  printf("\nTestcase 8: Line Length =24, Tag Length = 0");
  parse("echo \" \" | ./cmulookup testcases/testcase8",8);
  printf("\nTestcase 9: Line Length =129, Tag Length = 32");
  parse("echo \"SUPERCALIFRAGILISTICEXPIALIDOCI\" | ./cmulookup testcases/testcase9",9);
  printf("\nTestcase 10: Line Length = 128, Tag Length = 35");
  parse("echo \"SUPERCALIFRAGILISTICEXPIALIDOCIOUS\" | ./cmulookup testcases/testcase10",10);
  printf("\nTestcase 11: Line Length = 64, Tag Length = 32");
  parse("echo \"SUPERCALIFRAGILISTICEXPIALIDOCI\" | ./cmulookup testcases/testcase11",11);
  printf("\nTestcase 12: Line Length = 13, Tag Length = 0");
  parse("echo \" \" | ./cmulookup testcases/testcase12",12);
  printf("\nTestcase 13: Line Length =128, Tag Length = 16");
  parse("echo \"SUPERCALIFRAGIS\" | ./cmulookup testcases/testcase13",13);
  printf("\nTestcase 14: Line Length = 128, tag Length=1");
  parse("echo \"S\" | ./cmulookup testcases/testcase14",14);
  printf("\nTestcase 15: Line Length = 0, Tag Length=0, Phoneme Length=0");
  parse("echo \"\" | ./cmulookup testcases/testcase15",15);
  printf("\nTestcase 16: Line Length=1, Tag Length=1");
  parse("echo \"A\" | ./cmulookup testcases/testcase16",16);
  printf("\nTestcase 17: Number of Lines=150,000");
  parse("echo \"ZYWICKI\" | ./cmulookup testcases/testcase17",17);
  printf("\nTestcase 18: Number of Lines = 150,001");
  parse("echo \"ZYWICKI\" | ./cmulookup testcases/testcase18",18);
}

int parse(char * cmd,int tag) {

    char buf[BUFSIZE];
    FILE *fp;

    if ((fp = popen(cmd, "r")) == NULL) {
        return -1;
    }
    char * word = (char *) malloc(sizeof(char*));
    int i=0;
    while (fgets(buf, BUFSIZE, fp) != NULL) {
      if(i == 0){
        strcpy(word,buf);
        i++;
      }
    }
    if(pclose(fp)) {
        return -1;
    }
    if(tag==1){
      if(strcmp("?????\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==2){
      if(strcmp("?????\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==3){
      if(strcmp("HHH AAAHHH1 N IIIIY0 M UWWWW2 N EEERRR0 Z\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==4){
       if(strcmp("HH AH1 N IY0 M UW2 N Z\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==5){
      if(strcmp("?????\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==6){
      if(strcmp("?????\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==7){
      if(strcmp("ER0 OW1 M AH0\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==8){
      if(strcmp("?????\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==9){
      if(strcmp("S UW2 P ER0 K AE2 L AH0 F R AE1 JH AH0 L IH2 S T IH0 K EH2 K S P IY0 AE2 L AH0 D OW1 SH AH0 SSS\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==10){
      if(strcmp("?????\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==11){
      if(strcmp("S UW2 P ER0 K AE2 L AH0 F R AE\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==12){
      if(strcmp("?????\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==13){
      if(strcmp("S UW2 P ER0 K AE2 L AH0 F R AE1 JH AH0 L IH2 S T IH0 K EH2 K S P IY0 AE2 L AH0 D OW1 SH AH0 S RHTF GIVHHBV IHIG\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==14){
      if(strcmp("S UW2 P ER0 K AE2 L AH0 F R AE1 JH AH0 L IH2 S T IH0 K EH2 K S P IY0 AE2 L AH0 D OW1 SH AH0 S FKJBDD HOUHDIUDKJ NKN UFI UCU DF\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==15){
      if(word==NULL){
        printf("\nPASS ");
      }else{
        printf("\nFAIL ");
      }
    }else if(tag==16){
      if(strcmp("A\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==17){
      if(strcmp("Z IH0 W IH1 K IY0\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }else if(tag==18){
      if(strcmp("?????\n",word)==0){
        printf("\nPASS");
      }else{
        printf("\nFAIL");
      }
    }
    return 0;
}

void rmLine(char * line){
  char * newline = strchr(line, '\n');
  if (line)
    *newline = '\0';
}

void runTest(int n){
  if (n==1){
  printf("\nTestcase 1: Line Length=29, Tag Length=29");
  parse("echo \"SUPERCALIFRAGILISTICEXPIALIDOCI\" | ./cmulookup testcases/testcase1",1);
  }else if (n==2){
    printf("\nTestcase 2: Line Length=47,Tag Length=33");
    parse("echo \"HONEYQWERTYUIOPASDFGHJKLZXCVBNMQW\" | ./cmulookup testcases/testcase2",2);
  }else if(n==3){
    printf("\nTestcase 3: Line Length =64, Tag Length=16");
    parse("echo \"HONNNEYYYYMOONNNNERS\" | ./cmulookup testcases/testcase3",3);
  }else if(n==4){
    printf("\nTestcase 4: Line Length=40, Tag Length=16");
    parse("echo \"HOOONEEEYMOOONS\" | ./cmulookup testcases/testcase4",4);
  }else if(n==5){
    printf("\nTestcase 5: Line Length=129, Tag Length=33");
    parse("echo \"HONEHONEHONEHONEHONEHONEHONEHONE\" | ./cmulookup testcases/testcase5",5);
  }else if(n==6){
    printf("\nTestcase 6: Line Length=0, Tag Length=0, Phoneme Length =0");
    parse("echo \" \" | ./cmulookup testcases/testcase6",6);
  }else if(n==7){
    printf("\nTestcase 7: Line Length=5, Tag Length =5, Phoneme Length = 0");
    parse("echo \"HONEY\" | ./cmulookup testcases/testcase7",7);
  }else if(n==8){
    printf("\nTestcase 8: Line Length =24, Tag Length = 0");
    parse("echo \" \" | ./cmulookup testcases/testcase8",8);
  }else if(n==9){
    printf("\nTestcase 9: Line Length =129, Tag Length = 32");
    parse("echo \"SUPERCALIFRAGILISTICEXPIALIDOCI\" | ./cmulookup testcases/testcase9",9);
  }else if(n==10){
    printf("\nTestcase 10: Line Length = 128, Tag Length = 35");
    parse("echo \"SUPERCALIFRAGILISTICEXPIALIDOCIOUS\" | ./cmulookup testcases/testcase10",10);
  }else if(n==11){
    printf("\nTestcase 11: Line Length = 64, Tag Length = 32");
    parse("echo \"SUPERCALIFRAGILISTICEXPIALIDOCI\" | ./cmulookup testcases/testcase11",11);
  }else if(n==12){
    printf("\nTestcase 12: Line Length = 13, Tag Length = 0");
    parse("echo \" \" | ./cmulookup testcases/testcase12",12);
  }else if(n==13){
    printf("\nTestcase 13: Line Length =128, Tag Length = 16");
    parse("echo \"SUPERCALIFRAGIS\" | ./cmulookup testcases/testcase13",13);
  }else if (n==14){
    printf("\nTestcase 14: Line Length = 128, tag Length=1");
    parse("echo \"S\" | ./cmulookup testcases/testcase14",14);
  }else if(n==15){
    printf("\nTestcase 15: Line Length = 6, Tag Length=6, Phoneme Length=0");
    parse("echo \"HONEY\" | ./cmulookup testcases/testcase15",15);
  }else if(n==16){
    printf("\nTestcase 16: Line Length=1, Tag Length=1");
    parse("echo \"A\" | ./cmulookup testcases/testcase16",16);
  }else if(n==17){
    printf("\nTestcase 17: Number of Lines=150,000");
    parse("echo \"ZYWICKI\" | ./cmulookup testcases/testcase17",17);
  }else if(n==18){
    printf("\nTestcase 18: Number of Lines = 150,001");
    parse("echo \"ZYWICKI\" | ./cmulookup testcases/testcase18",18);
  }
}
