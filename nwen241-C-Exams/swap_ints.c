#include <stdio.h>

void swap_ptr(int **ppp, int **ppq);

int main(void)
{
    int p = 11, q = 22;
    int *ptrp = &p, *ptrq = &q;

    printf("*ptrp was: %d\n", *ptrp);
    printf("*ptrq was: %d\n", *ptrq);

    int **ppp = &ptrp, **ppq = &ptrq;
    swap_ptr(ppp, ppq);               /* &ptrp, &ptrq passed */
                                      /* to swap_ptr() */

    printf("*ptrp is: %d\n", *ptrp);
    printf("*ptrq is: %d\n", *ptrq);

    return 0;
}

void swap_ptr(int **ppp, int **ppq)
{
    int *temp = *ppp;
    *ppp = *ppq;
    *ppq = temp;
}