#include <stdio.h>
#include <gmp.h>

int gcdext(mpz_t g, mpz_t a, mpz_t b, mpz_t x, mpz_t y)
{
    if (mpz_cmp_ui(a, 0) == 0)
    {
        mpz_set_ui(x, 0);
        mpz_set_ui(y, 1);
        mpz_set(g, b);
        return 0;
    }

    mpz_t x1, y1, gcd, aux, div, mul, sub;
    mpz_inits(x1, y1, gcd, aux, div, sub, mul, NULL);
    mpz_mod(aux, b, a);
    gcdext(gcd, aux, a, x1, y1);
    
    mpz_div(div, b, a);
    mpz_mul(mul, div, x1);
    mpz_sub(x, y1, mul);

    mpz_set(y, x1);

    mpz_set(g, gcd);
    mpz_clears(x1, y1, gcd, aux, div, mul, sub, NULL);
    return 0;
}

void main()
{
    mpz_t a, b, gcd, s, t;
    mpz_inits(a, b, s, t, gcd, NULL);

    gmp_printf("Type a number: ");
    gmp_scanf("%Zd", a);
    gmp_printf("Type another number: ");
    gmp_scanf("%Zd", b);

    gcdext(gcd, a, b, s, t);

    gmp_printf("The greatest comum divisor of %Zd and %Zd is: %Zd", a, b, gcd);
}