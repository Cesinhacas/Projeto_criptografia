#include <stdio.h>
#include <gmp.h>

void main()
{
    mpz_t num, prime;
    int test = 0;

    mpz_inits(num, prime, NULL);
    gmp_printf("Type a number: ");
    gmp_scanf("%Zd", num);

    mpz_set(prime, num);
    mpz_add_ui(prime, prime, 1);
    test = mpz_probab_prime_p(prime, 3);

    while(test <= 0)
    {
        test = mpz_probab_prime_p(prime, 3);
        if(test == 0)
            mpz_add_ui(prime, prime, 1);
    }

    gmp_printf("The next prime of the number typed is: %Zd", prime);
}