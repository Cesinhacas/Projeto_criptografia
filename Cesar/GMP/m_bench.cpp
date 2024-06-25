#include <gmp.h>
#include <benchmark/benchmark.h>

int param(mpz_t n, mpz_t e, mpz_t d)
{
    // Criando variáveis
    mpz_t q, p, phi, aux, s, t, mult, mod, env;
    unsigned long seed; // Inicialize a seed
    
    // Iniciando as variáveis
    mpz_inits(q, p, phi, aux, s, t, mult, mod, env, NULL);

    // Inicializando o gerador de números aleatórios
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate, seed);

    // Gerando 'q' e 'p' como um número aleatório
    mpz_urandomb(aux, rstate, 512);
    mpz_nextprime(q, aux);

    mpz_urandomb(aux, rstate, 512);
    mpz_nextprime(p, aux);

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
    mpz_nextprime(e, aux);
    

    // Calculando 'd'
    mpz_gcdext(s, d, t, e, phi);
    if (mpz_cmp_ui(d, 0) < 0) {
        mpz_add(d, d, phi);
    }


    mpz_clears(q, p, phi, aux, s, t, mult, mod, q_minus_1, p_minus_1, env, NULL);

    return 0;
}

int cryp(mpz_t e, mpz_t d, mpz_t n, mpz_t env)
{
    //Procedimento de encriptar e deseencriptar
    mpz_t rec, crip;
    mpz_inits(rec, crip, NULL);
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);

    mpz_powm(crip, env, e, n);
    mpz_powm(rec, crip, d, n);

    // Liberar recursos
    mpz_clears(rec, crip, NULL);
    gmp_randclear(rstate);
    return 0;
}

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

    for(auto _: state)
    {
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
