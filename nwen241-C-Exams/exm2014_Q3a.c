#include <stdio.h>


typedef enum {metric, imperial} Scale;

typedef struct {
	int feet;
	int inches;
} FeetAndInches;

typedef union{
	float metres;
	FeetAndInches feetandinches;
} Value;

typedef struct {
	Scale scale;
	Value reading;
} Height;

void tometres(Height *h){
	// convert imperial to metres
	if (h->scale == imperial){
		float metres = h->reading.feetandinches.feet*0.3048 + h->reading.feetandinches.inches*0.0254;
		printf("%f",metres);
		Value val;
		val.metres = metres;
		h->reading = val;
	}
}

int main(void){
	Height h;
	Value val;
	FeetAndInches feet;
	feet.feet = 3;
	feet.inches = 1;
	val.feetandinches = feet;
	h.scale = imperial;
	h.reading = val;
	tometres(&h);
}
