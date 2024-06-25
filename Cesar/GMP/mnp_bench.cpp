#include <stdio.h>
#include <gmp.h>
#include <benchmark/benchmark.h>

void pow_mod(mpz_t aux, mpz_t base, mpz_t exp, mpz_t mod)
 {
    //Inicialização das variáveis
    mpz_t base1, exp1;

    //Dando valores às variáveis
    mpz_init_set(base1, base);
    mpz_init_set(exp1, exp);
    mpz_set_si(aux, 1);

    while (mpz_cmp_ui(exp1, 0) > 0) {
        if (mpz_odd_p(exp1)) {
            mpz_mul(aux, base1, aux);
            mpz_mod(aux, aux, mod);
        }
        mpz_mul(base1, base1, base1);
        mpz_mod(base1, base1, mod);
        mpz_div_ui(exp1, exp1, 2);
    }
    mpz_mod(aux, aux, mod);
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
int param(mpz_t n, mpz_t e, mpz_t d)
{
    // Criando variáveis
    mpz_t q, p, phi, aux, s, t, exp_mod_resul, mult, mod;
    unsigned long seed; // Inicializando a seed

    // Iniciando as variáveis
    mpz_inits(q, p, n, phi, e, d, aux, s, t, exp_mod_resul, mult, mod, NULL);

    // Inicializando o gerador de números aleatórios
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate, seed);

    // Gerando 'q' e 'p' como um número aleatório
    mpz_urandomb(aux, rstate, 512);
    NextPrime(q, aux);

    mpz_urandomb(aux, rstate, 512);
    NextPrime(p, aux);

    // Calculando 'n' e 'phi'
    mpz_mul(n, q, p);
    
    // phi = (q-1)*(p-1)
    mpz_t q_minus_1, p_minus_1;
    mpz_inits(q_minus_1, p_minus_1, NULL);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_mul(phi, q_minus_1, p_minus_1);

    // Calculando 'e'
    mpz_urandomm(aux, rstate, phi);
    NextPrime(e, aux);

    // Calculando 'd'
    gcdext(s, e, phi, d, t);
    if(mpz_cmp_ui(d, 0) < 0)
    {
        mpz_add(d, d, phi);
    }
    
    mpz_clears(q, p, phi, aux, s, t, mult, mod, q_minus_1, p_minus_1, NULL);
    gmp_randclear(rstate);
    
    return 0;
}
int cryp(mpz_t e, mpz_t d, mpz_t n, mpz_t env)
{
    //Procedimento de encriptar e deseencriptar
    mpz_t rec, crip;
    mpz_inits(rec, crip, NULL);

    pow_mod(crip, env, e, n);
    pow_mod(rec, crip, d, n);

    // Liberar recursos
    mpz_clears(rec, crip, NULL);

    return 0;
}
// Função de benchmark
void BM_param(benchmark::State& state)
{
    mpz_t n, e, d;
    mpz_inits(n, e, d, NULL);
    for (auto _ : state) {
        param(n, e, d);        
    }
    mpz_clears(n, e, d, NULL);
}

void BM_cypher(benchmark::State& state)
{
    mpz_t e, d, n, env;
    mpz_inits(n, e, d, env, NULL);
    unsigned long seed;
    param(n, e, d);
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate, seed);

    for (auto _ : state) {
        mpz_urandomb(env, rstate, 128);
        cryp(e, d, n, env);
    }
    mpz_clears(e, d, n, env, NULL);
}

// Registra a função de benchmark
BENCHMARK(BM_param)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_cypher)->Unit(benchmark::kMillisecond);

// Define o ponto de entrada do Google Benchmark
BENCHMARK_MAIN();