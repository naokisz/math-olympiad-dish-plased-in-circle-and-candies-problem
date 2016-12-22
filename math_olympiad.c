#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int int_sort(const void *a,const void *b) {
	if(*(int*)a < *(int*)b) {
		return -1;
	}
	else if(*(int*)a == *(int*)b) {
		return 0;
	}
	return 1;
}

int main() {

	int num_of_drops[5];
	int sum_drops[21];
	int space_of_two;
	int i, j, k, times;

	srand(time(NULL));
	for(times = 1;;times++) {

		num_of_drops[0] = 1;
		space_of_two = (int)(((double)rand() / RAND_MAX) * 2) + 2;
		num_of_drops[space_of_two] = 2;

		num_of_drops[1] = (int)(((double)rand() / RAND_MAX) * 16) + 1;
		num_of_drops[4] = (int)(((double)rand() / RAND_MAX) * (17 - num_of_drops[1])) + 1;
		if(space_of_two == 2) {
			num_of_drops[3] = 18 - num_of_drops[1] - num_of_drops[4];
		} else {
			num_of_drops[2] = 18 - num_of_drops[1] - num_of_drops[4];
		}

		for(i = 0;i < 21;i++) {
			sum_drops[i] = 0;
		}

		printf("num_of_drops:");
		for(i = 0;i < 5;i++) {
			printf("%d ", num_of_drops[i]);
		}
		printf("\n");

		for(i = 0;i < 4;i++) {
			for(j = 0;j < 5;j++) {
				for(k = 0;k <= i;k++) {
					sum_drops[i * 5 + j] += num_of_drops[(j + k) % 5];
				}
			}
		}
		for(i = 0;i < 5;i++) {
			sum_drops[20] += num_of_drops[i];
		}

		qsort(sum_drops, 21, sizeof(int), int_sort);

		for(i = 0;i < 21;i++) {
			if(sum_drops[i] != i + 1) {
				break;
			} else if(i == 20) {
				goto success;
			}
		}
	}

	success:
	printf("answer:");
	for(i = 0;i < 5;i++) {
		printf("%d ", num_of_drops[i]);
	}
	printf("\n");
	printf("times:%d\n", times);

	return 0;
}

