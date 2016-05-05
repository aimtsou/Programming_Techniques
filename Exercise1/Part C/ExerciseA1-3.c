#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;

//
// Program Entry Point
//
int main()
{

    FILE *input, *output;

    int rows, cols, dim;
    int i, j, k;
	float coeff,temp1,temp,temp2; 
	
    // open input file for read
    input = fopen("in.dat", "r");        
	if(input == NULL){
		perror("failed to open in.dat for read");
		return EXIT_FAILURE;
	}
	
	// open output file for write
    output = fopen("out.dat", "w");       
    if(output == NULL){
		perror("failed to open out.dat for write");
		fclose(input);
		return EXIT_FAILURE;
	}
	
	// read the dimensions of matrix from file
    fscanf(input, "%d %d", &rows, &cols);    
    
	// pass the rows to dim variable(nxn matrix)
    dim = rows;
    
	// Create the arrays
    float matrix[rows][cols];    
    float Inv[rows][cols];
	
	
	// read each line of file
    for (i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
             fscanf(input,"%f", &matrix[i][j]);
        }
    }
	
	// print input matrix to screen
	printf("Matrix Input by user:\n");
    for(i = 0; i < rows; i++){
        printf("\n");
		for(j=0; j < cols; j++){
            printf("% 2.2f",matrix[i][j]);
        }
	}
	printf("\n");
	
	// print input matrix to file
	fprintf(output,"\nMatrix Input by user:\n");
    for(i = 0; i < rows; i++){
        fprintf(output,"\n");
		for(j=0; j < cols; j++){
            fprintf(output,"% 2.2f",matrix[i][j]);
        }
    }	
	fprintf(output,"\n");
	
	// initialize inverse matrix
    for ( i = 0; i < rows; i++){
        for( j = 0; j < cols; j++) {
             Inv[i][j] = 0;
        }
        Inv[i][i] = 1;       
    }
    
	// if diagonal element is zero swap
	for(k = 0; k < dim; k++){
		if(matrix[k][k] == 0){
			for(j = 0; j < dim; j++){
				temp = matrix[1][j];
				matrix[1][j] = matrix[0][j];
				matrix[0][j] = temp;
				temp1 = Inv[1][j];
				Inv[1][j] = Inv[0][j];
				Inv[0][j] = temp1;
			}
		}
		// sanity check 
		if(matrix[k][k] == 0){
			printf("Matrix not inversible");
			getchar();
			return EXIT_FAILURE;
			}
        }
	
	// Gaussian Elimination		
	for(i = 0; i < dim; i++){
		temp2 = matrix[i][i];
		for (j = 0; j < dim; j++){
			matrix[i][j] = matrix[i][j] / temp2;
			Inv[i][j]= Inv[i][j] / temp2;
		}       
		for(k = 0; k < dim; k++){
			if(k != i){
				coeff = (matrix[k][i]);
				for(j = 0; j < dim; j++){
					matrix[k][j] = matrix[k][j]-(matrix[i][j]*coeff);
					Inv[k][j]= Inv[k][j]-(Inv[i][j]*coeff);
				}
			}
		}
	}	
	
	// print inverse matrix to screen
	printf("\nInverse of matrix is:\n");
	for ( i = 0; i < dim; i++){
		printf("\n");
        for( j = 0; j < dim; j++) {
				printf("% 2.2f",Inv[i][j]);				
        }
    }
	
	// print inverse matrix to file
	fprintf(output,"\nInverse of matrix is:\n");
	for ( i = 0; i < dim; i++){
		fprintf(output,"\n");
        for( j = 0; j < dim; j++) {
				fprintf(output,"% 2.2f",Inv[i][j]);
        }
    }
	
	// close files
	fclose(input);
    fclose(output);
	
    getchar();
    return EXIT_SUCCESS;

}
    


    
    
    
    
    

