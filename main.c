#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SPECIALITIES 4

const char *namesOfSpecialty[NUM_SPECIALITIES] ={"genaral Practice (OPD)","Paediatrics","Cardiology","Neurology"};
const float feesOfSpecialty[NUM_SPECIALITIES] ={1500.00,2500.00,4500.00,5000.00};
const int specialtyTimePerPatient[NUM_SPECIALITIES] ={15,20,30,30};
const int specialtyDailyCap[NUM_SPECIALITIES] ={30,20,12,10};

int main()
{
    printf("King's Landing Smart Hospital System\n");
    return 0;
}
