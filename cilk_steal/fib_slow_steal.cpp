#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cilk/cilk.h>
#include <time.h>

clock_t st = clock();

  //********************************************
  //       Core
  //********************************************
long temp(){
  for(int i=0; i < 10000 i++){
    int b = i * i;
  }
  return 0;
}
  //********************************************

long fib(long n, std::string previous_CPU, long pre_n) {
  clock_t cur_t = clock();
  int current_CPU = sched_getcpu();
  char *file_name = (char*)malloc(10 * sizeof(char));
  sprintf(file_name, "%d.txt", current_CPU);
  FILE *output_file = fopen(file_name, "a+");
  fprintf(output_file, "Start: N=%ld, Current_CPU=%d, Previous_CPU=%s, Pre_N=%ld, Cur_Time=%lf\n", \
		  n, current_CPU, previous_CPU.c_str(), pre_n,(double)(cur_t-st)/CLOCKS_PER_SEC);

  if (n < 2){
    cur_t = clock();
    fprintf(output_file, "End: N=%ld, Current_CPU=%d, Previous_CPU=%s, Pre_N=%ld, Cur_Time=%lf\n", \
  		  n, current_CPU, previous_CPU.c_str(), pre_n,(double)(cur_t-st)/CLOCKS_PER_SEC);
    free(file_name);
  }
    
  fclose(output_file);

  if (n < 2)
    return n;
  std::string cur_CPU_str = previous_CPU + std::to_string(current_CPU);

  //********************************************
  //       Core
  //********************************************
  cilk_spawn temp();
  long x = fib(n-1, cur_CPU_str, n);
  long y = fib(n-2, cur_CPU_str, n);
  cilk_sync;
  //********************************************


  cur_t = clock();
  output_file = fopen(file_name, "a+");
  fprintf(output_file, "End: N=%ld, Current_CPU=%d, Previous_CPU=%s, Pre_N=%ld, Cur_Time=%lf\n", \
		  n, current_CPU, previous_CPU.c_str(), pre_n,(double)(cur_t-st)/CLOCKS_PER_SEC);
  fclose(output_file);
  free(file_name);

  return x + y;
}

int main(int argc, char *argv[]) {
  long n = 10;
  int current_CPU = sched_getcpu();
  if (argc > 1)
    n = atol(argv[1]);
  
  long result = fib(n, std::to_string(current_CPU), -1);
  printf("fib(%ld) = %ld\n", n, result);
  return 0;
}
