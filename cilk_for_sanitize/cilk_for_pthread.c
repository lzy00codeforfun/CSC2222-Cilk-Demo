#include<cilk/cilk.h>
#include<stdio.h>
#include <stdlib.h>
#include <pthread.h> //pthread library

int main(int argc, char *argv[]){
  long long n = 10;
  if (argc > 1)
    n = atol(argv[1]);

  long long results = 0;
  pthread_mutex_t m; //define the lock
  pthread_mutex_init(&m,NULL); //initialize the lock
  
  cilk_for(long long i = 1; i <= n; i++){
    pthread_mutex_lock(&m); //lock - prevents other threads from running this code
    for(int j = 0; j < n; ++j){
      results += i;
    }
    pthread_mutex_unlock(&m); //unlock - allows other threads to access this code
  }
  printf("%lld*(1+...+%lld) = %lld\n", n, n, results);
}
