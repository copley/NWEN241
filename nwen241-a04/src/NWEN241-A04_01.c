/*
 * NWEN241-A04_01.c
 *
 *  Created on: 4/05/2015
 *      Author: diego
 */

#include <time.h>
#include <stdio.h>

unsigned int sum1(unsigned int from, unsigned int to); /* recursion */
unsigned int sum2(unsigned int from, unsigned int to); /* iteration */
unsigned int sum3(unsigned int from, unsigned int to); /* algorithm */
unsigned int sumRec(unsigned int from, unsigned int to, unsigned int sum);
/* algorithm: sum(1..n) = n*(n+1)/2, sum(m..n) = sum(1..n) - sum(1..m-1) */

int main(void) {
	unsigned int s;
	unsigned from, to;
	double t1, t2;
	printf("Enter the fist integer:");
	scanf("%d", &from);
	printf("Enter the second integer:");
	scanf("%d", &to);
	t1 = clock();
	s = sum1(from, to);
	t2 = clock();
	printf("sum1=%d, %f seconds.\n", s, (t2 - t1) / CLOCKS_PER_SEC);
	t1 = clock();
	s = sum2(from, to);
	t2 = clock();
	printf("sum2=%d, %f seconds.\n", s, (t2 - t1) / CLOCKS_PER_SEC);
	t1 = clock();
	s = sum3(from, to);
	t2 = clock();
	printf("sum3=%d, %f seconds.\n", s, (t2 - t1) / CLOCKS_PER_SEC);
	return 0;
}

unsigned int sum1(unsigned int from, unsigned int to) {
	// recursion
	printf("Sum with recursion\n");
	unsigned int sum = 0;
	sum = sumRec(from, to, sum);
	return sum;
}

unsigned int sumRec(unsigned int from, unsigned int to, unsigned int sum){
	if (from == to) {
//		printf("%d %d\n",from, to);
		return sum+to;
	} else {
//		printf("%d %d\n",from, to);
		sum = sumRec(from+1, to, sum+from);
	}
	return sum; // should never reach here
}

unsigned int sum2(unsigned int from, unsigned int to) {
	// iteration
	unsigned int sum = 0;
//	printf("Sum with iterative\n");
		for (int i = 0; i<=(to-from);i++){
			sum = sum + from + i;
		}
	return sum;
}

unsigned int sum3(unsigned int from, unsigned int to) {
	// algorithm with mult and div
	/* algorithm: sum(1..n) = n*(n+1)/2, sum(m..n) = sum(1..n) - sum(1..m-1) */
	unsigned int sum1N = to*(to+1)/2;
	unsigned int sum1M = (from)*((from-1)/2);
	unsigned int sum = sum1N - sum1M;
	return sum;
}

