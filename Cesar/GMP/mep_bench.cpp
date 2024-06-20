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

int cryp()
{
    // Criando variáveis
    mpz_t q, p, n, phi, e, d, aux, s, t, mult, mod;
    unsigned long seed; // Inicializando a seed

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

    // Procedimento de encriptar e deseencriptar
    mpz_t env, rec, crip;
    mpz_inits(env, rec, crip, NULL);

    mpz_urandomb(env, rstate, 128);
    pow_mod(crip, env, e, n);
    pow_mod(rec, crip, d, n);

    // Liberar recursos
    mpz_clears(q, p, n, phi, e, d, aux, s, t, mult, mod, q_minus_1, p_minus_1, env, rec, crip, NULL);
    gmp_randclear(rstate);
    return 0;
}

// Função de benchmark
void BM_CryptoBenchmark(benchmark::State& state) {
    for (auto _ : state) {
        cryp();
    }
}

// Registra a função de benchmark
BENCHMARK(BM_CryptoBenchmark);

// Define o ponto de entrada do Google Benchmark
BENCHMARK_MAIN();