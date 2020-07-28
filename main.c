

//  Created by Andrei Rusu on 06/05/2019.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Function Prototypes
float getCapVal(void);
float getIndVal(void);
int printArrInt(int *arr, int size);
float* getFreqArr(void);
float* getCapArr(float *userCap);
float* getIndArr(float *userInd);
float* getMatrix(float *freqArr, float *capArr, float *indArr, float *attArr, float *attdBArr);
float printArr(float *arr, int size);
float* getAttenuationArr(float *userInd, float *userCap);
float* getAttenuationDBArr(float *attenuationArr);


int main(void) {
    //Declaration of variables
    float capVal, indVal;
    float *capArray;
    float *indArray;
    float *attenuationArray;
    float *attenuationDBArray;
    float *freqArray;

    //Calling functions in order to pass down data to create the matrix
    capVal = getCapVal();
    indVal = getIndVal();
    freqArray = getFreqArr();
    capArray = getCapArr(&capVal);
    indArray = getIndArr(&indVal);
    attenuationArray = getAttenuationArr(&indVal, &capVal);
    attenuationDBArray = getAttenuationDBArr(attenuationArray);
    getMatrix(freqArray, capArray, indArray, attenuationArray, attenuationDBArray);

    return 0;
}

//collect inductance value from user input
float getIndVal()
{
    float indVal, *ptrI;
    printf("Enter your inductance value in mH: \n");
    scanf("%f", &indVal);
    ptrI = &indVal;
    *ptrI= *ptrI/ 1000;
    return *ptrI;
}

//Collect capacitance value from user input
float getCapVal()
{
    float capVal, *ptrC;
    printf("Enter your capacitance value in mF: \n");
    scanf("%f", &capVal);
    ptrC = &capVal;
    *ptrC = *ptrC/1000000;
    return *ptrC;
}
//Create  frequency  array.
float* getFreqArr(void)
{
    static float freqArr[18];
    int i, j;
    float *ptrArr;
    ptrArr = &freqArr[0];

    for (i=0; i <= 9; i++)
    {
        freqArr[i] = ((i+1)*100);
        //        printf("\nValue is: %d\n", *(ptrArr+ i));
    }
    for (j=10; j <= 18; j++)
    {
        freqArr[j] = ((j-8)*1000);
        //        printf("\nValue is: %d\n", *(ptrArr+ j));

    }
    return freqArr;
}

//Create capacitance array.
float* getCapArr(float *userCap)
{
    static float capArr[17];
    float *ptrArr;
    ptrArr = capArr;
    int i,j;

    for (i = 0; i <= 9; i++)
    {
        capArr[i] = (1 / (2 * M_PI * (*userCap) * ((i+1) * 100)));
        //printf("\nValue is: %.3f\n", *(ptrArr+ i));
    }

    for (j = 10; j<=17; j++)
    {
        capArr[j] =(1 / (2 * M_PI * (*userCap) * ((j-8)* 1000)));
        //printf("\nValue is: %.3f\n", *(ptrArr+ j));
    }

    return &capArr[0];
}


float* getIndArr(float *userInd)
{
    static float indArr[17];
    float *ptrArr;
    ptrArr = indArr;
    int i, j;

    for (i = 0; i <= 9; i++)
    {
        indArr[i] = (2 * M_PI * (*userInd) * ((i+1) * 100));
        //printf("\nValue is: %.3f\n", *(ptrArr+ i));
    }

    for (j = 10; j<=17; j++)
    {
        indArr[j] =(2 * M_PI * (*userInd) * ((j-8)* 1000));
        //printf("\nValue is: %.3f\n", *(ptrArr+ j));
    }
    //return memeory address of 1st element in array.
    return &indArr[0];

}

float* getAttenuationArr(float *userInd, float *userCap )
{
    static float attenuationArr[17];
    float *ptrArr, omega;

    ptrArr = attenuationArr;
    int i, j;
    //Iterates over values in order to populate attenuationArr with user input values.
    for (i = 0; i <= 9; i++) {
        omega = (2 * M_PI * ((i+1) * 100) );
        attenuationArr[i] = fabsf(1/(1 - (omega*omega) * (*userInd) * (*userCap)));
        //printf("\nValue is: %.3f\n", *(ptrArr+ i));
    }
    for (j = 10; j <= 17; j++) {
        omega = (2 * M_PI * ((j-8) * 1000) );
        attenuationArr[j] = fabsf(1/(1 - (omega*omega) * (*userInd) * (*userCap)));
        //printf("\nValue is: %.3f\n", *(ptrArr+ j));
    }
    //return memeory address of 1st element in array.
    return &attenuationArr[0];
}

