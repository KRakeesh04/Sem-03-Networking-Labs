// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "mypcm.h"


// function prototypes
void run(asignal * inputsignal);
int powerOf(int num1, int num2);
int *dSignal ;
int duration;


int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);

    for (int i = 0; i < duration+1; i++)
    {
        printf("%d", dSignal[i]);
    }
    printf("\n");
    free(dSignal);

    free(inputsignal);
	return 0;
}

void run(asignal * inputsignal) 
{
	float A, omega, sigma, interval, encoderBits;

    // getting input
    scanf("%f %f %f %d %f %f", &A, &omega, &sigma, &duration, &interval, &encoderBits);
    inputsignal->A = A;
    inputsignal->omega = omega;
    inputsignal->sigma = sigma;
    inputsignal->duration = duration;

    // sampling the the analog signal
    float *samples = malloc((duration+1)*sizeof(float));
    sampler(samples, interval, *inputsignal);

    // quantizing the sample values
    int *pcmpulses = malloc((duration+1)*sizeof(int));
    int Qlevels = powerOf(2,encoderBits);
    quantizer(samples, pcmpulses, Qlevels, A);

    // encoding to digital signal
    dSignal = malloc((duration+1)*sizeof(int));
    encoder(pcmpulses, dSignal, encoderBits);
}

int powerOf(int num1, int num2)
{
    int result = 1;
    for (int i = 0; i < num2; i++)
    {
        result *= num1;
    }
    return result;
}
