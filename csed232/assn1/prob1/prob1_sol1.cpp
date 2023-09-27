#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

using std::atoi;
using std::freopen;
using std::printf;
using std::scanf;
using std::size_t;
using std::sqrt;

bool is_prime(uint64_t num);

int main(int argc, char **argv) {
  if (argc > 1)
    for (size_t i = 1; i < argc; i++)
      printf("%c ", is_prime(atoi(argv[i]))? 'y' : 'n');
  else {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int num;
    char delim = ' ';
    while (delim == ' ') {
      scanf("%d%c", &num, &delim);
      printf("%c ", is_prime(num)? 'y' : 'n');
    }
  }
  return 0;
}

bool is_prime(uint64_t num) {
  uint32_t lim = sqrt(num);
  for (size_t i = 2; i <= lim; i++)
    if (!(num % i))
      return false;
  return true;
}
