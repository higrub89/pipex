#include "../inc/pipex.h"

int main(int ac, char **av)
{
    if(ac > 1)
    {
        int n = 0;
        int num1 = atoi(av[1]);
        int num2 = atoi(av[2]);
        if (av[3][0] == '+')
            n = num1 + num2;
        printf("El resultado de la suma es: \n");
        printf("%i \n", n);
    }
    return (0);
}