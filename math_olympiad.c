#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int int_sort(const void *a,const void *b) {
	if(*(int*)a < *(int*)b) {
		return -1;
	}
	else if(*(int*)a == *(int*)b) {
		return 0;
	}
	return 1;
}

int int_pointer_sort(const void *a, const void *b) {
	if(**(int**)a < **(int**)b) {
		return -1;
	}
	else if(**(int**)a == **(int**)b) {
		return 0;
	}
	return 1;
}
int max_sum_drops(int x) {

	return pow(x, 2) - x + 1;
}

int main() {

	int num_of_dish;
	int *dishes;
	int **tmp_dishes;
	int *sum_drops;
	int i, j, k, times;
	int head, add_times, add_count;

	srand(time(NULL));
	printf("皿の数は？>");
	scanf("%d", &num_of_dish);
	dishes = (int*)malloc(num_of_dish * sizeof(int));
	sum_drops = (int*)malloc(max_sum_drops(num_of_dish) * sizeof(int));
	tmp_dishes = (int**)malloc(num_of_dish * sizeof(int*));

	for(times = 1;;times++) {
		for(;;) {
			for(i = 0;i < num_of_dish;i++) {
				dishes[i] = 0;
			}
	
			dishes[0] = 1;
			for(i = 0;i < (max_sum_drops(num_of_dish) - 1);i++) {
				dishes[(int)(((double)rand() / RAND_MAX) * (num_of_dish - 1) + 1)]++;
			}
			for(i = 0;i < num_of_dish;i++) {
				tmp_dishes[i] = &dishes[i];
			}
	
			qsort(tmp_dishes, num_of_dish, sizeof(int*), int_pointer_sort);

			for(i = 0;i < (num_of_dish - 1);i++) {
				if(*tmp_dishes[i] == *tmp_dishes[i + 1]) {
					break;
				} else if(i == (num_of_dish - 2) && *tmp_dishes[i] != *tmp_dishes[i + 1]) {
					goto success_rand;
				}
			}
		}

		success_rand:

		for(i = 0;i < max_sum_drops(num_of_dish);i++) {
			sum_drops[i] = 0;
		}

/*
		printf("num_of_drops:");
		for(i = 0;i < num_of_dish;i++) {
			printf("%d ", dishes[i]);
		}
		printf("\n");
*/

/*
		for(i = 0;i < 4;i++) { //足す回数
			for(j = 0;j < 5;j++) { //dishのカウンタ
				for(k = 0;k <= i;k++) { //足すのは何回目か
					sum_drops[i * 5 + j] += num_of_drops[(j + k) % 5];
				}
			}
		}
		for(i = 0;i < 5;i++) {
			sum_drops[20] += num_of_drops[i];
		}
*/
		for(head = 0;head < num_of_dish;head++) {
			for(add_times = 0;add_times < (num_of_dish - 1);add_times++) {
				for(add_count = 0;add_count <= add_times;add_count++) {
					sum_drops[head * (num_of_dish - 1) + add_times] += dishes[(head + add_count) % num_of_dish];
				}
			}
		}
		for(add_count = 0;add_count < num_of_dish;add_count++) {
			sum_drops[max_sum_drops(num_of_dish) - 1] += dishes[add_count];
		}

		qsort(sum_drops, max_sum_drops(num_of_dish), sizeof(int), int_sort);

/*
		printf("sum:");
		for(i = 0;i < max_sum_drops(num_of_dish);i++) {
			printf("%d ", sum_drops[i]);
		}
		printf("\n");
*/

		for(i = 0;i < max_sum_drops(num_of_dish);i++) {
			if(sum_drops[i] != i + 1) {
				break;
			} else if(i == (max_sum_drops(num_of_dish) -1)) {
				goto success;
			}
		}
	}

	success:
	printf("answer:");
	for(i = 0;i < num_of_dish;i++) {
		printf("%d ", dishes[i]);
	}
	printf("\n");
	printf("times:%d\n", times);

	return 0;
}

