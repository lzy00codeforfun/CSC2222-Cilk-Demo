#include <stdio.h>
#include <stdlib.h>

#include <cilk/cilk.h>

long fib(long n) {
  // ********************************
  //           Hightlight
  // ********************************
  if (n < 2){
    for(int i=0; i<10000; ++i){
      int b = i*i;
    }
    return n;
  }
  // ********************************
  long x = fib(n-1);
  long y = fib(n-2);
  return x + y;
}

int main(int argc, char *argv[]) {
  long n = 10;
  if (argc > 1)
    n = atol(argv[1]);

  long result = fib(n);
  printf("fib(%ld) = %ld\n", n, result);
  return 0;
}
