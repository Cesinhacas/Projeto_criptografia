#include <stdio.h>
#include <gmp.h>

int main() {
    mpz_t x;
    mpz_init(x);
    mpz_set_ui(x, 123);
    gmp_printf("x = %Zd\n", x);
    mpz_clear(x);
    return 0;
}
