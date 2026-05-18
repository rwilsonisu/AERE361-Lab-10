#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define TOL 1e-6
#define MAXITER 1000

int counter(double **A, int n) { //make use of sparse matrix storage
  int count = 0;
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n+1; j++) {
      if(A[i][j] != 0) { //counts non-zeros for sparse compression
	count++;
	
      } //end if
    } //end for j
  } //end for i
  
  return count;
} //end counter function

int isdd(double **A, int n) { //checks if matrix is diagonally dominant
  for(int i = 0; i < n; i++) {
    double diag = fabs(A[i][i]);
    double sum = 0;

    for(int j = 0; j < n; j++) {
      if(j != i) {
	sum += fabs(A[i][j]);
      } //end if
    } //end for j

    if(diag < sum) {
      return 0;
    } //end if
  } //end for
  return 1;
} //end isdd function

void gauss_seidel_func(double **A, double *x, int n, double tolerance, int maxIter) {
  for(int iter = 0; iter < maxIter; iter++) {
    double error = 0;
    for(int i = 0; i < n; i++) {

      if(A[i][i] == 0) { //checks to make sure theres no division by 0
	printf("Error: dividing by zero at row %d\n", i);
	exit(1);


      } //end if
      
      double sum = A[i][n]; //gauss-seidel equation
      for(int j = 0; j < n; j++) {
	if(j != i) {
	  sum -= A[i][j] * x[j]; //gauss-seidel equation
	} //end if
      } //end for

      double prev = x[i];
      x[i] = sum/A[i][i]; //gauss-seidel equation
      error += fabs(x[i] - prev);
    } //end for

    if(error < tolerance) { //stops when error is less than tolerance
      break;
    } //end if
  } //end for
} //end gauss_seidel_func function




int main(int argc, char *argv[]) {
  int n;
  double *x;
  double **A;
  double tol = TOL;
  int maxIter = MAXITER;

  for(int i = 1; i < argc; i++) { //checks parses
    if(strcmp(argv[i], "-tol") == 0 && i+1 < argc)
      tol = atof(argv[++i]);
    else if(strcmp(argv[i], "-iter") == 0 && i+1 < argc)
      maxIter = atoi(argv[++i]);
  } //end for

  //counts rows to determine n
  if(argc > 1 && argv[1][0] != '-') {
    FILE *fp = fopen(argv[1], "r");
    if(!fp) {
      printf("Error: can't open file.\n");
      return 1;
    } //end if

    char line[1024];
    n = 0;
    while(fgets(line, sizeof(line), fp)) {
      n++;
    } //end while
    rewind(fp);

    A = malloc(n*sizeof(double*));
    for(int i = 0; i < n; i++) {
      A[i] = malloc((n+1)*sizeof(double));
    } //end for

    int i = 0;
    while(fgets(line, sizeof(line), fp)) {
      int j = 0;
      char *charac = strtok(line, ",");
      while(charac) {
	A[i][j++] = atof(charac);
	charac = strtok(NULL, ",");
      } //end while
      i++;
    } //end while

    fclose(fp);
    
  } else {
    printf("How many equations: ");
    scanf("%d", &n);

    A = malloc(n*sizeof(double*));
    for(int i = 0; i < n; i++) {
      A[i] = malloc((n+1)*sizeof(double));
    } //end for

    printf("Enter augmented matrix: (%d rows, elements separated by a space)\n", n);
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n+1; j++) {
	scanf("%lf", &A[i][j]);
      } //end for j
    } //end for i
  } //end if else

  if(!isdd(A, n)) {
  fprintf(stderr, "\n\nError: Matrix is not diagonally dominant (might not converge)\n");
  } //end if
  
  x = calloc(n, sizeof(double));

  int nonZeros = counter(A, n); //sparse compression
  int total = n*(n+1);
  double compression = 1.0 - ((double)nonZeros/total);

  fprintf(stderr, "\n\nCompressed matrix contains %d elements, compressed by %.0f%%\n", nonZeros, compression*100);

  gauss_seidel_func(A, x, n, tol, maxIter);

  if(argc > 1 && argv[1][0] != '-') {
    FILE *out = fopen("answer.csv", "w");
    
    for(int i = 0; i < n; i++) {
      fprintf(out, "%lf\n", x[i]);
    } //end for
    
    fclose(out);
    
  } else {
    printf("\nSolution:\n");
    
    for(int i = 0; i < n; i++) {
      printf("x%d = %lf\n", i+1, x[i]);
    } //end for
  } //end if else

  return 0;
} //end main


