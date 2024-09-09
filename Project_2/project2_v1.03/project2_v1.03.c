/* Project 2
 * ===========
 *    Name: Joshua Omori
 *    Class: EE 160
 *
 * Current objective: (v1.03)
 * ====================
 *    Now that Gauss Jordan has been done for a polynomial of 1, it will be done for the
 *    other 4 polynomials as well...
 *
 *    (The calculations... :,) <= Literally me now)
 * 
 * Overall purpose:
 * ==================
 *    In order to get the best fit line of a polynomial, the order of best fit 
 *    and the plotpoints will be inputted and a combination of matrices and 
 *    Gauss-Jordan elimination will be used.  The plotpoints are read from an ASCII
 *    file and outputted into one as well.  This takes everything we have learned
 *    in the past and combines it into one huge chunggus of a project.
 *
 * Inputs: 
 * ========= 
 *    User:
 *       poly_order = The order of polynomial that will be used for Gauss Jordan later on...
 *       fn = The file name the user wants the program to open
 *       otpt_fle_ck = Checks if the user wants the results shown in an output file 
 *       otpt_file = The file name the user wants the results to save under
 *    File:
 *       data d[] = The x and y values get stored in here
 * 
 * Outputs:
 * =========
 *    TBA in later versions
 *    number of data points read from file
 *    Each step written out during matrix calculation
 *
 * Version Info:
 * ===============
 *    v1.02 Calculations pt 1
 *    v1.01 Creation of the "get inputs"
 *    v1.02 Matrix calculations for 1 polynomial (the base that will be used)
 *    v1.03 Matrix calculations for all polynomials will be done
 *    Compile Date: Nov 30, 2021
 */


#include <stdio.h>
#include <math.h>

struct data {
   double x;
   double y;
};

double sum_x(struct data d[], int n, int k);
double sum_y(struct data d[], int n, int k);

