gcc *.c *.h -o benchmarker -fopenmp -pthread -pg -O3
./benchmarker
gprof benchmarker gmon.out > profile.txt