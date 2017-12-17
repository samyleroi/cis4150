#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gpacalc.h"

int main(){
  StudentGPAInfo *info = gpaCalcInit("Mark","001");
  gpaCalcAddNumericGrade(info,"t",86);
  gpaCalcAddNumericGrade(info,"t",78);
  gpaCalcAddNumericGrade(info,"t",94);
  float avg = getTermGPA(info, "t");
  if(avg == 3.866667){
    printf("PASS\n");
  }else{
    printf("FAIL\n");
  }
  printf("Expected Average: %f\n",avg);
}
