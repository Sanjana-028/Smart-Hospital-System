#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SPECIALITIES 4
#define NUM_WARDS 4
#define MAX_BEDS_PER_WARD 20


const char *namesOfSpecialty[NUM_SPECIALITIES] ={"Genaral Practice (OPD)","Paediatrics","Cardiology","Neurology"};
const float feesOfSpecialty[NUM_SPECIALITIES] ={1500.00,2500.00,4500.00,5000.00};
const int specialtyTimePerPatient[NUM_SPECIALITIES] ={15,20,30,30};
const int specialtyDailyCap[NUM_SPECIALITIES] ={30,20,12,10};

const char *wardNames[NUM_WARDS] ={"Genaral Ward","Paediatric Ward","Surgical Ward","ICU (Intensive Care Unit)"};
const float dailyBedRate[NUM_WARDS] ={3000.00,6000.00,12000.00,25000.00};
const int totalBedCapacity[NUM_WARDS] ={20,10,10,05};

/* bedOccupancy[wardIndex][bedIndex] :- 0=Available , 1=Occupied */
int bedOccupancy[NUM_WARDS][MAX_BEDS_PER_WARD];


void initbedOccupancy();


int main()
{
    initbedOccupancy();

    return 0;
}

void initbedOccupancy()
{
    for (int w=0;w < NUM_WARDS;w++){
        for (int b=0;b < MAX_BEDS_PER_WARD;b++){
            bedOccupancy[w][b] = 0;
        }
    }
}

void printBedStatus()
{
    printf("=================== Bed Occupancy Status ===================\n");
    for (int w=0;w < NUM_WARDS;w++){
        int occupied =0;
        printf("\n%s (Capacity: %d)\n[",wardNames[w],totalBedCapacity[w]);
        for (int b =0;b < totalBedCapacity;b++){
            printf("%d",bedOccupancy[w][b]);
            if (bedOccupancy[w][b] ==1)
                occupied++;
        }
        printf("] -> %d/%d occupied (%.1f%%)\n",occupied,totalBedCapacity[w],(occupied*100.0)/totalBedCapacity[w]);
    }
    printf("=============================================================\n");
}
int findAvailableBed(int wardIdx)
{
    for (int b=0;b <totalBedCapacity[wardIdx];b++){
        if(bedOccupancy[wardIdx][b] ==0)
            return b;
    }
    return -1;
}
