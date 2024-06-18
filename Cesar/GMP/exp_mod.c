#include <stdio.h>

int exp_mod(int base, int exp, int mod)
{
    int aux = 1;
    int base1 = base;
    int exp1 = exp;
     
    while(exp1 > 0)
    {
        if(exp1 % 2 == 1)
            aux = (aux * base1) % mod;
        base1 = (base1 * base1) % mod;
        exp1 /= 2; 
    }
    
    return aux % mod;
}