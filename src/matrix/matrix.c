#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

// Размещаем массив. Размер определяется в структуре, чтобы иметь возможность перемещаться
// массив напрямую, без дополнительных параметров
void createMatrix(Matrix *matrix, int size) {
    matrix->size = size;
    matrix->data = (T**) calloc(matrix->size, sizeof(T*));
 
    int i;
    for (i = 0; i < matrix->size; i++) {
        matrix->data[i] = (T*) calloc(matrix->size, sizeof(T));
    }
}

// Вычисление минимума, максимума и суммы диапазона
T 	SumMinMax(int v[], int n1, int n2){
	int i=0;
	T t;
	
	t.sum = 0;
	t.min = v[n1]; // инициализируем минимум первым значением диапазона
	t.max = v[n1]; 
	
	for(i=n1; i<=n2; i++){
		if(v[i]>t.max){
			t.max = v[i]; // максимум
		}else{
			if(v[i]<t.min){
				t.min = v[i]; // минимум
			}
		}
		t.sum += v[i]; // сумма
	}
	return t; //возвращает кортеж
}

// Строим массив с кортежами (минимум, максимум, сумма)
void processMatrix(Matrix *matrix, int v[], int size){
	int i=0, j=0;
	
// обход позиций, где i<=j вычисление кортежей
// соответствующий рассматриваемому диапазону
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			if(i <= j){
				matrix->data[i][j] = SumMinMax(v, i+1, j+1);
			}else{
				matrix->data[i][j] = matrix->data[j][i];
			}
		}
	}
}


// Добавляет +1 к каждому элементу в диапазоне [n1, n2]
void addMatrix(Matrix *matrix, int v[], int size, int n1, int n2){
	int i=0;

	for(i=n1; i<=n2; i++){
		v[i]++;
	}

//обработать матрицу снова, как только значения вектора
// подверглись изменениям
	processMatrix(matrix, v, size);
}

// Вычитает 1 из каждого элемента в диапазоне [n1, n2]
void subMatrix(Matrix *matrix, int v[], int size, int n1, int n2){
	int i=0;

	for(i=n1; i<=n2; i++){
		v[i]--;
	}

//обработать матрицу снова, как только значения вектора
// подверглись изменениям
	processMatrix(matrix, v, size);
}
 
// Освобождаем память, выделенную для массива
void freeMatrix(Matrix *matrix) {
    int i;
    for (i = 0; i < matrix->size; i++) {
        free(matrix->data[i]);
    }
 
    free(matrix->data);
}
