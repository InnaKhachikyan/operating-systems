#include <stdio.h>
#include <stdlib.h>

#define MAX_GROUP_SIZE 40
int main(void) {

	int number_of_students;

	printf("Enter the number of students: ");
	if(scanf("%d", &number_of_students) != 1) {
		printf("Reading input failed\n");
		return 1;
	}

	if(number_of_students <= 0 || number_of_students > MAX_GROUP_SIZE) {
		printf("Invalid number of students\n");
		return 1;
	}

	double *grades = (double*)malloc(sizeof(double)*number_of_students);
	if(!grades) {
		perror("malloc");
		return 1;
	}

	printf("Enter the grades: ");
	for(int i = 0; i < number_of_students; i++) {
		if(scanf("%lf", &grades[i]) != 1) {
			printf("Reading input failed\n");
			free(grades);
			grades = NULL;
			return 1;
		}
		if(grades[i] < 0 || grades[i] > 100) {
			printf("Invalid grade input\n");
			free(grades);
			grades = NULL;
			return 1;
		}
	}

	double lowest = 100;
	double highest = 0;

	for(int i = 0; i < number_of_students; i++) {
		if(grades[i] < lowest) {
			lowest = grades[i];
		}
		if(grades[i] > highest) {
			highest = grades[i];
		}
	}

	printf("Highest grade: %f\n", highest);
	printf("Lowest grade: %f\n", lowest);

	free(grades);
	grades = NULL;

	return 0;
}
