#include <stdio.h>

int main()
{
    int base = 0, exp = 0, mod = 0, aux = 1;
    long long res;
    printf("digite sua base: ");
    scanf("%d", &base);
    printf("Digite seu expoente: ");
    scanf("%d", &exp);
    printf("Digite o modulo: ");
    scanf("%d", &mod);
    int base1 = base;
    int exp1 = exp;
     
    while(exp1 > 0)
    {
        if(exp1 % 2 == 1)
            aux = (aux * base1) % mod;
        base1 = (base1 * base1) % mod;
        exp1 /= 2; 
    }
    
    res = aux % mod;


    printf("(%d^%d) mod %d = %d", base, exp, mod, res);
    return 0;
}