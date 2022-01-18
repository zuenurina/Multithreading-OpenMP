#include<stdio.h>
#include <stdlib.h>
#include<omp.h>
#include <time.h>
#define ARRAYSIZE 100

int main(int argc, const char* argv[]) {

	int i, imin, imax, totalThread, one = 0, two = 0, three = 0, four = 0, five = 0, six = 0;
	double min, max;
	int total = 0;
	double a[ARRAYSIZE], b[ARRAYSIZE], c[ARRAYSIZE], d[ARRAYSIZE], e[ARRAYSIZE];
	double f[ARRAYSIZE], y[ARRAYSIZE];
	double array1[ARRAYSIZE], array2[ARRAYSIZE], array3[ARRAYSIZE], array4[ARRAYSIZE];
	double array5[ARRAYSIZE], array6[ARRAYSIZE];

	srand(time(NULL));

	for (i = 0; i < ARRAYSIZE; i++) {
		a[i] = rand() % 100 + 1;
		b[i] = rand() % 50 + 10;
		c[i] = rand() % 10 + 1;
		d[i] = rand() % 50 + 1;
		e[i] = rand() % 5 + 1;
		f[i] = rand() % 80 + 10;
	}

#pragma omp parallel num_threads(2)
	{
#pragma omp for reduction (+:total)
		for (i = 0; i < ARRAYSIZE; i++) {
#pragma omp critical
			y[i] = (a[i] * b[i]) + c[i] + (d[i] * e[i]) + f[i] / 2;
			printf("y[%d] = %.2f\n", i, y[i]);
		}

#pragma omp for reduction (+:total)
		for (i = 0; i < ARRAYSIZE; i++) {
#pragma omp critical
			if (a[one] > 0 && b[one] > 0) {
				array1[one] = a[one] * b[one];
			}
			else {
				array1[one] = 0;
			}
			if (array1[one] != 0) {
				printf("Value of A * B: %.2f \n", array1[one]);
			}
			one++;
		}

#pragma omp for reduction (+:total)
		for (i = 0; i < ARRAYSIZE; i++) {
#pragma omp critical
			if (d[two] > 0 && e[two] > 0) {
				array2[two] = d[two] * e[two];
			}
			else {
				array2[two] = 0;
			}
			if (array2[two] != 0) {
				printf("Value of D * E: %.2f \n", array2[two]);
			}
			two++;
		}

#pragma omp for reduction (+:total)
		for (i = 0; i < ARRAYSIZE; i++) {
#pragma omp critical
			if (f[three] > 0) {
				array3[three] = f[three] / 2;
			}
			else {
				array3[three] = 0;
			}

			if (array3[three] != 0) {
				printf("Value of F / 2: %.2f \n", array3[three]);
			}
			three++;
		}

#pragma omp for reduction (+:total)
		for (i = 0; i < ARRAYSIZE; i++) {
#pragma omp critical
			if (c[four] > 0) {
				array4[four] = (array1[four] + c[four]);
			}
			else {
				array4[four] = 0;
			}

			if (array3[four] != 0) {
				printf("Value of (A * B) + C: %.2f \n", array4[four]);
			}
			four++;
		}

#pragma omp for reduction (+:total)
		for (i = 0; i < ARRAYSIZE; i++) {
#pragma omp critical
			array5[five] = (array4[five] + array2[five]);
			printf("Value of (A * B) + C + (D * E): %.2f \n", array5[five]);
			five++;
		}

#pragma omp for reduction (+:total)
		for (i = 0; i < ARRAYSIZE; i++) {
#pragma omp critical
			array6[six] = (array5[six] + array3[six]);
			printf("Value of (A * B) + C + (D * E) + F / 2: %.2f \n", array6[six]);
			six++;
		}

#pragma omp for reduction (+:total)
		for (i = 0; i < ARRAYSIZE; i++) {
#pragma omp critical
			if (i == 0) {
				min = array6[i];
				imin = i;
			}
			else {
				if (array6[i] < min) {
					min = array6[i];
					imin = i;
				}
			}
		}

#pragma omp for reduction (+:total)
		for (i = 0; i < ARRAYSIZE; i++) {
#pragma omp critical
			if (i == 0) {
				max = array6[i];
				imax = i;
			}
			else {
				if (array6[i] > max) {
					max = array6[i];
					imax = i;
				}
			}
		}
	}

#pragma omp sections
	{
#pragma omp section
		{
			printf("Min y[%d] = %.2f\n", imin, min);
		}
#pragma omp section
		{
			printf("Max y[%d] = %.2f\n", imax, max);
		}
	}
	return 0;
}