/* Written by: Prof. Kristin Yvonne Rozier
   March 2018

This is an example program implementing the Coordinate Format (COO) algorithm for sparse matrices. It includes several helper functions to demonstrate debugging and use in test-case generation.
*/

#include<stdlib.h>
#include<stdio.h>
#include<time.h> /*for rand()*/


/*Declare a struct to pass around a matrix*/
typedef struct coo_matrix_ {
  int nnz;

  /*unsigned rows[nnz]; row index for each non-zero value */
  unsigned int *rows;

  /*unsigned columns[nnz];  column index for each non-zero value */
  unsigned int *columns;

  /*double values[nnz]; each non-zero value */
  unsigned int *values;

};




/*Write a function to create a dense test matrix*/
void initialize_matrix(int M, int N, int nnz, int myMatrix[][N]) {

  int r; /*random integer*/
  int m, n; /*loop counters*/

  int running_nnz = 0; /*current number of nnz in matrix*/

  printf("Made a matrix:\n");

  for (m = 0; m < M; m++) {
    for (n = 0; n < N; n++) {
      
      if ( ((M * N) - (m * N + n)) == (nnz - running_nnz) ) {
	/*All remaining values must be non-zero*/
	while ( (r = rand()%100) == 0) {printf("rand is %d\n", r);}
	myMatrix[m][n] = r;
	running_nnz++;
      } /* end if*/
      else { /*Can choose a zero value*/
	
	/*if can choose a non-zero value, flip a coin*/
	if (( running_nnz < nnz) && (rand()%2 == 1) ) { 
	  
	  myMatrix[m][n] = rand()%100;
	  if (myMatrix[m][n] != 0) { running_nnz++; }
	} /*end if*/
	else { /*must choose a zero value*/
	  myMatrix[m][n] = 0;
	} /*end else*/
	
      } /*end else*/
      
      printf("%d ", myMatrix[m][n]);

    } /*end for*/
    printf("\n");
  } /*end for*/
    printf("\n");
  
    /*printf("running_nnz = %d\n", running_nnz);*/

  return;

} /*end initialize_matrix*/
  

void initialize_COO_matrix(int M, int N, int nnz, int denseMatrix[][N], struct coo_matrix_ *cooMatrix) {

  int m = 0;
  int n = 0;
  int running_nnz = 0;

  for (m = 0; m < M; m++) {
    for (n = 0; n < N; n++) {      
      if (denseMatrix[m][n] == 0) { continue; }
      
      /*Otherwise, we need to store the non-zero value*/
      cooMatrix->rows[running_nnz] = m;
      cooMatrix->columns[running_nnz] = n;
      cooMatrix->values[running_nnz] = denseMatrix[m][n];
      
      running_nnz++; /*make sure to increment!*/
    } /*end for*/
  } /*end for*/
  
  printf("COO format:\n");
  printf("unsigned rows[%d] =    { ", nnz);
  for (running_nnz = 0; running_nnz < nnz; running_nnz++) {
    printf(" %d ", cooMatrix->rows[running_nnz]);
  } /*end for*/ 
  printf("};\n");
  
  printf("unsigned columns[%d] = { ", nnz);
  for (running_nnz = 0; running_nnz < nnz; running_nnz++) {
    printf(" %d ", cooMatrix->columns[running_nnz]);
  } /*end for*/ 
  printf("};\n");
  
  printf("unsigned values[%d] =  { ", nnz);
  for (running_nnz = 0; running_nnz < nnz; running_nnz++) {
    printf("%d ", cooMatrix->values[running_nnz]);
  } /*end for*/ 
  printf("};\n");
  
  
  return;
  
} /*end initialize_COO_matrix*/


void COO_find_value(int row, int col, struct coo_matrix_ *coo_matrix) {

  int i;
  int result;

  printf("looking until nnz of %d\n", coo_matrix->nnz);
  
  for (i = 0; i < coo_matrix->nnz; i++) {
    printf("found row %d col %d has val %d...\n", coo_matrix->rows[i], coo_matrix->columns[i], coo_matrix->values[i]);
    if ( (coo_matrix->rows[i] == row) && (coo_matrix->columns[i] == col) ) {
      result = coo_matrix->values[i];
      break;
    } /*end if*/
    else { /*no exact match is found*/
      result = 0;
    } /*end else*/ 
  } /*end for*/
  
  printf("The value at (%d,%d) is %d\n", row, col, result);

} /*end COO_find_value*/


int main (void) {


  /*initialize random number generator*/
  srand(time(0));

  /*randomly initialize matrix*/
  /*int** myMatrix;
    initialize_matrix(3,3,6, myMatrix);*/

  int M = 3;
  int N = 3; 
  int NNZ = 6;

  int denseMatrix[M][N]; /*declare matrix*/
  initialize_matrix(M, N, NNZ, denseMatrix);

  /*Make a struct to pass the COO matrix*/
  struct coo_matrix_ coo_matrix;
  coo_matrix.nnz = NNZ;
  coo_matrix.rows = (int *)malloc(NNZ * sizeof(int));
  coo_matrix.columns = (int *)malloc(NNZ * sizeof(int));
  coo_matrix.values = (int *)malloc(NNZ * sizeof(int));

  /*Store the dense matrix in COO format*/
  initialize_COO_matrix(M, N, NNZ, denseMatrix, &coo_matrix);
  
  /*Try to find a value in COO*/
  COO_find_value(1,1,&coo_matrix);

  return 0; /*terminate normally*/
  
} /*end main*/

