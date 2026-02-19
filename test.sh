rm -f a.out
g++ -fsanitize=address -fsanitize=undefined -O0 -g src/utils.cpp src/Multivariate.cpp src/Univariate.cpp src/LinAlgb.cpp src/Numerical.cpp src/DCEI.cpp test.cpp
./a.out