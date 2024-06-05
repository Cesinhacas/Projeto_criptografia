#include <stdio.h>
#include <gmp.h>

int main()
{
    mpz_t msg, d, n, aux;
    mpz_inits(msg, d, n, NULL);
    mpz_set_si(d, 73207625);
    mpz_set_ui(n, -254117177);

    gmp_printf("insira sua mensagem: ");
    gmp_scanf("%Zd", msg);
    mpz_powm(aux, msg, d, n);
    gmp_printf("Mensagem enviada: %Zd", aux);
    
}