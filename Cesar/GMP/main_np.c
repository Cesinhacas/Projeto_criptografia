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
void NextPrime(mpz_t prime, mpz_t num)
{
    int test = 0;
    
    mpz_set(prime, num);
    mpz_add_ui(prime, prime, 1);
    test = mpz_probab_prime_p(prime, 50);

    while(test <= 0)
    {
        test = mpz_probab_prime_p(prime, 50);
        if(test == 0)
            mpz_add_ui(prime, prime, 1);
    }
}
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

void main() {
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
    mpz_urandomb(aux, rstate, 1024);
    NextPrime(q, aux);
    gmp_printf("q =   %Zd\n", q);

    mpz_urandomb(aux, rstate, 1024);
    NextPrime(p, aux);
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
    NextPrime(e, aux);
    gmp_printf("e =   %Zd\n", e);

    // Calculando 'd'
    gcdext(s, e, phi, d, t);
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


    mpz_urandomb(env, rstate, 512);;
    gmp_printf("Mensagem enviada: %Zd\n", env);
    pow_mod(crip, env, e, n);
    gmp_printf("Mensagem encriptada: %Zd\n", crip);
    pow_mod(rec, crip, d, n);
    gmp_printf("Mensagem recebida: %Zd\n", rec);




    // Liberar recursos
    mpz_clears(q, p, n, phi, e, d, aux, s, t, exp_mod_resul, mult, mod, q_minus_1, p_minus_1, NULL);
    gmp_randclear(rstate);
}