rm 0.txt 1.txt
taskset -c 0,1 ./fib_cilk_note_first
vim 0.txt
