#include <cstdio>
#include <cstdlib>
#include <cstring>

using std::FILE;
using std::atoi;
using std::fclose;
using std::fopen;
using std::fprintf;
using std::fscanf;
using std::memset;
using std::size_t;

inline constexpr bool validate(int N, int M, int S, int D) {
  return N >= 1 && N <= 10
      && M >= 1 && M <= 10
      && S >= -10 && S <= 10
      && D >= -10 && D <= 10;
}

void solve(int (*arr)[10], int N, int M, int S, int D);
void print(FILE *fout, int (*arr)[10], int N, int M);

int main(int argc, char **argv) {
  int N, M, S, D;
  int arr[10][10] = {};
  if (argc > 1) {
    N = atoi(argv[1]),
    M = atoi(argv[2]),
    S = atoi(argv[3]),
    D = atoi(argv[4]);
    if (validate(N, M, S, D)) {
      solve(arr, N, M, S, D);
      print(stdout, arr, N, M);
    } else fprintf(stderr, "[!] Invalid input: (N, M, S, D) = (%d, %d, %d, %d)\n", N, M, S, D);
  } else {
    FILE *fin = fopen("input.txt", "r"),
         *fout = fopen("output.txt", "w");
    while (fscanf(fin, "%d %d %d %d", &N, &M, &S, &D) != EOF)
      if (validate(N, M, S, D)) {
        solve(arr, N, M, S, D);
        print(fout, arr, N, M);
        memset(&arr[0][0], 0, 100 * sizeof(int));
      } else fprintf(stderr, "[!] Invalid input: (N, M, S, D) = (%d, %d, %d, %d)\n", N, M, S, D);
    fclose(fin);
    fclose(fout);
  }
  return 0;
}

void solve(int (*arr)[10], int N, int M, int S, int D) {
  constexpr int dx[4] = {1, 0, -1, 0},
                dy[4] = {0, 1, 0, -1};
  size_t cx = 0,
         cy = 0,
         dir = 0;
  for (size_t i = 0; i < N * M; i++) {
    arr[cx][cy] = S + D * i;
    if (cx + dx[dir] < 0 || cx + dx[dir] >= M
     || cy + dy[dir] < 0 || cy + dy[dir] >= N
     || arr[cx + dx[dir]][cy + dy[dir]])
      dir = (dir + 1) % 4;
    cx += dx[dir],
    cy += dy[dir];
  }
}

void print(FILE *fout, int (*arr)[10], int N, int M) {
  for (size_t y = 0; y < N; y++) {
    for (size_t x = 0; x < M; x++)
      fprintf(fout, "%d ", arr[x][y]);
    fprintf(fout, "\n");
  }
  fprintf(fout, "\n");
}
