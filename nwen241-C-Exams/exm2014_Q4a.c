#include <math.h>

typedef struct student {
	int id;
	int age;
	char gender;
} Student;

int pack(Student *);

int pack(Student *s){
	// make a new int n, which is used to pack . Initalise to 0 so we cna use | operator
	int n = 0;
	// make a mask for gender, one for age and one for id
	int maskAge = pow(2,7);
	int maskId = pow(2,24);
	// add to n bitwise operation with masks
	n |= (s->gender == 'M' ? 1:0);
	n |= (s->age<<1);
	n |= (s->id<<8);
	return 1;
}


int main(void){
	Student s;
	s.gender = 'M';
	s.age = 13;
	s.id = 20302;
}