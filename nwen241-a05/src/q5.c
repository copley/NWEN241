/*
 * q5.c
 *
 *  Created on: 19/05/2015
 *      Author: diego
 */

#include <stdio.h>
/* Note: Program assumes years are in the same century. */

struct date {
	int month, day, year;
};

int compare_dates(struct date d1, struct date d2);
void put_date(struct date d);
int check_date(struct date d);

int main(void) {
	struct date d1, d2;

	printf("Enter first date (mm/dd/yy): ");
	/* for you to complete */
	scanf("%d/%d/%d", &d1.month, &d1.day, &d1.year);

	printf("Enter second date (mm/dd/yy): ");
	/* for you to complete */
	scanf("%d/%d/%d", &d2.month, &d2.day, &d2.year);

	// chceck dates
	if (check_date(d1) || check_date(d2) < 0 ){
	printf("Invalide dates.");
		return -1;
	}

	int a = compare_dates(d1, d2);

	if (a < 0) {
		put_date(d1);
		printf(" is earlier than ");
		put_date(d2);
		printf("\n");
	} else if (a > 0) {
		put_date(d2);
		printf(" is earlier than ");
		put_date(d1);
		printf("\n");
	} else {
		printf("Dates are equal !");
	}

	return 0;
}

int check_date(struct date d){
	if (d.year < 0 || d.year > 99) {
		return -1;
	}
	if (d.month < 1 || d.month > 12){
		return -1;
	}
	if (d.day < 1 || d.day > 31){
		return -1;
	}
	return 0;
}

int compare_dates(struct date d1, struct date d2) {
	if (d2.year < d1.year) {
		return 1;
	} else if (d2.year > d1.year) {
		return -1;
	} else { // same year
		if (d2.month < d1.month) {
			return 1;
		} else if (d2.month > d1.month) {
			return -1;
		} else { // same month
			if (d2.day < d1.day) {
				return 1;
			} else if (d2.day > d1.day) {
				return -1;
			} else { // same day !!
				return 0;
			}
		}
	}
}

void put_date(struct date d) {
	printf("%d/%d/%.2d", d.month, d.day, d.year);
}

