#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SPECIALITIES 4
#define NUM_WARDS 4
#define MAX_BEDS_PER_WARD 20
#define MAX_PATIENTS 157
#define MAX_NAME_LEN 50



const char *namesOfSpecialty[NUM_SPECIALITIES] ={"General Practice (OPD)","Paediatrics","Cardiology","Neurology"};
const float feesOfSpecialty[NUM_SPECIALITIES] ={1500.00,2500.00,4500.00,5000.00};
const int specialtyTimePerPatient[NUM_SPECIALITIES] ={15,20,30,30};
const int specialtyDailyCap[NUM_SPECIALITIES] ={30,20,12,10};

const char *wardNames[NUM_WARDS] ={"General Ward","Paediatric Ward","Surgical Ward","ICU (Intensive Care Unit)"};
const float dailyBedRate[NUM_WARDS] ={3000.00,6000.00,12000.00,25000.00};
const int totalBedCapacity[NUM_WARDS] ={20,10,10,05};

/* bedOccupancy[wardIndex][bedIndex] :- 0=Available , 1=Occupied */
int bedOccupancy[NUM_WARDS][MAX_BEDS_PER_WARD];

int patientCount=0;

char patientName[MAX_PATIENTS][MAX_NAME_LEN];
int patientAge[MAX_PATIENTS];
int patientUrgency[MAX_PATIENTS]; /*1.Normal 2.Urgent 3.Critical*/
int patientSpecialtyIdx[MAX_PATIENTS];
int patientAdmitted[MAX_PATIENTS]; /*1=Yes, 0=No (OPD only)*/
int patientWardIdx[MAX_PATIENTS];
int patientBedNo[MAX_PATIENTS];
int patientDaysAdmitted[MAX_PATIENTS];
float patientBaseFee[MAX_PATIENTS];
float patientSurcharge[MAX_PATIENTS];
float patientWardCost[MAX_PATIENTS];
float patientGrossTotal[MAX_PATIENTS];
float patientDiscount[MAX_PATIENTS];
float patientFinalAmount[MAX_PATIENTS];
float patientWaitTime[MAX_PATIENTS];


void initbedOccupancy();

void registerPatient();



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

void registerPatient()
{
    int i=patientCount;
    printf("\n");
    printf("-------------------New Patient Registration--------------------\n");
    printf("\n");
    printf("Patient's Name(with initials): ");
    scanf("%[^\n]", patientName[i]);
    printf("Patient's Age: ");
    scanf("%d", &patientAge[i]);
    printf("Triage Level (1=Normal, 2=Urgent, 3=Critical): ");
    scanf("%d", &patientUrgency[i]);
    printf("Specialty (");
    for (int s=0;s < NUM_SPECIALITIES;s++)
    {
        printf("%d= %s", s +1,namesOfSpecialty[s]);
    }
    printf("): ");
    int specialtyID;
    scanf("%d", &specialtyID);
    patientSpecialtyIdx[i] = specialtyID - 1;
}
