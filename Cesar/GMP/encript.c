#include <stdio.h>
#include <gmp.h>

int main()
{
    mpz_t msg, e, n, aux;
    mpz_inits(msg, e, n, NULL);
    mpz_set_ui(e, 873283447);
    mpz_set_ui(n, 1869722749);

    gmp_printf("insira sua mensagem:");
    gmp_scanf("%Zd", msg);
    mpz_powm(aux, msg, e, n);
    gmp_printf("Sua mensagem encriptada talvez seja: %Zd", aux);
    
}