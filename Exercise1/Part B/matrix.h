#ifndef _matrix_h_
#define _matrix_h_

typedef struct element {
	int red, green, blue;
} element_t;

typedef struct matrix {
	int rows, cols;
	element_t data[0];
} matrix_t; 

int matrix_create(matrix_t **matrix, int rows, int cols);
int matrix_free(matrix_t **matrix);
element_t *matrix_index(matrix_t *matrix, int x, int y);

#endif 