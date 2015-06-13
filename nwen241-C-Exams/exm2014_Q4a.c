#include <math.h>

typedef struct student {
	int id;
	int age;
	char gender;
} Student;

int pack(Student *);

int pack(Student *s){
	int n = 0;
	n |= (s->gender == 'M' ? 1:0);
	n |= (s->age<<1);
	n |= (s->id<<8);
	return n;
}

int main(void){
	Student s;
	s.gender = 'M';
	s.age = 13;
	s.id = 20302;
}