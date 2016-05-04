#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"


// 
// creates matrix from input file
// 
int matrix_create(matrix_t **matrix, int rows, int cols)
{
	matrix_t *temp;
	int size;
	
	// sanity check parameters
	if(matrix == NULL) return 0;
	
	// allocate structure
	size = sizeof(matrix_t) + ((rows * cols) * sizeof(element_t));
	temp = (matrix_t *)malloc(size);
	
	// if we allocated ok then fill in structure
	if(temp){
		memset(temp, 0, size);
		temp->rows = rows;
		temp->cols = cols;
	}
	
	// set new matrix pointer
	*matrix = temp;
	return 1;
}

// 
// free previously allocated matrix
// 
int matrix_free(matrix_t **matrix)
{
	// sanity check parameters
	if(matrix == NULL) return 0;
	
	// free matrix and clear pointer
	free(*matrix);
	*matrix = NULL;
	
	return 1;
}

//
// get matrix position
//
element_t *matrix_index(matrix_t *matrix, int x, int y)
{
	// sanity check parameters
	if(matrix == NULL) return 0;
	
	return &matrix->data[(y * matrix->cols) + x];
}