float* getAttenuationDBArr(float *attenuationArr )
{
    static float  attenuationDBArr[17], a;
    float *ptrArr;
    int i;

    ptrArr = attenuationDBArr;
    //Iterates over values in order to populate getAttenuationDBArr array with values from attenuationArr.
    for (i=0; i<=17; i++)
    {
        a = *(attenuationArr+i);
        //TO TEST VALUE OF a UNCOMMENT:
        //printf("Value of a is: %f", *(attenuationArr+ i));
        attenuationDBArr[i] = fabs(-20 * log10(a));
        //TO TEST VALUES OF attenuationDBArr:
        //printf("\nValue is: %.3f\n", *(ptrArr+ i));
    }
    //return memeory address of 1st element in array.
    return &attenuationDBArr[0];
}

//ASSIGNS AND PRINTS MATRIX
float* getMatrix(float *freqArr, float *capArr, float *indArr, float *attArr, float *attdBArr)
{
    static float matrix[5][18] = {{0}};
    float *ptrFreqArr, *ptrCapArr, *ptrIndArr, *ptrAttArr, *ptrArrDBArr;
    float (*p)[18] = matrix;
    int i;
    int row, col;


    ptrFreqArr = freqArr;
    ptrCapArr = capArr;
    ptrIndArr = indArr;
    ptrAttArr = attArr;
    ptrArrDBArr = attdBArr;
    //ASSIGNING VALUES TO 2-D ARRAY:matrix
    for (i= 0; i<18; i++)
    {
        *(*(p)+ i ) = *(ptrFreqArr + i);

    }
    for (i = 0; i<18; i++)
    {
        *(*(p+1) +i) = *(ptrCapArr + i);
        //        To test:
        //        printf("printing induc: %.3f |", *(*(p+1)+ i));

    }
    for (i = 0; i<18; i++)
    {
        *(*(p+2)+i) = *(ptrIndArr + i);
        //        To test:
        //        printf("printing capa: %.3f |",   *(*(p+2) + i)    );
        //        printf("\n");
    }
    for (i = 0; i<18; i++)
    {
        *(*(p+3)+i) = *(ptrAttArr + i);
        //        To test:
        //        printf("printing ATTENUATION: %.3f |",   *(*(p+2) + i)    );
        //        printf("\n");
    }
    for (i = 0; i<18; i++)
    {
        *(*(p+4)+i) = *(ptrArrDBArr + i);
        //        To test:
        //        printf("printing ATTENUATION2: %.3f |",   *(*(p+2) + i)    );
        //        printf("\n");
    }
    //PRINTING MATRIX
    printf("\t\t\t\t\t\t\t ****University of Brighton****\n");
    printf("\t\t\t\t\t\t\t Division of Mathematics and Computing\n");
    printf("\n");
    printf("Student Name: Andrei Rusu\n");
    printf("\n");
    printf("\tFrequency (Hz)\t\tCapacitor Reactance(Xc)\t\tInductive Reactance(XL)\t\tAttenuation(Vout/Vin)\t\tAttenuation(dB)\n");
    printf("------------------\t\t-----------------------\t\t----------------------\t\t--------------------\t\t------------------\n");


    for (row = 0; row < 18; row++) {
        for (col = 0; col < 5; col++)
        {
            printf("\t\t  %.3f \t\t\t", matrix[col][row]);
        }
        printf("\n\n");
    }

    //Control FLow to Save the File

    FILE *ptrFile = NULL;
    char filename[30];
    char userAns;


    printf("Would you like to save the file?\n Type y for yes:\n");
    scanf("%c", &userAns);
    if(userAns == 'y')
    {

        if ( ptrFile != NULL )
        {
            printf("Please specify the name of the file: ");
            fscanf(ptrFile,"%c", filename);
            ptrFile = fopen(filename, "w");


            fprintf(ptrFile,"\t\t\t\t\t\t\t ****University of Brighton****\n");
            fprintf(ptrFile,"\t\t\t\t\t\t\t Division of Mathematics and Computing\n");
            fprintf(ptrFile,"\n");
            fprintf(ptrFile,"Student Name: Andrei Rusu\n");
            fprintf(ptrFile,"\n");
            fprintf(ptrFile,"\tFrequency (Hz)\t\tCapacitor Reactance(Xc)\t\tInductive Reactance(XL)\t\tAttenuation(Vout/Vin)\tAttenuation(dB)\n");
            fprintf(ptrFile,"------------------\t\t------------------\t\t------------------\t\t------------------\t\t------------------\n");


            for (row = 0; row < 18; row++)
            {
                for (col = 0; col < 5; col++)
                {
                    fprintf(ptrFile,"\t\t  %.3f \t\t", matrix[col][row]);
                }
                fprintf(ptrFile,"\n");

            }

            fputs(filename, ptrFile);
            fclose(ptrFile);
            printf("File write was successful\n");
        }else
        {
            printf("File already saved!");
        }
    }
    return 0;
}
