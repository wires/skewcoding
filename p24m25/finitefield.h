/*
 * finitefield.h
 *
 *  Created on: Apr 6, 2011
 *      Author: nela
 */

#ifndef FINITEFIELD_H_
#define FINITEFIELD_H_

#define ARRAY_SIZE 13
#define MAX_DEGREE (ARRAY_SIZE - 1)

void copy_polynomial(int f[], int g[]);
void zero_polynomial(int f[]);
void print_polynomial(int f[]);
void random_polynomial(int f[], int d, int z, int seed);
int  next_polynomial(int f[], int k, int start_digit, int end_digit);

int is_zero(int f[]);

int field_size();

int add(int s, int t);
int sub(int s, int t);
int mult(int s, int t);
int divi(int s, int t);

void skew_add(int f[], int h[], int g[]);
void skew_sub(int f[], int h[], int g[]);
void skew_mult(int f[], int h[], int g[]);
int skew_div(int f[], int h[], int g[]);

int degree(int f[]);
int theta(int r, int a);


#endif /* FINITEFIELD_H_ */
