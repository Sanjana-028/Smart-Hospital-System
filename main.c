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

int specialtyQueueCount[NUM_SPECIALITIES] ={0,0,0,0};

const char *wardNames[NUM_WARDS] ={"General Ward","Paediatric Ward","Surgical Ward","ICU (Intensive Care Unit)"};
const float dailyBedRate[NUM_WARDS] ={3000.00,6000.00,12000.00,25000.00};
const int totalBedCapacity[NUM_WARDS] ={20,10,10,05};

/* bedOccupancy[wardIndex][bedIndex] :- 0=Available , 1=Occupied */
int bedOccupancy[NUM_WARDS][MAX_BEDS_PER_WARD];
int findAvailableBed(int wardIdx);

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
int findAvailableBed(int wardIdx);

float calculateWaitTime(int specialtyIdx);
float calculateSurCharge(int urgency,float baseFee);
float calculateWardCost(int admitted,int daysAdmitted,int wardIdx);
float calculateDiscount(int age,float grossTotal);

void printBillReceipt(int i);

void registerPatient();
void printPriorityList();




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

float calculateWaitTime(int specialtyIdx)
{
    return specialtyQueueCount[specialtyIdx] * (float) specialtyTimePerPatient[specialtyIdx];
}

float calculateSurCharge(int urgency,float baseFee)
{
    if (urgency ==2){
         return baseFee*0.20;
    }
    if (urgency ==3){
        return baseFee*0.50;
    }
    return 0.0;
}

float calculateWardCost(int admitted,int daysAdmitted,int wardIdx)
{
    if (!admitted){
        return 0.0;
    }
    return daysAdmitted*dailyBedRate[wardIdx];
}

float calculateDiscount(int age,float grossTotal)
{
    if (age < 5 || age > 65){
        return grossTotal*0.15;
    }
    return 0.0;
}

void printBillReceipt(int i)
{
    char patientID[16];
    sprintf(patientID,"PAT-%d\n",1000 + i+1);

    printf("===============================================================\n");
    printf("\n");
    printf("      King's Landing Smart Hospital Admission & The Bill\n");
    printf("\n");
    printf("===============================================================\n");
    printf("\n");
    printf("Patient ID    : %s\n", patientID);
    printf("Patient Name  : %s\n", patientName[i]);
    printf("Patient's Age : %d years\n", patientAge[i],(patientAge[i] < 5 || patientAge[i] > 65 )? "(15% Subsidy Eligible":"");
    printf("Specialty     : %s\n",namesOfSpecialty[patientSpecialtyIdx[i]]);
    if (patientAdmitted[i]){
        printf("Assigned Ward   : %s (Bed #%02d)\n", wardNames[patientWardIdx[i]],patientBedNo[i] +1);
    }
    else {
        printf("Assigned Ward   : outpatient (OPD)\n");
    }
    printf("Urgency Level : Level %d (%s)\n", patientUrgency[i], patientUrgency[i] ==3 ? "Critical": patientUrgency[i] ==2 ? "Urgent":"Normal");
    printf("-----------------------------------------------------------------\n");
    printf("\n");
    printf("Base Consulation Fee :LKR %.2f\n", patientBaseFee[i]);
    printf("Emergency Surcharge  :LKR %.2f\n", patientSurcharge[i]);
    printf("Ward Days Cost(%d days) :LKR %.2f\n", patientDaysAdmitted[i],patientWardCost[i]);
    printf("------------------------------------------------------------------\n");
    printf("\n");
    printf("Gross Total Bill     :LKR %.2f\n", patientGrossTotal[i]);
    printf("Age Subsidy Discount :LKR %.2f\n", patientDiscount[i]);
    printf("------------------------------------------------------------------\n");
    printf("\n");
    printf("Final Amount         :LKR %.2f\n",patientFinalAmount[i]);
    printf("Estimated Waiting Time : %.2f mins %s\n", patientWaitTime[i],patientWaitTime[i] ==0 ? "(Immediate  Attention)" : "");
    printf("\n");
    printf("Thank you!\nHave a nice day.\n");
    printf("==================================================================\n");
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


    patientWaitTime[i] = calculateWaitTime(patientSpecialtyIdx[i]);
    specialtyQueueCount[patientSpecialtyIdx[i]]++;

    patientBaseFee[i] =feesOfSpecialty[patientSpecialtyIdx[i]];
    patientSurcharge[i] =calculateSurCharge(patientUrgency[i],patientBaseFee[i]);
    patientWardCost[i] =calculateWardCost(patientAdmitted[i],patientDaysAdmitted[i],patientWardIdx[i]);
    patientGrossTotal[i] =patientBaseFee[i] + patientSurcharge[i] + patientWardCost[i];
    patientDiscount[i] =calculateDiscount(patientAge[i],patientGrossTotal[i]);
    patientFinalAmount[i] =patientGrossTotal[i] - patientDiscount[i];
}

void printPriorityList()
{
    if (patientCount == 0){
       printf("\nNo patients registered yet.\n");
       return;
    }
    int order[MAX_PATIENTS];
    for (int i=0;i < patientCount;i++){
        order[i]=i;
    }
    for (int i=1;i < patientCount;i++){
        int key=order[i];
        int keyUrgency=patientUrgency[i];
        int j=i-1;
        while (j >= 0 && patientUrgency[order[j]]< keyUrgency){
            order[j+1] =order[j];
            j--;
        }
        order[j+1] = order[j];
    }
    printf("\n=========== Patient's Priority List==============\n");
    printf("\n");
    for (int r=0;r < patientCount;r++){
        int i = order[r];
        printf("%2d. PAT-%-6d %-20s     urgency : Level %d      Final Bill :LKR %.2f\n", r+1,1000 +i+1,patientName[i],patientUrgency[i],patientFinalAmount[i]);
    }
    printf("\n");
    printf("===================================================\n");
}