int main(void) {

// PART 1: Get input from user

   // 1) create variables

   int poly_ordr;
   char fn[100], chr;
   FILE *fp1;
   struct data d[200];
   char otpt_fle_ck;
   char otpt_fle[100];
   FILE *fp2;
   

   // 2) Get polynomial order

   printf("\nEnter the polynomial order (1-5): ");
   scanf("%i", &poly_ordr);
   if (poly_ordr > 5 || poly_ordr < 1) {
      printf("\nERROR: Enter a valid integer...\n\n");
      return 1;
   }

   // 3) Open file

   printf("\nFiles Available: \n");
   printf("   test1.csv\n   test2.csv\n   final.csv\n\n");

   printf("Please enter file name: ");
   scanf("%100s", fn);

   fp1 = fopen(fn, "r");
   if (fp1 == NULL) {
      printf("\nERROR: File not found\n\n");
      return 1;
   }

   printf("\nfile successfully opened...\n\n");


   // 4) Read file
      // pt1-count amount of \n in order to determine num of lines 
   char c;
   int i = 0;
   for (c=getc(fp1); c != EOF; c = getc(fp1)) {
      if (!(c == '\n' || c == ',' || c == '.' || c == '-') && isdigit(c)==0) {
         printf("\nERROR: File can't be read...\n");
         printf("   (double check that there isn't a header and all values are numbers)...\n\n");
         return 1;
      }
      if (c == '\n') {
         i = i + 1;
      }
   }
   printf("Total data points (x,y) read from file = %i\n\n", i);

      //pt2-repeat 'i' amount of lines to read the correct amount of info
   fp1 = fopen(fn, "r");
   int n;
   for (n=0;n<i;n++) {
      fscanf(fp1,"%lf,%lf",&d[n].x,&d[n].y);
// TEST
      printf("%lf,%lf\n",d[n].x, d[n].y);
      printf("%i\n", n);
   }
   printf("\nfile successfully read...\n\n");


// PART 2: Calculations... Split each polynomial calculation into 5 different sections

   // 1st order
   if (poly_ordr == 1) {
      // 1) Create the matrix that will be used for Gauss Jordan
      double mtrx[2][3] = { {n, sum_x(d, n, 1), sum_y(d, n, 0)}, 
                               {sum_x(d, n, 1), sum_x(d, n, 2), sum_y(d, n, 1)} };

      printf("The coefficients (square) matrix 'A' is 2 x 2 with values: \n");
      printf("[%.3lf %.3lf]\n", mtrx[0][0], mtrx[0][1]);
      printf("[%.3lf %.3lf]\n\n", mtrx[1][0], mtrx[1][1]);

      printf("The constants (column) Matrix 'B' is 2 x 1\n");
      printf("[%.3lf]\n", mtrx[0][2]);
      printf("[%.3lf]\n\n", mtrx[1][2]);

      // 2) Gauss Jordan Time (swapping step not needed)
      mtrx[0][1] = mtrx[0][1] / mtrx[0][0];
      mtrx[0][2] = mtrx[0][2] / mtrx[0][0];
      mtrx[0][0] = mtrx[0][0] / mtrx[0][0];

      mtrx[1][1] = mtrx[1][1] - (mtrx[0][1] * mtrx[1][0]);
      mtrx[1][2] = mtrx[1][2] - (mtrx[0][2] * mtrx[1][0]);
      mtrx[1][0] = mtrx[1][0] - (mtrx[0][0] * mtrx[1][0]);

      mtrx[1][2] = mtrx[1][2] / mtrx[1][1];
      mtrx[1][0] = mtrx[1][0] / mtrx[1][1];
      mtrx[1][1] = mtrx[1][1] / mtrx[1][1];

      mtrx[0][2] = mtrx[0][2] - (mtrx[1][2] * mtrx[0][1]);
      mtrx[0][0] = mtrx[0][0] - (mtrx[1][0] * mtrx[0][1]);
      mtrx[0][1] = mtrx[0][1] - (mtrx[1][1] * mtrx[0][1]);

      // 3) Display results
      printf("The row reduced (RREF) augmented matrix is: \n");
      printf("[ 1.000 0.000 | %lf ]\n", mtrx[0][2]);
      printf("[ 0.000 1.000 | %lf ]\n\n", mtrx[1][2]);

      printf("The best-fit Least squares equation is:\n\n");
      printf("%lf * x^0 + %lf * x^1\n\n", mtrx[0][2], mtrx[1][2]);

// TEST
//   printf("\n   a      b      c   \n");
//   printf("=========================\n");
//   printf("%-7.2f %-7.2f = %-7.2f\n", mtrx[0][0], mtrx[0][1], mtrx[0][2]);
//   printf("%-7.2f %-7.2f = %-7.2f\n\n", mtrx[1][0], mtrx[1][1], mtrx[1][2]);
   }

   // 2nd order
   else if (poly_ordr == 2) {
      // 1) Create the matrix that will be used for Gauss Jordan
      double mtrx[3][4] = { {n, sum_x(d, n, 1), sum_x(d, n, 2) ,sum_y(d, n, 0)},
               {sum_x(d, n, 1), sum_x(d, n, 2), sum_x(d, n, 3), sum_y(d, n, 1)}, 
               {sum_x(d, n, 2), sum_x(d, n, 3), sum_x(d, n, 4), sum_y(d, n, 2)} };

      printf("The coefficients (square) matrix 'A' is 3 x 3 with values: \n");
      printf("[%.3lf %.3lf %.3lf]\n", mtrx[0][0], mtrx[0][1], mtrx[0][2]);
      printf("[%.3lf %.3lf %.3lf]\n", mtrx[1][0], mtrx[1][1], mtrx[1][2]);
      printf("[%.3lf %.3lf %.3lf]\n\n", mtrx[2][0], mtrx[2][1], mtrx[2][2]);

      printf("The constants (column) Matrix 'B' is 3 x 1\n");
      printf("[%.3lf]\n", mtrx[0][3]);
      printf("[%.3lf]\n\n", mtrx[1][3]);
      printf("[%.3lf]\n\n", mtrx[2][3]);

      // 2) Gauss Jordan Time (swapping step not needed)
      mtrx[0][1] = mtrx[0][1] / mtrx[0][0];
      mtrx[0][2] = mtrx[0][2] / mtrx[0][0];
      mtrx[0][3] = mtrx[0][3] / mtrx[0][0];
      mtrx[0][0] = mtrx[0][0] / mtrx[0][0];

      mtrx[1][1] = mtrx[1][1] - (mtrx[0][1] * mtrx[1][0]);
      mtrx[1][2] = mtrx[1][2] - (mtrx[0][2] * mtrx[1][0]);
      mtrx[1][3] = mtrx[1][3] - (mtrx[0][3] * mtrx[1][0]);
      mtrx[1][0] = mtrx[1][0] - (mtrx[0][0] * mtrx[1][0]);

      mtrx[2][1] = mtrx[2][1] - (mtrx[0][1] * mtrx[2][0]);
      mtrx[2][2] = mtrx[2][2] - (mtrx[0][2] * mtrx[2][0]);
      mtrx[2][3] = mtrx[2][3] - (mtrx[0][3] * mtrx[2][0]);
      mtrx[2][0] = mtrx[2][0] - (mtrx[0][0] * mtrx[2][0]);

      mtrx[1][2] = mtrx[1][2] / mtrx[1][1];
      mtrx[1][0] = mtrx[1][0] / mtrx[1][1];
      mtrx[1][3] = mtrx[1][3] / mtrx[1][1];
      mtrx[1][1] = mtrx[1][1] / mtrx[1][1];

      mtrx[0][2] = mtrx[0][2] - (mtrx[1][2] * mtrx[0][1]);
      mtrx[0][0] = mtrx[0][0] - (mtrx[1][0] * mtrx[0][1]);
      mtrx[0][3] = mtrx[0][3] - (mtrx[1][3] * mtrx[0][1]);
      mtrx[0][1] = mtrx[0][1] - (mtrx[1][1] * mtrx[0][1]);

      mtrx[2][0] = mtrx[2][0] - (mtrx[1][0] * mtrx[2][1]);
      mtrx[2][3] = mtrx[2][3] - (mtrx[1][3] * mtrx[2][1]);
      mtrx[2][2] = mtrx[2][2] - (mtrx[1][2] * mtrx[2][1]);
      mtrx[2][1] = mtrx[2][1] - (mtrx[1][1] * mtrx[2][1]);

      mtrx[2][0] = mtrx[2][0] / mtrx[2][2];
      mtrx[2][3] = mtrx[2][3] / mtrx[2][2];
      mtrx[2][1] = mtrx[2][1] / mtrx[2][2];
      mtrx[2][2] = mtrx[2][2] / mtrx[2][2];

      mtrx[0][0] = mtrx[0][0] - (mtrx[2][0] * mtrx[0][2]);
      mtrx[0][3] = mtrx[0][3] - (mtrx[2][3] * mtrx[0][2]);
      mtrx[0][1] = mtrx[0][1] - (mtrx[2][1] * mtrx[0][2]);
      mtrx[0][2] = mtrx[0][2] - (mtrx[2][2] * mtrx[0][2]);

      mtrx[1][0] = mtrx[1][0] - (mtrx[2][0] * mtrx[1][2]);
      mtrx[1][3] = mtrx[1][3] - (mtrx[2][3] * mtrx[1][2]);
      mtrx[1][1] = mtrx[1][1] - (mtrx[2][1] * mtrx[1][2]);
      mtrx[1][2] = mtrx[1][2] - (mtrx[2][2] * mtrx[1][2]);

      // 3) Display results
      printf("The row reduced (RREF) augmented matrix is: \n");
      printf("[ 1.000 0.000 0.000 | %lf ]\n", mtrx[0][3]);
      printf("[ 0.000 1.000 0.000 | %lf ]\n", mtrx[1][3]);
      printf("[ 0.000 0.000 1.000 | %lf ]\n\n", mtrx[2][3]);

      printf("The best-fit Least squares equation is:\n\n");
      printf("%lf * x^0 + %lf * x^1 + %lf * x^2\n\n", mtrx[0][3], mtrx[1][3], mtrx[2][3]);

// TEST
//   printf("\n   a	 b        c        d   \n");
//   printf("====================================\n");
//   printf("%-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[0][0], mtrx[0][1], mtrx[0][2], mtrx[0][3]);
//   printf("%-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[1][0], mtrx[1][1], mtrx[1][2], mtrx[1][3]);
//   printf("%-7.2f %-7.2f %-7.2f = %-7.2f\n\n", mtrx[2][0], mtrx[2][1], mtrx[2][2], mtrx[2][3]);

   }

   // 3rd order
   else if (poly_ordr == 3) {
      // 1) Create the matrix that will be used for Gauss Jordan
      double mtrx[4][5] = { {n, sum_x(d, n, 1), sum_x(d, n, 2), sum_x(d, n, 3), sum_y(d, n, 0)},
               {sum_x(d, n, 1), sum_x(d, n, 2), sum_x(d, n, 3), sum_x(d, n, 4), sum_y(d, n, 1)}, 
               {sum_x(d, n, 2), sum_x(d, n, 3), sum_x(d, n, 4), sum_x(d, n, 5), sum_y(d, n, 2)},
               {sum_x(d, n, 3), sum_x(d, n, 4), sum_x(d, n, 5), sum_x(d, n, 6), sum_y(d, n, 3)} };

      printf("The coefficients (square) matrix 'A' is 4 x 4 with values: \n");
      printf("[%.3lf %.3lf %.3lf %.3lf]\n", mtrx[0][0], mtrx[0][1], mtrx[0][2], mtrx[0][3]);
      printf("[%.3lf %.3lf %.3lf %.3lf]\n", mtrx[1][0], mtrx[1][1], mtrx[1][2], mtrx[1][3]);
      printf("[%.3lf %.3lf %.3lf %.3lf]\n", mtrx[2][0], mtrx[2][1], mtrx[2][2], mtrx[2][3]);
      printf("[%.3lf %.3lf %.3lf %.3lf]\n\n", mtrx[3][0], mtrx[3][1], mtrx[3][2], mtrx[3][3]);

      printf("The constants (column) Matrix 'B' is 3 x 1\n");
      printf("[%.3lf]\n", mtrx[0][4]);
      printf("[%.3lf]\n", mtrx[1][4]);
      printf("[%.3lf]\n", mtrx[2][4]);
      printf("[%.3lf]\n\n", mtrx[3][4]);

      // 2) Gauss Jordan Time (swapping step not needed)
      mtrx[0][1] = mtrx[0][1] / mtrx[0][0];
      mtrx[0][2] = mtrx[0][2] / mtrx[0][0];
      mtrx[0][3] = mtrx[0][3] / mtrx[0][0];
      mtrx[0][4] = mtrx[0][4] / mtrx[0][0];
      mtrx[0][0] = mtrx[0][0] / mtrx[0][0];

      mtrx[1][1] = mtrx[1][1] - (mtrx[0][1] * mtrx[1][0]);
      mtrx[1][2] = mtrx[1][2] - (mtrx[0][2] * mtrx[1][0]);
      mtrx[1][3] = mtrx[1][3] - (mtrx[0][3] * mtrx[1][0]);
      mtrx[1][4] = mtrx[1][4] - (mtrx[0][4] * mtrx[1][0]);
      mtrx[1][0] = mtrx[1][0] - (mtrx[0][0] * mtrx[1][0]);

      mtrx[2][1] = mtrx[2][1] - (mtrx[0][1] * mtrx[2][0]);
      mtrx[2][2] = mtrx[2][2] - (mtrx[0][2] * mtrx[2][0]);
      mtrx[2][3] = mtrx[2][3] - (mtrx[0][3] * mtrx[2][0]);
      mtrx[2][4] = mtrx[2][4] - (mtrx[0][4] * mtrx[2][0]);
      mtrx[2][0] = mtrx[2][0] - (mtrx[0][0] * mtrx[2][0]);

      mtrx[3][1] = mtrx[3][1] - (mtrx[0][1] * mtrx[3][0]);
      mtrx[3][2] = mtrx[3][2] - (mtrx[0][2] * mtrx[3][0]);
      mtrx[3][3] = mtrx[3][3] - (mtrx[0][3] * mtrx[3][0]);
      mtrx[3][4] = mtrx[3][4] - (mtrx[0][4] * mtrx[3][0]);
      mtrx[3][0] = mtrx[3][0] - (mtrx[0][0] * mtrx[3][0]);

      mtrx[1][2] = mtrx[1][2] / mtrx[1][1];
      mtrx[1][0] = mtrx[1][0] / mtrx[1][1];
      mtrx[1][3] = mtrx[1][3] / mtrx[1][1];
      mtrx[1][4] = mtrx[1][4] / mtrx[1][1];
      mtrx[1][1] = mtrx[1][1] / mtrx[1][1];

// TEST
   printf("\n   a	b	c	d	e   \n");
   printf("=====================================\n");
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[0][0], mtrx[0][1], mtrx[0][2], mtrx[0][3],
                                                      mtrx[0][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[1][0], mtrx[1][1], mtrx[1][2], mtrx[1][3],
                                                      mtrx[1][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[2][0], mtrx[2][1], mtrx[2][2], mtrx[2][3],
                                                      mtrx[2][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n\n", mtrx[3][0], mtrx[3][1], mtrx[3][2], mtrx[3][3],
                                                      mtrx[3][4]);

      mtrx[0][2] = mtrx[0][2] - (mtrx[1][2] * mtrx[0][1]);
      mtrx[0][0] = mtrx[0][0] - (mtrx[1][0] * mtrx[0][1]);
      mtrx[0][3] = mtrx[0][3] - (mtrx[1][3] * mtrx[0][1]);
      mtrx[0][4] = mtrx[0][4] - (mtrx[1][4] * mtrx[0][1]);
      mtrx[0][1] = mtrx[0][1] - (mtrx[1][1] * mtrx[0][1]);

      mtrx[2][0] = mtrx[2][0] - (mtrx[1][0] * mtrx[2][1]);
      mtrx[2][3] = mtrx[2][3] - (mtrx[1][3] * mtrx[2][1]);
      mtrx[2][2] = mtrx[2][2] - (mtrx[1][2] * mtrx[2][1]);
      mtrx[2][4] = mtrx[2][4] - (mtrx[1][4] * mtrx[2][1]);
      mtrx[2][1] = mtrx[2][1] - (mtrx[1][1] * mtrx[2][1]);

      mtrx[3][0] = mtrx[3][0] - (mtrx[1][0] * mtrx[3][1]);
      mtrx[3][3] = mtrx[3][3] - (mtrx[1][3] * mtrx[3][1]);
      mtrx[3][2] = mtrx[3][2] - (mtrx[1][2] * mtrx[3][1]);
      mtrx[3][4] = mtrx[3][4] - (mtrx[1][4] * mtrx[3][1]);
      mtrx[3][1] = mtrx[3][1] - (mtrx[1][1] * mtrx[3][1]);

      mtrx[2][0] = mtrx[2][0] / mtrx[2][2];
      mtrx[2][3] = mtrx[2][3] / mtrx[2][2];
      mtrx[2][1] = mtrx[2][1] / mtrx[2][2];
      mtrx[2][4] = mtrx[2][4] / mtrx[2][2];
      mtrx[2][2] = mtrx[2][2] / mtrx[2][2];

// TEST
   printf("\n   a	b	c	d	e   \n");
   printf("=====================================\n");
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[0][0], mtrx[0][1], mtrx[0][2], mtrx[0][3],
                                                      mtrx[0][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[1][0], mtrx[1][1], mtrx[1][2], mtrx[1][3],
                                                      mtrx[1][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[2][0], mtrx[2][1], mtrx[2][2], mtrx[2][3],
                                                      mtrx[2][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n\n", mtrx[3][0], mtrx[3][1], mtrx[3][2], mtrx[3][3],
                                                      mtrx[3][4]);

      mtrx[0][0] = mtrx[0][0] - (mtrx[2][0] * mtrx[0][2]);
      mtrx[0][3] = mtrx[0][3] - (mtrx[2][3] * mtrx[0][2]);
      mtrx[0][1] = mtrx[0][1] - (mtrx[2][1] * mtrx[0][2]);
      mtrx[0][4] = mtrx[0][4] - (mtrx[2][4] * mtrx[0][2]);
      mtrx[0][2] = mtrx[0][2] - (mtrx[2][2] * mtrx[0][2]);

      mtrx[1][0] = mtrx[1][0] - (mtrx[2][0] * mtrx[1][2]);
      mtrx[1][3] = mtrx[1][3] - (mtrx[2][3] * mtrx[1][2]);
      mtrx[1][1] = mtrx[1][1] - (mtrx[2][1] * mtrx[1][2]);
      mtrx[1][4] = mtrx[1][4] - (mtrx[2][4] * mtrx[1][2]);
      mtrx[1][2] = mtrx[1][2] - (mtrx[2][2] * mtrx[1][2]);

      mtrx[3][0] = mtrx[3][0] - (mtrx[2][0] * mtrx[3][2]);
      mtrx[3][3] = mtrx[3][3] - (mtrx[2][3] * mtrx[3][2]);
      mtrx[3][1] = mtrx[3][1] - (mtrx[2][1] * mtrx[3][2]);
      mtrx[3][4] = mtrx[3][4] - (mtrx[2][4] * mtrx[3][2]);
      mtrx[3][2] = mtrx[3][2] - (mtrx[2][2] * mtrx[3][2]);

      mtrx[3][0] = mtrx[3][0] / mtrx[3][3];
      mtrx[3][1] = mtrx[3][1] / mtrx[3][3];
      mtrx[3][4] = mtrx[3][4] / mtrx[3][3];
      mtrx[3][2] = mtrx[3][2] / mtrx[3][3];
      mtrx[3][3] = mtrx[3][3] / mtrx[3][3];

// TEST
   printf("\n   a	b	c	d	e   \n");
   printf("=====================================\n");
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[0][0], mtrx[0][1], mtrx[0][2], mtrx[0][3],
                                                      mtrx[0][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[1][0], mtrx[1][1], mtrx[1][2], mtrx[1][3],
                                                      mtrx[1][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[2][0], mtrx[2][1], mtrx[2][2], mtrx[2][3],
                                                      mtrx[2][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n\n", mtrx[3][0], mtrx[3][1], mtrx[3][2], mtrx[3][3],
                                                      mtrx[3][4]);

      mtrx[0][0] = mtrx[0][0] - (mtrx[3][0] * mtrx[0][3]);
      mtrx[0][1] = mtrx[0][1] - (mtrx[3][1] * mtrx[0][3]);
      mtrx[0][4] = mtrx[0][4] - (mtrx[3][4] * mtrx[0][3]);
      mtrx[0][2] = mtrx[0][2] - (mtrx[3][2] * mtrx[0][3]);
      mtrx[0][3] = mtrx[0][3] - (mtrx[3][3] * mtrx[0][3]);

      mtrx[1][0] = mtrx[1][0] - (mtrx[3][0] * mtrx[1][3]);
      mtrx[1][1] = mtrx[1][1] - (mtrx[3][1] * mtrx[1][3]);
      mtrx[1][4] = mtrx[1][4] - (mtrx[3][4] * mtrx[1][3]);
      mtrx[1][2] = mtrx[1][2] - (mtrx[3][2] * mtrx[1][3]);
      mtrx[1][3] = mtrx[1][3] - (mtrx[3][3] * mtrx[1][3]);

      mtrx[2][0] = mtrx[2][0] - (mtrx[3][0] * mtrx[2][3]);
      mtrx[2][1] = mtrx[2][1] - (mtrx[3][1] * mtrx[2][3]);
      mtrx[2][4] = mtrx[2][4] - (mtrx[3][4] * mtrx[2][3]);
      mtrx[2][2] = mtrx[2][2] - (mtrx[3][2] * mtrx[2][3]);
      mtrx[2][3] = mtrx[2][3] - (mtrx[3][3] * mtrx[2][3]);

// TEST
   printf("\na	b	c	d	e   \n");
   printf("=====================================\n");
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[0][0], mtrx[0][1], mtrx[0][2], mtrx[0][3],
                                                      mtrx[0][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[1][0], mtrx[1][1], mtrx[1][2], mtrx[1][3],
                                                      mtrx[1][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[2][0], mtrx[2][1], mtrx[2][2], mtrx[2][3],
                                                      mtrx[2][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n\n", mtrx[3][0], mtrx[3][1], mtrx[3][2], mtrx[3][3],
                                                      mtrx[3][4]);

      // 3) Display results
      printf("The row reduced (RREF) augmented matrix is: \n");
      printf("[ 1.000 0.000 0.000 0.000 | %lf ]\n", mtrx[0][4]);
      printf("[ 0.000 1.000 0.000 0.000 | %lf ]\n", mtrx[1][4]);
      printf("[ 0.000 0.000 1.000 0.000 | %lf ]\n", mtrx[2][4]);
      printf("[ 0.000 0.000 0.000 1.000 | %lf ]\n\n", mtrx[3][4]);

      printf("The best-fit Least squares equation is:\n\n");
      printf("%lf * x^0 + %lf * x^1 + %lf * x^2 + %lf * x^3\n\n", mtrx[0][4], mtrx[1][4], mtrx[2][4],
								  mtrx[3][4]);

// TEST
   printf("\n	a	b	c	d	e   \n");
   printf("=====================================\n");
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[0][0], mtrx[0][1], mtrx[0][2], mtrx[0][3],
						      mtrx[0][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[1][0], mtrx[1][1], mtrx[1][2], mtrx[1][3],
						      mtrx[1][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n", mtrx[2][0], mtrx[2][1], mtrx[2][2], mtrx[2][3],
						      mtrx[2][4]);
   printf("%-7.2f %-7.2f %-7.2f %-7.2f = %-7.2f\n\n", mtrx[3][0], mtrx[3][1], mtrx[3][2], mtrx[3][3],
                                                      mtrx[3][4]);
   }

   // 4th order
   else if (poly_ordr == 4) {
      printf("The coefficients (square) matrix 'A' is %i x %i with values: \n",
                                 poly_ordr + 1, poly_ordr + 1);
      
   }
   // 5th order
   else if (poly_ordr == 5) {
      printf("The coefficients (square) matrix 'A' is %i x %i with values: \n",
                                 poly_ordr + 1, poly_ordr + 1);
      
   }

   return 0;
}

#include <math.h>
double sum_x(struct data d[], int n, int k) {
   int m;
   double sum = 0;
   for (m=0; m<n; m++) {
      sum = sum + pow(d[m].x, k);
   }
   return sum;
}

double sum_y(struct data d[], int n, int k) {
   int m;
   double sum = 0;
   for (m=0; m<n; m++) {
      sum = sum + pow(d[m].x, k) * d[m].y;
   }
   return sum;
}
