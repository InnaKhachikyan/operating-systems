#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int number_of_students;

	printf("Enter the number of students: ");
	if(scanf("%d", &number_of_students) != 1) {
		printf("Reading input failed\n");
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
