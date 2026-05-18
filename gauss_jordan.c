#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    /* Declare Variables */
    int i,j,k,n; /*iterators*/
    /* You'll need a few more variables, including a matrix! */
    double temp;
    char s[100];

    /* Request System Order (Number of Equations) */
    printf("\nHow many equations: ");
    scanf("%s", s);

    int len = strlen(s);
    for(k = 0; k < len; k++) {
      if(!isdigit(s[k])) {
	printf("Error: Not a valid input for n.\n");
	return 0;
      } //end if
    } //end for
    
    n = atoi(s);

    if(n < 2) {
      printf("Error: Not a valid input for n.\n");
      return 0;
    } //end if

    /* Allocate Dynamic Variables
       (psst... malloc is pretty good at this) */
    float **mat = malloc(n*sizeof(float*));
    for(i = 0; i < n; i++) {
      mat[i] = malloc((n+1)*sizeof(float)); //dynamically allocate
    } //end for

    float *solution = malloc(n*sizeof(float));

    /* Request Augmented Matrix Values. */
    printf("\nEnter the elements of augmented matrix row-wise:\n");
    for (i = 0; i < n; i++) {
      for (j = 0; j < n+1; j++) {
            printf(" Matrix[%d][%d]: ", i+1, j+1);
            scanf("%f", &mat[i][j]);
        } /*end for*/
    } /*end for*/

    /* Diagonalize the matrix. */
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
	  if (i != j) {
	    
	    if(mat[j][j] == 0.0) {
	      printf("Error: Division by 0.\n");
	      return 0;
	    } //end if
	  
	    // There is a useful intermediate value you can compute here.
	    temp = mat[i][j]/mat[j][j];

	    for (k = 0; k < n+1; k++) {
	      /*This is where the magic happens ... */
	      mat[i][k] = mat[i][k] - (temp*mat[j][k]);
	    } //end for
	  } /*end if*/
	} /*end for*/
    } /*end for*/
    
    printf("\nThe solution is:\n");
    for (i = 0; i < n; i++) {
      if(mat[i][i] == 0.0) {
	printf("Error: Division by 0.\n");
	return 0;
      } //end if
      
      // One last bit of math - compute the unknown from the diagonal and constant
      solution[i] = mat[i][n]/mat[i][i];
      printf("\n x%d = %f\n", i+1, solution[i]);
    } /*end for*/
    
    return 0; /*exit normally*/
} /*end main*/
