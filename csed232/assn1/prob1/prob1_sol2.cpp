#include <bitset>
#include <cstdio>
#include <cstdlib>

using std::FILE;
using std::atoi;
using std::bitset;
using std::fclose;
using std::fopen;
using std::fprintf;
using std::fscanf;
using std::printf;
using std::size_t;

constexpr size_t SIEVE_MAX = 100000;

bitset<SIEVE_MAX + 1> sieve();

int main(int argc, char **argv) {
  bitset<SIEVE_MAX + 1> is_composite = sieve();
  if (argc > 1)
    for (size_t i = 1; i < argc; i++)
      printf("%c ", is_composite[atoi(argv[i])]? 'n' : 'y');
  else {
    FILE *fin = fopen("input.txt", "r"),
         *fout = fopen("output.txt", "w");
    int num;
    char delim = ' ';
    while (delim == ' ') {
      fscanf(fin, "%d%c", &num, &delim);
      fprintf(fout, "%c ", is_composite[num]? 'n' : 'y');
    }
    fclose(fin);
    fclose(fout);
  }
  return 0;
}

bitset<SIEVE_MAX + 1> sieve() {
  bitset<SIEVE_MAX + 1> is_composite;
  for (size_t i = 2; i <= SIEVE_MAX; i++)
    if (!is_composite[i])
      for (size_t j = i * 2; j <= SIEVE_MAX; j += i)
        is_composite[j] = true;
  return is_composite;
}
