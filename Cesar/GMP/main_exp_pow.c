#include <stdio.h>
#include <gmp.h>

void pow_mod(mpz_t aux, mpz_t base, mpz_t exp, mpz_t mod)
{
    //Inicialização das variáveis
    mpz_t base1, exp1;

    //Dando valores às variáveis
    mpz_init_set(base1, base);
    mpz_init_set(exp1, exp);
    mpz_set_si(aux, 1);
    
    while(mpz_cmp_ui(exp1, 0) > 0)
    {
        
        if(mpz_odd_p(exp1)) // if(exp1 % 2 == 1)
        {
            mpz_mul(aux, base1, aux);
            mpz_mod(aux, aux, mod); //aux = (aux * base1) % mod;
        }
        mpz_mul(base1, base1, base1);
        mpz_mod(base1, base1, mod); //base1 = (base1 * base1) % mod;

        mpz_div_ui(exp1, exp1, 2);// exp1 /= 2; 
    }
    mpz_mod(aux, aux, mod); //return = aux % mod;
    mpz_clears(base1, exp1, NULL);
}

int main() {
    // Criando variáveis
    mpz_t q, p, n, phi, e, d, aux, s, t, exp_mod_resul, mult, mod;
    unsigned long seed; // Inicializando a seed

    // Iniciando as variáveis
    mpz_inits(q, p, n, phi, e, d, aux, s, t, exp_mod_resul, mult, mod, NULL);

    // Inicializando o gerador de números aleatórios
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate, seed);

    // Gerando 'q' e 'p' como um número aleatório
    mpz_urandomb(aux, rstate, 128);
    mpz_nextprime(q, aux);
    gmp_printf("q =   %Zd\n", q);

    mpz_urandomb(aux, rstate, 128);
    mpz_nextprime(p, aux);
    gmp_printf("p =   %Zd\n", p);

    // Calculando 'n' e 'phi'
    mpz_mul(n, q, p);
    gmp_printf("n =   %Zd\n", n);

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
    gmp_printf("e =   %Zd\n", e);

    // Calculando 'd'
    mpz_gcdext(s, d, t, e, phi);
    if(mpz_cmp_ui(d, 0) < 0)
    {
        mpz_add(d, d, phi);
    }
    gmp_printf("d =   %Zd\n", d);
    gmp_printf("s =   %Zd\n", s);
    gmp_printf("t =   %Zd\n", t);
    
    // Checando 'd' ---- mod DEVE ser igual a 1 -----
    mpz_mul(mult, e, d);
    mpz_mod(mod, mult, phi);
    gmp_printf("mod = %Zd\n", mod);


    //Procedimento de encriptar e deseencriptar

    mpz_t env, rec, crip;
    mpz_inits(env, rec, crip, NULL);


    mpz_set_ui(env, 12345);
    gmp_printf("Mensagem enviada: %Zd\n", env);
    pow_mod(crip, env, e, n);
    gmp_printf("Mensagem encriptada: %Zd\n", crip);
    pow_mod(rec, crip, d, n);
    gmp_printf("Mensagem recebida: %Zd\n", rec);




    // Liberar recursos
    mpz_clears(q, p, n, phi, e, d, aux, s, t, exp_mod_resul, mult, mod, q_minus_1, p_minus_1, NULL);
    gmp_randclear(rstate);

    return 0;
}