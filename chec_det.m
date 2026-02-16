pkg load symbolic

% Define symbolic variable
syms x


% Define Mat4 (4x4 matrix)
Mat4 = [2+x+x^3,        -1+2*x+x^2,     3-2*x^2,         1+x+x^2+x^3;
        4-3*x+2*x^2,    1-x^3,          5*x+x^2,         2+2*x;
        -2+x+3*x^2,     6,              1-x+x^2-x^3,     4*x^2;
        3+x,            -4+2*x^2+x^3,   1+3*x-x^2,       5-2*x+2*x^3];

det4 = det(Mat4)

