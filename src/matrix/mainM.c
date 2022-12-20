#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include <sys/time.h>

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);

	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main(int argc, char *argv[]) {
	int N=0, M=0;
	int i=0, n1=0, n2=0;
	char op[4];
	
// указатели для чтения и записи в файлы
// вход и выход
	FILE *fpr, *fpw;

	if(argc == 3){
		fpr = fopen(argv[1], "r");
		
		if(fscanf(fpr, "%d %d", &N, &M)!=2){
			printf("Ошибка чтения N и M\n");
		}
		
// прерываем программу, если N и M имеют значения
// вне указанных пределов
		if((N<1 || N>1000000) || (M<1 || M>10000000))
			return 0;
		
		int *V = (int *) malloc((N+1)*sizeof(int));
		Matrix matrix;
    	createMatrix(&matrix, N+1);

// массив начинается с позиции 1, а не с 0
		for(i=1; i<=N; i++){
			if(fscanf(fpr, "%d", &V[i])!=1){
				printf("Ошибка: Нет элементов для массива\n");
			}
		}

//обрабатываем массив с кортежами, соответствующими диапазонам

		processMatrix(&matrix, V, N);

		fpw = fopen(argv[2], "w");

		for(i=0; i<M; i++){
			if(fscanf(fpr, "%s %d %d", op, &n1, &n2)<=0){
				printf("Ошибка: отсутствуют операции\n");
			}
// выполнение операций
			if(strcmp(op, "Add")==0){
				addMatrix(&matrix, V, N, n1, n2);
			}else{
				if(strcmp(op, "Sub")==0){
					subMatrix(&matrix, V, N, n1, n2);
				}else{
					if(strcmp(op, "Min")==0){
						fprintf(fpw, "%d\n", matrix.data[n1-1][n2-1].min);
					}else{
						if(strcmp(op, "Max")==0){
							fprintf(fpw, "%d\n", matrix.data[n1-1][n2-1].max);
						}else{
							if(strcmp(op, "Sum")==0){
								fprintf(fpw, "%d\n", matrix.data[n1-1][n2-1].sum);
							}
						}
					}
				}
			}
		}
		fclose(fpw);
		fclose(fpr);

		freeMatrix(&matrix);
	}else{
		printf("Ошибка ввода\n");
	}
	return 0;
}