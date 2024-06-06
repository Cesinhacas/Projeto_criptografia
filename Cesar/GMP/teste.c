#include <stdio.h>
#include <gmp.h>


int main()
{
    //Criando variáveis
    mpz_t q, p, n, phi, e, d, aux, s, t, exp_mod_resul, mult, mod;
    unsigned long seed;

    //iniciando as variáveis
    mpz_inits(q, p, n, phi, e, d, aux, s, t, exp_mod_resul, mult, mod);

    //Inicializando o gerador de números aleatórios
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate, seed);

    //Gerando 'q' e 'p' como um número aleatório
    mpz_urandomb(aux, rstate, 8);
    mpz_nextprime(q, aux);

    mpz_urandomb(aux, rstate, 8);
    mpz_nextprime(p, aux);


    //Calculando 'n' e 'phi'
    mpz_mul(n,q,p);
    mpz_mul(phi,(q-1),(p-1));


    //Calculando 'e'
    mpz_urandomm(aux, rstate, phi);
    mpz_nextprime(e, aux);


    //calculando 'd'
    mpz_gcdext(d, s, t, e, phi);
    
    //checando 'd' ---- mod DEVE ser igual a 1 -----
    mpz_mul(mult, e, d);
    mpz_mod(mod, mult, phi);    
    gmp_printf("%d", mod);

    return(0);

}
