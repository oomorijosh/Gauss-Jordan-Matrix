/* Project 2
 * ===========
 *    Name: Joshua Omori
 *    Class: EE 160
 *
 * Current objective: (v1.01)
 * ====================
 *    In order to get the project to somewhat work, the collection of inputs
 *    is firstly needed.
 *    (The calculations can come later :,) <= Literally me in the near future)
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
 *
 * Version Info:
 * ===============
 *    v1.01 Creation of the "get inputs"
 *    
 *
 *    Compile Date: Nov 30, 2021
 */


#include <stdio.h>
#include <math.h>

struct data {
   double x;
   double y;
};

int main(void) {

// PART 1: Get input from user

   // 1) create variables

   int poly_ordr;
   char fn[100], chr;
   FILE *fp1;
   struct data d[50];
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


// PART 2: Calculations... Done later

   return 0;
}


