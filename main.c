#include <inttypes.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BIAS 1023
#define PI 3.14159265358979323846264338327950288

static inline void print_double(uint64_t x, int n_bits) {
  for (int i = n_bits - 1; i >= 0; --i) {
    putchar((x & (1ULL << i) ? '1' : '0'));
    if (i == 52 || i == 63) {
      putchar(' ');
    }
  }
  putchar('|');
}

int main(void) {
  // exemplo: 7.34375 = 4 + 2 + 1 + 1/4 + 1/16 + 1/32
  double exemplo;
  scanf("%lf", &exemplo);
  uint64_t normal;
  memcpy(&normal, &exemplo, sizeof(normal));
  // print_binary(normal, 64);

  // extrair campos com máscaras corretas
  uint64_t sign = (normal >> 63) & 1ULL;
  uint64_t exp_raw = (normal >> 52) & 0x7FFULL; // 11 bits
  uint64_t mant = normal & ((1ULL << 52) - 1);

  print_double(sign, 1);
  print_double(exp_raw, 11);
  print_double(mant, 52);

  int normalized = (exp_raw != 0);
  int E = normalized ? (int)exp_raw - BIAS : 1 - BIAS;

  uint64_t sig = normalized ? ((1ULL << 52) | mant) : mant;
  int sig_bits = normalized ? 53 : 52;

  /*printf("\nsign = %" PRIu64 "\n", sign);
  printf("exp_raw = %" PRIu64 "  (E = %d)\n", exp_raw, E);
  printf("mantissa raw: ");*/

  putchar('\n');
  for (int i = sig_bits - 1; i >= 0; --i) {
    if ((sig >> i) & 1) {
      printf(" %c 2^%d", (i != (sig_bits - 1) ? '+' : ' '), (int)(E - 52 + i));
    }
  }
  putchar('\n');

  return 0;
}
