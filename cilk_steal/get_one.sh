rm 0.txt 1.txt
taskset -c 0,1 ./fib_fast_steal
vim 0.txt
