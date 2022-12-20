#include "SegTree.h"

// Возвращает индекс, соответствующий левым дочерним элементам узла.
int get_left(int i){
	return 2*i;
}

// Возвращает индекс, соответствующий правым дочерним элементам узла.
int get_right(int i){
	return 2*i + 1;
}

// Возвращает индекс, соответствующий середине вектора
int get_mid(int l, int r){
	return (l+r)/2;
}

// Строит дерево сегментации с его 2n-1 узлами, вычисляя кортеж
// совпадает только один раз.
// Построение начинается с листовых узлов и идет вверх по дереву.
void BuildSegTree(T tree[], int v[], int index, int l, int r){
	// если интересующий интервал [l,r] с l=r, мы приходим к листовому узлу
	if (l == r){ 
		// заставляет листовой узел получить соответствующий кортеж из вектора v
		tree[index].min = v[l];
		tree[index].max = v[l];
		tree[index].sum = v[l]; 
	}else{ 
		BuildSegTree(tree, v, get_left(index), l, get_mid(l, r));
		BuildSegTree(tree, v, get_right(index), get_mid(l, r) + 1, r);
		// min и max внутреннего узла будут min и max его левого и правого потомков
		tree[index].min = min(tree[get_left(index)].min, tree[get_right(index)].min);
		tree[index].max = max(tree[get_left(index)].max, tree[get_right(index)].max);
		// сумма внутреннего узла будет суммой левого и правого потомков
		tree[index].sum = tree[get_left(index)].sum + tree[get_right(index)].sum;
	}
}

// Добавляет 1 к элементам в диапазоне [L, R] и обновляет предыдущие узлы до корня
void add(T tree[], int index, int l, int r, int L, int R){		
	// если интересующий интервал [L, R] находится вне текущего анализируемого интервала [l, r]
	if ((l > r) || (l > R) || (r < L))
		return;
	// если достигнута сумма листового узла 1
	if (l == r){
		tree[index].min += 1;
		tree[index].max += 1;
		tree[index].sum += 1;
	}else{ 
		add(tree, get_left(index), l, get_mid(l, r), L, R);
		add(tree, get_right(index), get_mid(l, r) + 1, r, L, R);
		// обновляет минимум, максимум и сумму внутренних узлов от их дочерних элементов	
		tree[index].min = min(tree[get_left(index)].min, tree[get_right(index)].min);
		tree[index].max = max(tree[get_left(index)].max, tree[get_right(index)].max);
		tree[index].sum = tree[get_left(index)].sum + tree[get_right(index)].sum;
	}
}

// Вычитает 1 из элементов в диапазоне [L, R] и обновляет предыдущие узлы до корня
void sub(T tree[], int index, int l, int r, int L, int R){		
	if ((l > r) || (l > R) || (r < L))
		return;
	// если вы достигли конечного узла, вычтите 1
	if (l == r){
		tree[index].min -= 1;
		tree[index].max -= 1;
		tree[index].sum -= 1;
	}else{
		sub(tree, get_left(index), l, get_mid(l, r), L, R);
		sub(tree, get_right(index), get_mid(l, r) + 1, r, L, R);		
		tree[index].min = min(tree[get_left(index)].min, tree[get_right(index)].min);
		tree[index].max = max(tree[get_left(index)].max, tree[get_right(index)].max);
		tree[index].sum = tree[get_left(index)].sum + tree[get_right(index)].sum;
	}
}

// Запрос суммы диапазона [l, r] в дереве
int computeSum(T tree[], int index, int l, int r, int L, int R){
	// если интересующий интервал [L, R] находится вне текущего анализируемого интервала [l, r]
	if ((l > R) || (r < L))
		return 0;  //нейтральный элемент

	// если интересующий интервал присутствует в дереве, возвращает сумму этого узла
	if ((l >= L) && (r <= R))
		return tree[index].sum; 	

	// если он не запрашивает левый и правый дочерние узлы, которые образуют [l, r]
	int sL = computeSum(tree, get_left(index), l, get_mid(l, r), L, R);
	int sR = computeSum(tree, get_right(index), get_mid(l, r) + 1, r, L, R);

	return sL + sR;
}

// Запросить минимум интервала [l, r] в дереве
int computeMin(T tree[], int index, int l, int r, int L, int R){
	if ((l > R) || (r < L))
		return 2147483647;  //нейтральный элемент

	// если интересующий интервал присутствует в дереве, возвращает минимум этого узла
	if ((l >= L) && (r <= R))
		return tree[index].min;	

	int minL = computeMin(tree, get_left(index), l, get_mid(l, r), L, R);
	int minR = computeMin(tree, get_right(index), get_mid(l, r) + 1, r, L, R);

	return min(minL, minR);
}

// Запрос максимального диапазона [l, r] в дереве
int computeMax(T tree[], int index, int l, int r, int L, int R){
	if ((l > R) || (r < L))
		return -2147483648;  //нейтральный элемент

	// если интересующий интервал присутствует в дереве, возвращает максимум этого узла
	if ((l >= L) && (r <= R))
		return tree[index].max;	

	int maxL = computeMax(tree, get_left(index), l, get_mid(l, r), L, R);
	int maxR = computeMax(tree, get_right(index), get_mid(l, r) + 1, r, L, R);

	return max(maxL, maxR);
}