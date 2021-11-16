#include<cilk/cilk.h>
#include<stdio.h>
#include <stdlib.h>
#include <cilk/reducer_opadd.h>

int main(int argc, char *argv[]){
  long long n = 10;
  if (argc > 1)
    n = atol(argv[1]);

  cilk::reducer_opadd<long long> results ;
  
  cilk_for(long long i = 1; i <= n; i++){
    for(int j = 0; j < n; ++j){
      results += i;
    }
  }
  printf("%lld*(1+...+%lld) = %lld\n", n, n, results.get_value());
}
