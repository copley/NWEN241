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

void printheight(Height h){
	if (h.scale == imperial){
		printf("Imperial scale: %d feet %d inches\n",h.reading.feetandinches.feet, h.reading.feetandinches.inches);
	} else {
		printf("Metric scale: %.2f\n", h.reading.metres);
	}
}

void tometres(Height *h){
	if (h->scale == imperial){
		float m = (h->reading.feetandinches.feet*12 + h->reading.feetandinches.inches)*0.0254;
		h->scale = metric;
		h->reading.metres = m;
	}
}

int main(void){
	Height h;
	h.scale = imperial;
	Value v;
	v.feetandinches.feet = 3;
	v.feetandinches.inches = 2;
	h.reading = v;
	printheight(h);
	tometres(&h);
	printheight(h);
}