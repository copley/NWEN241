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
	if (h->scale == imperial){
		h->reading.metres = h->reading.feetandinches.feet*0.3048 + h->reading.feetandinches.inches*0.0254;
		h->scale = metric;
	}
}

int main(void){
	Height h;
	Value val;
	FeetAndInches feet;
	feet.feet = 3;
	feet.inches = 1;
	printf("\nValue in feet and inches: %d\',%d\'\'\n", feet.feet, feet.inches);
	val.feetandinches = feet;
	h.scale = imperial;
	h.reading = val;
	tometres(&h);
	printf("Value in metres: %.2f\n", h.reading.metres);
}
