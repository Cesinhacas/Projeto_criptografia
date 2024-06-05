#include <stdio.h>
#include <gmp.h>

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
    mpz_t env, rec, crip;
    mpz_inits(env, rec, crip, NULL);
    mpz_set_ui(env, 1234);
    gmp_printf("Mensagem enviada: %Zd\n", env);
    mpz_powm(crip, env, e, n);
    gmp_printf("mensagem encriptada: %Zd\n", crip);
    mpz_powm(rec, crip, d, n);
    gmp_printf("Mensagem recebida: %Zd\n", rec);




    // Liberar recursos
    mpz_clears(q, p, n, phi, e, d, aux, s, t, exp_mod_resul, mult, mod, q_minus_1, p_minus_1, env, rec, crip, NULL);
    gmp_randclear(rstate);

    return 0;
}
