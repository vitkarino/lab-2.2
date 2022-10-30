#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x); // function f(x)
void show_result(double a, double b, unsigned int n, double I); // show calculation result
double l_rect(double a, double b, unsigned int n); // Left rectangle method
double r_rect(double a, double b, unsigned int n); // Right rectangle method
double trapeze(double a, double b, unsigned int n); // Trapezoid rectangle method
double parabola(double a, double b, unsigned int n); // Simpson's Parabola method

int main() {

	unsigned int method = 0, n, N;
	double I, I1 = 0, I2 = 0;
	const double a = -4.5, b = 10, eps = 0.0001;

	printf("\nChoose calculating method:\n\t[1] Left Rectangles method\n\t[2] Right Rectangles method\n\t[3] Trapezoid method\n\t[4] Simpson's Parabola method\n\t Method = ");
	scanf("%d", &method);
	
	while (method < 1 || method > 4) {

		printf("\nChoose calculating method:\n\t[1] Left Rectangles method\n\t[2] Right Rectangles method\n\t[3] Trapezoid method\n\t[4] Simpson's Parabola method\n\t Method = ");
		scanf("%d", &method);

		if (method < 1 || method > 4) {
			printf("\nInvalid option, try again.\n");
		}
	}

	do {
		printf("\nEnter the number of partition n (n > 0)\n\tn = ");
		scanf("%d", &n);
	} while (n <= 0);

	switch (method) {

	case 1:

		I = l_rect(a, b, n);
		show_result(a, b, n, I);

		N = 0;
		do {
			N += 2;
			I1 = l_rect(a, b, N);
			I2 = l_rect(a, b, N + 2);
		} while (fabs(I2 - I1) > eps);
		
		printf("\nN = %u, I = %.5lf\n", N, I1);
		printf("\n+**********************************************+\n");

		break;

	case 2:
		I = r_rect(a, b, n);
		show_result(a, b, n, I);

		N = 0;
		do {
			N += 2;
			I1 = r_rect(a, b, N);
			I2 = r_rect(a, b, N + 2);
		} while (fabs(I2 - I1) > eps);

		printf("\nN = %u, I = %.5lf\n", N, I1);
		printf("\n+**********************************************+\n");

		break;

	case 3:
		I = trapeze(a, b, n);
		show_result(a, b, n, I);

		N = 0;
		do {
			N += 2;
			I1 = trapeze(a, b, N);
			I2 = trapeze(a, b, N + 2);
		} while (fabs(I2 - I1) > eps);
		
		printf("\nN = %u, I1 = %.5lf\n", N, I1);
		printf("\n+**********************************************+\n");

		break;

	case 4:
		I = parabola(a, b, n);
		show_result(a, b, n, I);

		N = 0;
		do {
			N += 2;
			I1 = r_rect(a, b, N);
			I2 = r_rect(a, b, N + 2);
		} while (fabs(I2 - I1) > eps);
		
		printf("\nN = %u, I1 = %.5lf\n", N, I1);
		printf("\n+**********************************************+\n");

		break;
	}
}

// left rectangle method calculation
double l_rect(double a, double b, unsigned int n) {

	double h;
	double x;
	double sum = 0;

	h = (b - a) / n;
	x = a;

	for (unsigned int i = 0; i < n - 1; i++) {

		sum += f(x);
		x += h;
	}

	return sum * h;
}

// right rectangle method calculation
double r_rect(double a, double b, unsigned int n) {

	double h;
	double x;
	double sum = 0;

	h = (b - a) / n;
	x = a;

	for (unsigned int i = 1; i <= n; i++) {

		sum += f(x);
		x += h;
	}

	return sum * h;
}

// trapezoid method calculation
double trapeze(double a, double b, unsigned int n) {

	double h;
	double x;
	double sum = 0;

	h = (b - a) / n;
	x = a + h;

	for (unsigned int i = 1; i <= n - 1; i++) {

		sum += (f(x) + f(x + h)) / 2;
		x += h;
	}

	return sum * h;
}

// Simpson's parabola method calculation
double parabola(double a, double b, unsigned int n) {

	double h;
	double x;
	double sum = 0;

	h = (b - a) / n;
	x = a;

	do {

		sum += 4 * f(x);
		x += h;

		if (x >= b) {

			sum += 2 * f(x);
			x += h;
		}
		
	} while (x < b);

	sum = (h / 3) * (sum + f(a) + f(b));
	return sum;
}

// function f(x)
double f(double x) {
	return pow(x, 2) * sin(x);
}

// show calculation results
void show_result(double a, double b, unsigned int n, double I) {
	system("cls");
	printf("\n+**********************************************+");
	printf("\n+~~~~ Result ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
	printf("\n+**********************************************+\n");

	printf("\na = %.2lf b = %.2lf n = %u integral = %.2lf", a, b, n, I);
}