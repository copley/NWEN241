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
