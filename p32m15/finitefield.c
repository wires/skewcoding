/*
 * finitefield.c
 *
 *  Created on: Apr 13, 2011
 *      Author: nela
 */
#include <stdio.h>
#include <stdlib.h>

#ifndef __FIELD_H
#define __FIELD_H
#include "fdefs/fdefs_8.h"
#endif

#include "finitefield.h"

// field size
int field_size()
{
	return FIELD_SIZE;
}

// zero out a polynomial
void zero_polynomial(int f[])
{
	int i;

	for (i = 0; i < ARRAY_SIZE; i++)
		f[i] = 0;
};

// check if polynomial is zero, returns 1 if it is
int is_zero(int f[])
{
   int i;

   // just check that all coefficients are zero
   for (i = 0; i < ARRAY_SIZE; i++)
       if(f[i] != 0)
           return 0;

   return 1;
};


// copy f into g
void copy_polynomial(int f[], int g[])
{
	int i;

	for (i = 0; i < ARRAY_SIZE; i++)
			f[i] = g[i];
};

void print_polynomial(int f[])
{
	int d = degree(f);
	int i;
	for(i = 0; i < d+1; i++)
		fprintf(stderr, "%d,", f[i]);

	fprintf(stderr, " degree=%i\n", d);
}

// write into f a random polynomial taken from F_z of degree d
void random_polynomial(int f[], int d, int z, int seed)
{
	srand(seed);

	int i;
	for(i = 0; i <= d; i++)
		f[i] = rand() % z; // in F_z

	// to make sure never to have a zero degree polynomial
	f[1] = 1;

}

// next polynomial over F_k, returns nonzero if
// MAX_DEGREE reached; i.e. all polynomials are enumerated
int next_polynomial(int f[], int k, int start_digit, int end_digit)
{
    int i;

    for(i = start_digit; i < end_digit; i++)
    {
        // check if i-th digit is not going to overflow
        if(f[i] < (k - 1))
        {
            // increment "i'th digit"
            f[i] += 1;
            return 0;
        }
        else
        {
            // incrementing would overflow, thus carry
            f[i] = 0;
        }
    }

    // enumerated all polynomials
    return 1;
}

/*
 * Operations on elements of finite fields
 */
int add(int s, int t)
{
	return field_add[(FIELD_SIZE*s)+t];
}

int sub(int s, int t)
{
	return field_sub[(FIELD_SIZE*s)+t];
}

int mult(int s, int t)
{
	return field_mul[(FIELD_SIZE*s)+t];
}

int divi(int s, int t)
{
	return field_div[(FIELD_SIZE*s)+t];
}

/*
 * Operations on polynomials over finite fields
 */
void skew_add(int f[], int h[], int g[])
{
	int i;
	for (i=0; i<ARRAY_SIZE; i++)
		f[i]=add(h[i],g[i]);
}

void skew_sub(int f[], int h[], int g[])
{
	int d = ARRAY_SIZE;
	int i;
	for (i=0; i<d; i++)
		f[i]=sub(h[i],g[i]);
}

// skew multiplication: pass two polynomials h and g. returns their skew product
void skew_mult(int f[], int g[], int h[])
{
	int i,j;
	for (i=0; i<degree(h)+1; i++)
        for (j=0; j<degree(g)+1; j++)
        {
//        	fprintf(stderr, "s=h[i]=%i t=%i", h[i], theta(i,g[j]));
        	f[i+j] = add(f[i+j], mult(h[i], theta(i,g[j])));
//       	printf("f[%i+%i]=%i \n", i,j,f[i+j]);
//        	printf("h[%i]=%i", i, h[i]);
//        	printf("theta^i(g(j))=%i\n", theta(i,g[j]));
        }
}

// returns the degree of a polynomial
int degree(int f[])
{
	int i;

	// going backwards in array to find a first nonzero entry
	for (i = ARRAY_SIZE - 1; i >= 0; i--)
		if (f[i] != 0)
			return i;

	return 0; // zero polynomial
}

int theta(int r, int a)
{
    /*	r=power of theta
		a=element of field on which we are applying the automorphism theta
		p=definition of theta: theta(a)=a^p
    */
//	printf("r=%i", r);
//	printf("parity of r=%i", r % 2);
	if ((r%2) == 1)//if r is odd
		return mult(a,a);
	else
		return a;
}

// we skew divide f by g and write the result into h (which we assume to be zero'd out before calling this method)
// we return the degree of the remainder
int skew_div(int h[], int f[], int g[])
{
	int f1[ARRAY_SIZE];
	int f2[ARRAY_SIZE];

	zero_polynomial(f1);
	zero_polynomial(f2);

	int df = degree(f);
	int dg = degree(g);

	copy_polynomial(f2, f);
	int df2 = degree(f2);


	while(df2 >= dg)
	{
		h[df2-dg] = divi(f2[df2], theta(df2-dg, g[dg]));

		//fprintf(stderr, "df2= %i, dh=%i ", df2, dg);

		//skew_mult(f1, h, g);
		//Wrong: I do not multiply all of h with g, but only the term of h computed in the current iteration
		//namely, h[df2-dg] term.

		int i= df2-dg;
		int j;
		zero_polynomial(f1);
		for (j=0; j<degree(g)+1; j++)
		{
		   	f1[i+j] = add(f1[i+j], mult(h[i], theta(i,g[j])));
		}

		skew_sub(f2, f2, f1);
		df2 = degree(f2);
		//fprintf(stderr, "df2= %i", df2);
	}

	return df2;
}
