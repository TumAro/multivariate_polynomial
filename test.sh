rm -f a.out
time g++ -fsanitize=address -fsanitize=undefined -O0 -g src/utils.cpp src/Multivariate.cpp src/Univariate.cpp src/LinAlgb.cpp src/Numerical.cpp src/Methods.cpp test/test_case.cpp
./a.out