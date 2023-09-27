#include <cstdio>
#include <cstdlib>

using std::FILE;
using std::atof;
using std::atoi;
using std::fclose;
using std::fopen;
using std::fprintf;
using std::fscanf;
using std::printf;
using std::size_t;

int factorial(int n);
int double_factorial(int n);

int main(int argc, char **argv) {
  if (argc > 1) {
    switch (argv[1][0]) {
    case '+':
      if (argc != 4)
        fprintf(stderr, "[!] + takes two operands\n");
      else
        printf("%.3f\n", atof(argv[2]) + atof(argv[3]));
      break;
    case '-':
      if (argc != 4)
        fprintf(stderr, "[!] - takes two operands\n");
      else
        printf("%.3f\n", atof(argv[2]) - atof(argv[3]));
      break;
    case '*':
      if (argc != 4)
        fprintf(stderr, "[!] * takes two operands\n");
      else
        printf("%.3f\n", atof(argv[2]) * atof(argv[3]));
      break;
    case '/':
      if (argc != 4)
        fprintf(stderr, "[!] / takes two operands\n");
      else if (atoi(argv[3]) == 0)
        fprintf(stderr, "[!] Division by zero is illegal\n");
      else
        printf("%.3f\n", atof(argv[2]) / atof(argv[3]));
      break;
    case '!':
      switch (argv[1][1]) {
      case '\0':
        if (argc != 3)
          fprintf(stderr, "[!] ! takes one operand\n");
        else if (atoi(argv[2]) < 0)
          fprintf(stderr, "[!] Gamma function is undefined for negative integers\n");
        else
          printf("%d\n", factorial(atoi(argv[2])));
        break;
      case '!':
        if (argc != 3)
          fprintf(stderr, "[!] !! takes one operand\n");
        else if (atoi(argv[2]) < 0)
          fprintf(stderr, "[!] Gamma function is undefined for negative integers\n");
        else
          printf("%d\n", double_factorial(atoi(argv[2])));
        break;
      default:
        fprintf(stderr, "[!] Unrecognised operator \"%s\"\n", argv[1]);
        break;
      }
      break;
    default:
      fprintf(stderr, "[!] Unrecognised operator \"%s\"\n", argv[1]);
      break;
    }
  } else {
    FILE *fin = fopen("input.txt", "r"),
         *fout = fopen("output.txt", "w");
    char op[3];
    float f1, f2;
    int n;
    while (fscanf(fin, "%s", op) != EOF) {
      switch (op[0]) {
      case '+':
        fscanf(fin, "%f %f", &f1, &f2);
        fprintf(fout, "%.3f\n", f1 + f2);
        break;
      case '-':
        fscanf(fin, "%f %f", &f1, &f2);
        fprintf(fout, "%.3f\n", f1 - f2);
        break;
      case '*':
        fscanf(fin, "%f %f", &f1, &f2);
        fprintf(fout, "%.3f\n", f1 * f2);
        break;
      case '/':
        fscanf(fin, "%f %f", &f1, &f2);
        if (f2 == 0) {
          fprintf(fout, "계산할 수 없습니다.\n");
          fprintf(stderr, "[!] Division by zero is illegal\n");
        } else
          fprintf(fout, "%.3f\n", f1 / f2);
        break;
      case '!':
        switch (op[1]) {
        case '\0':
          fscanf(fin, "%d", &n);
          if (n < 0)
            fprintf(stderr, "[!] Gamma function is undefined for negative integers\n");
          else
            fprintf(fout, "%d\n", factorial(n));
          break;
        case '!':
          fscanf(fin, "%d", &n);
          if (n < 0)
            fprintf(stderr, "[!] Gamma function is undefined for negative integers\n");
          else
            fprintf(fout, "%d\n", double_factorial(n));
          break;
        default:
          fprintf(stderr, "[!] Unrecognised operator \"%s\"\n", op);
          break;
        }
        break;
      default:
        fprintf(stderr, "[!] Unrecognised operator \"%s\"\n", op);
        break;
      }
    }
    fclose(fin);
    fclose(fout);
  }
  return 0;
}

int factorial(int n) {
  return n? double_factorial(n) * double_factorial(n - 1) : 1;
}

int double_factorial(int n) {
  constexpr size_t MEM_EVEN_MAX = 10,
                   MEM_ODD_MAX = 10;
  static int mem_even[MEM_EVEN_MAX] = {1},
             mem_odd[MEM_ODD_MAX] = {1};
  static size_t mem_even_len = 1,
                mem_odd_len = 1;
  if (n % 2) {
    const size_t mem_idx = (n - 1) / 2;
    for (; mem_idx >= mem_odd_len; mem_odd_len++)
      mem_odd[mem_odd_len] = mem_odd[mem_odd_len - 1] * (mem_odd_len * 2 + 1);
    return mem_odd[mem_idx];
  } else {
    const size_t mem_idx = n / 2;
    for (; mem_idx >= mem_even_len; mem_even_len++)
      mem_even[mem_even_len] = mem_even[mem_even_len - 1] * (mem_even_len * 2);
    return mem_even[mem_idx];
  }
}
