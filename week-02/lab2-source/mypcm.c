// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
//Add any necessary headers here

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:
void Deci2Bin(int pcmpulse, int *bin, int encoderBits);
int mergeTwoNumbers(int a, int b);


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
		pcmpulses[i] = levels * floor( fabs( (samples[i] + A)/(2*A) ) );
	}
	
}
void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
	//TODO
}