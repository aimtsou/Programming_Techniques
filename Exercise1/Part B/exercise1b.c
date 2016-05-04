#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "matrix.h"

//
// find element average
//
float elementAverage(element_t* e)
{
	return (e->red + e->green + e->blue) / 3.0;
}

//
// find percentage of diference
//
float cellDifference(matrix_t* matrix1, int x1, int y1, int x2, int y2)
{
	element_t *one, *two;
	float oneAvg, twoAvg;
	
	//get matrix position
	one = matrix_index(matrix1, x1, y1);
	
	//find element average
	oneAvg = elementAverage(one);
	
	//get matrix position
	two = matrix_index(matrix1, x2, y2);
	
	//find element average
	twoAvg = elementAverage(two);
	
	//calculate percentage
	if (oneAvg != 0)
		return abs(oneAvg - twoAvg)/oneAvg * 100;
	else
		return 100;	
}

//
// find edges
//
matrix_t* findEdges(matrix_t* matrix1, float allowedDifference)
{
	matrix_t* result;
	int x,y;
	
	// sanity check parameters
	if(!matrix_create(&result, matrix1->rows, matrix1->cols)) 
	{
		perror("failed to create result");		
		return 0;
	}

	for (y = 0; y < matrix1->rows; ++y)
	{
		for (x = 0; x < matrix1->cols; ++x)
		{
			// check parameters
			char tooDifferent = 0;
			if (y > 0)
				tooDifferent |=
					cellDifference(matrix1, x, y, x, y - 1) > allowedDifference;
			
			if (y < matrix1->rows)
				tooDifferent |=
					cellDifference(matrix1, x, y, x, y + 1) > allowedDifference;
			
			if (x > 0)
				tooDifferent |=
					cellDifference(matrix1, x, y, x - 1, y) > allowedDifference;
			
			if (x < matrix1->cols)
				tooDifferent |=
					cellDifference(matrix1, x, y, x + 1, y) > allowedDifference;
			
			//get matrix position
			element_t* res = matrix_index(result, x, y);
			res->red = res->green = res->blue =
				tooDifferent ? 1 : 0;
		}
	}
	
	return result;
}

extern int errno;

//
// program entry point
//
int main(int argc, char *argv[])
{
	FILE *input, *output;
	matrix_t *matrix1, *result;
	element_t *item;
	int rows, cols, x, y;
	float allowedDifference, *averages;
	
	// open input file for read
	input = fopen("in.dat", "r");
	if(input == NULL){
		perror("failed to open in.dat for read");
		return EXIT_FAILURE;
	}
	
	// read rows and columns from input file
	fscanf(input, "%d %d\n", &rows, &cols);
	
	// create matrix1 from input file	
	if(!matrix_create(&matrix1, rows, cols)){
		perror("failed to create matrix1");
		fclose(input);
		return EXIT_FAILURE;
	}
	
	// create result from input file
	if(!matrix_create(&result, rows, cols)){
		perror("failed to create result");
		fclose(input);
		return EXIT_FAILURE;
	}
	
	// create array for averages
	if((averages = (float *)malloc(sizeof(float) * cols * rows)) == NULL){
		perror("failed to create averages array");
		fclose(input);
		return EXIT_FAILURE;
	}
	
	// open output file for write
	output = fopen("out.dat", "w");
	if(output == NULL){
		perror("failed to open out.dat for write");
		fclose(input);
		return EXIT_FAILURE;
	}
	
	for(y = 0; y < rows; y++){
		for(x = 0; x < cols; x++){
			
			// get matrix position
			item = matrix_index(matrix1, x, y);
			
			// read the elements
			fscanf(input, "%d %d %d ",
				&item->red, &item->green, &item->blue);
			
			// sanity check parameters
			if((item->red < 0 || item->red > 255) || (item->green < 0 || item->green > 255)
					|| (item->blue < 0 || item->blue > 255)){
				perror("Value must be between 0-255"); 
				matrix_free(&matrix1);
				fclose(input);
				
				return EXIT_FAILURE;
			}

			// average
			averages[y * cols + x] = elementAverage(item);
		}
	}
	
	// print matrix1 to screen
	for(y = 0; y < rows; y++){
		for(x = 0; x < cols; x++){
			item = matrix_index(matrix1, x, y);
			printf("matrix1[%d, %d] = { %3d, %3d, %3d }\n", x, y, item->red, item->green, item->blue);
		}
	}
	printf("\n");
	
	// print matrix1 to file
	for(y = 0; y < rows; y++){
		for(x = 0; x < cols; x++){
			item = matrix_index(matrix1, x, y);
			fprintf(output, "matrix1[%d, %d] = { %3d, %3d, %3d }\n", x, y, item->red, item->green, item->blue);
		}
	}
	
	printf("\n");
	
	// print averages to screen
	for(y = 0; y < rows; y++){
		for(x = 0; x < cols; x++){
			printf("averages[%d, %d] = %f\n", x, y, averages[y * cols + x]);
		}
	}
	
	printf("\n");
	
	// print averages to file
	for(y = 0; y < rows; y++){
		for(x = 0; x < cols; x++){
			fprintf(output, "averages[%d, %d] = %f\n", x, y, averages[y * cols + x]);
		}
	}
	
	// get percentage
	printf("enter allowed difference:\n");
	fflush(stdout);
	scanf("%f", &allowedDifference);
	
	result = findEdges(matrix1, allowedDifference); 
	printf("\n");
	
	// print result to screen
	for(y = 0; y < rows; y++){
		for(x = 0; x < cols; x++){
			item = matrix_index(result, x, y);
			printf("result[%d, %d] = { %3d, %3d, %3d }\n", x, y, item->red, item->green, item->blue);
		}
	}
	
	printf("\n");
	
	// print result to file
	for(y = 0; y < rows; y++){
		for(x = 0; x < cols; x++){
			item = matrix_index(result, x, y);
			fprintf(output,"result[%d, %d] = { %3d, %3d, %3d }\n", x, y, item->red, item->green, item->blue);
		}
	}	
	
	
	// free memory allocated to matrices
	matrix_free(&matrix1);
	matrix_free(&result);
	
	// close previously opened files
	fclose(output);
	fclose(input);
	
	system("pause");
	return EXIT_SUCCESS;
}
