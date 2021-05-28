#include <stdio.h>
#define NY 7
#define NX 5


int main()
{
    int i, j;
    double Xos, Yos;
    for (i = NX-1; i >= 0; i--)
    {
        Xos = (double) i;
        for (j = 0; j <= NY - 1; j++)
        {
            Yos = (double) j;
            printf("(%.2f, %.2f)\t", Xos/(NX-1), Yos/(NY-1));
        }
        printf("\n");
    }
}