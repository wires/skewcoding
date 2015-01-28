#include "bsp.h"
#include "finitefield.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NR_PROCESSORS 12

void dostuff()
{
    int i, j, m;

    int completed;

    int f[ARRAY_SIZE]; // global counter, only used by P(0)

    int g[ARRAY_SIZE]; // local counter
    int h[ARRAY_SIZE]; // x^n - 1
    int r[ARRAY_SIZE]; // rest term

    int f1[ARRAY_SIZE];
    int f2[ARRAY_SIZE];
    int f3[ARRAY_SIZE];

    // keep track of us being done
    completed = -1;

    // field_size()^4 polynomials to each processor
    m = 4;

    bsp_begin(NR_PROCESSORS);

    bsp_push_reg(&g, ARRAY_SIZE*sizeof(int));
    bsp_push_reg(&completed, sizeof(int));

    zero_polynomial(f);
    zero_polynomial(g);
    zero_polynomial(h);


    // set h = x^n ...
    h[MAX_DEGREE] = 1;

    // ... -1, works only for fields of size power of 2
    h[0] = field_size() - 1;

    bsp_sync();

    while(1)
    {

        if(bsp_pid() == 0)
        {
            // distribute starting polynomials to all processors
            for(i = 0; i < NR_PROCESSORS; i++)
            {
		//print_polynomial(f);

                // send current polynomial to processor i
                bsp_put(i, &f, &g, 0, ARRAY_SIZE*sizeof(int));

                // get next start polynomial (ie. increment with field_size()^m)
                if(next_polynomial(f, field_size(), ARRAY_SIZE - m, ARRAY_SIZE))
                {
                    // we enumerated all polynomials, work should start
                    // at processor P(i)
                    completed = i;

                    // tell other processors we are done
                    for(j = 0; j < NR_PROCESSORS; j++)
                        bsp_put(j, &completed, &completed, 0, sizeof(int));

                    break;
                }
            }
        }

        // communicate
        bsp_sync();

        // see if we need to do work
        if((completed == -1) || (bsp_pid() <= completed))
        {
            while(1)
            {
		// skip polynomials of degree 0
		if(degree(g) != 0)
		{
			// clear the rest
			zero_polynomial(r);

			//skew division of h by g, the result is r:
			if(skew_div(r, h, g) == 0)
			{
			    // print divisor if it's zero
			    //fprintf(stderr, "P(%d) -> found divisor, ", bsp_pid());
			    print_polynomial(g);
			}
		}

                // next polynomial
                if(next_polynomial(g, field_size(), 0, m))
                    // done with all polygons for this sub-block
                    break;
            }
        }

        bsp_sync();

        // if work is done, exit the main loop
        if(completed != -1)
            break;
    }

    bsp_end();
}

void main(int argc, char **argv)
{
    bsp_init(dostuff, argc, argv);

    dostuff();

    exit(0);
}
