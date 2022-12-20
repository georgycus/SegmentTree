#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SegTree.h"

int main(int argc, char *argv[]) {
	int N=0, M=0;
	int i=0, n1=0, n2=0;
	char op[4];

	FILE *fpr, *fpw;

	if(argc == 3){
		fpr = fopen(argv[1], "r");
		
		if(fscanf(fpr, "%d %d", &N, &M)!=2){
			printf("Ошибка чтения 1\n");
		}
		
		//базовый вектор и вектор, который будет служить деревом
	int *v = (int *) malloc(sizeof(int)*(N));
	T *tree = (T *) malloc(sizeof(T)*(4*N+1));

		//читать числа из вектора
		for(i=1; i<=N; i++){
			if(fscanf(fpr, "%d", &v[i])!=1){
				printf("Ошибка чтения 2\n");
			}
		}

		BuildSegTree(tree, v, 1, 1, N);

		fpw = fopen(argv[2], "w");

		for(i=0; i<M; i++){
			if(fscanf(fpr, "%s %d %d", op, &n1, &n2)<=0){
				printf("Ошибка чтения 3\n");
			}

			if(strcmp(op, "Add")==0){
				add(tree, 1, 1, N, n1, n2);
			}else{
				if(strcmp(op, "Sub")==0){
					sub(tree, 1, 1, N, n1, n2);
				}else{
					if(strcmp(op, "Min")==0){
						fprintf(fpw, "%d\n", computeMin(tree, 1, 1, N, n1, n2));
					}else{
						if(strcmp(op, "Max")==0){
							fprintf(fpw, "%d\n", computeMax(tree, 1, 1, N, n1, n2));
						}else{
							if(strcmp(op, "Sum")==0){
								fprintf(fpw, "%d\n", computeSum(tree, 1, 1, N, n1, n2));
							}
						}
					}
				}
			}
		}

		fclose(fpw);
		fclose(fpr);
		
	free(v);
	free(tree);
		
	}else{
		printf("Ошибка ввода\n");
	}
	return 0;
}
