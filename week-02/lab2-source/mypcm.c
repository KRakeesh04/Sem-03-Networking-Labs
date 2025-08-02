// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
//Add any necessary headers here
#include <math.h>

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:
extern int duration;



// implementation
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

