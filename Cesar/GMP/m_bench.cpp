#include <gmp.h>
#include <benchmark/benchmark.h>

int cryp()
{
    // Criando variáveis
    mpz_t q, p, n, phi, e, d, aux, s, t, mult, mod;
    unsigned long seed; // Inicialize a seed
    
    // Iniciando as variáveis
    mpz_inits(q, p, n, phi, e, d, aux, s, t, mult, mod, NULL);

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


    //Procedimento de encriptar e deseencriptar
    mpz_t env, rec, crip;
    mpz_inits(env, rec, crip, NULL);

    mpz_urandomb(env, rstate, 128);
    mpz_powm(crip, env, e, n);
    mpz_powm(rec, crip, d, n);

    // Liberar recursos
    mpz_clears(q, p, n, phi, e, d, aux, s, t, mult, mod, q_minus_1, p_minus_1, env, rec, crip, NULL);
    gmp_randclear(rstate);
    return 0;
}

void BM_CryptoBenchmark(benchmark::State& state) {
    for (auto _ : state) {
        cryp();        
    }
}

// Registra a função de benchmark
BENCHMARK(BM_CryptoBenchmark)->Unit(benchmark::kMillisecond);

// Define o ponto de entrada do Google Benchmark
BENCHMARK_MAIN();
