#include <stdio.h>
#include <float.h>

	float max_diff(const float *a, int n){
		float largest = FLT_MIN;		
		float smallest = FLT_MAX;
		int i;

		for (i=0;i<n;i++){
			if (a[i]>largest) largest = a[i];
			// printf("largest %.2f\n", largest);
			if (a[i]<smallest) smallest = a[i];
			// printf("smallest %.2f\n", smallest);
		}
		return largest-smallest;
	}

int main(void){
	float f[] = {1,2,3,4,5,6,7,8,9};
	printf("Largest - smallest of first %d numbers is : %.2f",5,max_diff(f,5));
}