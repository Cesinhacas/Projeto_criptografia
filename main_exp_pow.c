#include <stdio.h>
#include <gmp.h>

int pow_mod(int base, int exp, int mod)
{
    int base1 = base;
    int exp1 = exp;
    int aux = 1;
     
    while(exp1 > 0)
    {
        if(exp1 % 2 == 1)
            aux = (aux * base1) % mod;
        base1 = (base1 * base1) % mod;
        exp1 /= 2; 
    }
    
    return aux % mod;
}

int main() {
    // Criando variáveis
    mpz_t q, p, n, phi, e, d, aux, s, t, exp_mod_resul, mult, mod;
    unsigned long seed; // Inicialize a seed

    // Iniciando as variáveis
    mpz_inits(q, p, n, phi, e, d, aux, s, t, exp_mod_resul, mult, mod, NULL);

    // Inicializando o gerador de números aleatórios
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate, seed);

    // Gerando 'q' e 'p' como um número aleatório
    mpz_urandomb(aux, rstate, 8);
    mpz_nextprime(q, aux);
    gmp_printf("q = %Zd\n", q);

    mpz_urandomb(aux, rstate, 8);
    mpz_nextprime(p, aux);
    gmp_printf("p = %Zd\n", p);

    // Calculando 'n' e 'phi'
    mpz_mul(n, q, p);
    gmp_printf("n = %Zd\n", n);

    // phi = (q-1)*(p-1)
    mpz_t q_minus_1, p_minus_1;
    mpz_inits(q_minus_1, p_minus_1, NULL);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_mul(phi, q_minus_1, p_minus_1);
    gmp_printf("phi = %Zd\n", phi);

    // Calculando 'e'
    mpz_urandomm(aux, rstate, phi);
    mpz_nextprime(e, aux);
    gmp_printf("e = %Zd\n", e);

    // Calculando 'd'
    mpz_gcdext(s, d, t, e, phi);
    gmp_printf("d = %Zd\n", d);
    gmp_printf("s = %Zd\n", s);
    gmp_printf("t = %Zd\n", t);
    
    // Checando 'd' ---- mod DEVE ser igual a 1 -----
    mpz_mul(mult, e, d);
    mpz_mod(mod, mult, phi);
    gmp_printf("mod = %Zd\n", mod);


    //Procedimento de encriptar e deseencriptar

    int crip = 1, env, e1, n1, rec = 1, d1;
    env = 1234;
    e1 = mpz_get_si(e);
    n1 = mpz_get_si(n);
    d1 = mpz_get_si(d);

    printf("Mensagem enviada: %d\n", env);
    crip = pow_mod(env, e1, n1);
    printf("Mensagem encriptada: %d\n", crip);
    rec = pow_mod(crip, d1, n1);
    printf("Mensagem recebida: %d\n", rec);




    // Liberar recursos
    mpz_clears(q, p, n, phi, e, d, aux, s, t, exp_mod_resul, mult, mod, q_minus_1, p_minus_1, NULL);
    gmp_randclear(rstate);

    return 0;
}
