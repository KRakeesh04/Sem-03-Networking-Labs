#include "mypcm.h"


/****************************************************************************************************************************************************/

// Additional header files 
#include <math.h>

// Global variable
int duration;

// function prototypes
void run(asignal * inputsignal);
int powerOf(int num1, int num2);

// Implement functions here
int powerOf(int num1, int num2)
{
    int result = 1;
    for (int i = 0; i < num2; i++)
    {
        result *= num1;
    }
    return result;
}


float analog_signal_generator(asignal signal, int t)
{
	double result = signal.A * sin(signal.omega * t + signal.sigma);
	return result;
}

void sampler(float *samples, int interval, asignal signal)
{
	for (int i = 0; i < signal.duration+1; i+=interval)
    {
        samples[i] = analog_signal_generator(signal,i);
    }
}

// void quantizer1(float *samples, int *pcmpulses, int levels)
// {
// 	//TODO
// }

void quantizer(float *samples, int *pcmpulses, int levels, float A)
{
	
	for (int i = 0; i < duration+1; i++)
	{
		int level = floor( levels * fabs((samples[i] + A) / (2*A)) );
		if (level >= levels)
		{
			level = levels - 1;
		}
		
		pcmpulses[i] = level;
	}
	
}

void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
	int ptr = 0;
	for (int i = 0; i < duration+1; i++)
	{
		// Deci2Bin(pcmpulses[i], &dsignal, encoderbits);
		int *tempBits = malloc(encoderbits * sizeof(int));

		// Initialize to zeros
		for (int k = 0; k < encoderbits; k++) 
		{
			tempBits[k] = 0;
		}

		// Fill bits from LSB to MSB at correct position
		int j = encoderbits-1;
		int pcmpulse = pcmpulses[i];
		while (pcmpulse > 0) 
		{
			tempBits[j] = pcmpulse % 2;
			pcmpulse /= 2;
			j--;
		}

		for (int k = 0; k < encoderbits; k++)
		{
			dsignal[ptr] = tempBits[k];
			ptr++;
		}
		
		free(tempBits);
	}
}




//-------------------------------------------------------------

int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    
    //call any other function here

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
    int count = (duration+1)*encoderBits;
    int *dSignal = malloc(count*sizeof(int));
    encoder(pcmpulses, dSignal, encoderBits);

    // printing the digital signal
    for (int i = 0; i < count; i++)
    {
        printf("%d", dSignal[i]);
    }
    printf("\n");

    free(samples);
    free(pcmpulses);
    free(dSignal);
}

/****************************************************************************************************************************************************/