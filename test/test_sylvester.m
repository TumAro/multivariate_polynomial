% test_sylvester.m
% Builds Sylvester matrix of two bivariate polynomials and computes det at test y-values.
%
% Storage: C(a+1, b+1) = coefficient of x^a * y^b, where a+b <= 6

clear; clc;

max_deg = 6;

M = zeros(max_deg+1, max_deg+1);
N = zeros(max_deg+1, max_deg+1);

% M(a+1, b+1) = coeff of x^a * y^b
M(1,1)= 1.39; M(2,1)=-4.75; M(3,1)=-2.25; M(4,1)=-2.77; M(5,1)= 2.36; M(6,1)= 1.77; M(7,1)= 3.92;
M(1,2)=-4.13; M(2,2)=-0.78; M(3,2)=-4.70; M(4,2)=-2.81; M(5,2)= 0.05; M(6,2)=-4.73;
M(1,3)=-3.01; M(2,3)= 1.50; M(3,3)= 0.45; M(4,3)=-2.80; M(5,3)= 0.89;
M(1,4)= 3.09; M(2,4)=-4.94; M(3,4)= 3.06; M(4,4)= 1.98;
M(1,5)=-1.60; M(2,5)=-3.45; M(3,5)= 4.57;
M(1,6)=-1.63; M(2,6)=-4.07;
M(1,7)=-4.03;

N(1,1)= 3.47; N(2,1)= 1.04; N(3,1)= 3.07; N(4,1)= 2.30; N(5,1)= 0.36; N(6,1)= 4.73; N(7,1)=-1.21;
N(1,2)= 0.52; N(2,2)= 3.29; N(3,2)= 1.19; N(4,2)= 3.62; N(5,2)= 0.77; N(6,2)= 2.05;
N(1,3)=-4.54; N(2,3)=-2.72; N(3,3)=-2.11; N(4,3)=-4.20; N(5,3)=-2.67;
N(1,4)=-3.99; N(2,4)=-2.22; N(3,4)= 1.36; N(4,4)=-1.35;
N(1,5)=-1.30; N(2,5)=-2.90; N(3,5)=-2.33;
N(1,6)= 4.37; N(2,6)= 1.48;
N(1,7)= 1.09;

% ===================== RUN TESTS =====================

fprintf('=== Sylvester Matrix Determinant Test ===\n\n');
fprintf('Both polynomials: degree 6 in x, total degree <= 6\n');
fprintf('Sylvester matrix size: 12 x 12\n\n');

test_y = [-2.0, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 3.0];

fprintf('%12s  %25s\n', 'y_value', 'det(Sylvester)');
fprintf('%s\n', repmat('-', 1, 40));

for i = 1:length(test_y)
    yv = test_y(i);
    S = build_sylvester(M, N, yv, max_deg);
    d = det(S);
    fprintf('%12.4f  %25.10e\n', yv, d);
end

% Print Sylvester matrix at y=0
fprintf('\n=== Sylvester matrix at y = 0 ===\n');
S0 = build_sylvester(M, N, 0.0, max_deg);
for r = 1:rows(S0)
    fprintf('  ');
    for c = 1:columns(S0)
        fprintf('%8.4f ', S0(r,c));
    end
    fprintf('\n');
end
fprintf('det(S at y=0) = %.10e\n', det(S0));

% Polynomial evaluation sanity check
fprintf('\n=== Polynomial evaluation sanity check ===\n');
fprintf('%8s %8s %16s %16s\n', 'x', 'y', 'M(x,y)', 'N(x,y)');
fprintf('%s\n', repmat('-', 1, 52));

test_pts = [0 0; 1 0; 0 1; 1 1; -1 1; 2 -1; 0.5 0.5];
for i = 1:rows(test_pts)
    xv = test_pts(i,1);
    yv = test_pts(i,2);
    mv = eval_poly(M, xv, yv, max_deg);
    nv = eval_poly(N, xv, yv, max_deg);
    fprintf('%8.2f %8.2f %16.6f %16.6f\n', xv, yv, mv, nv);
end

fprintf('\n=== Use these values to verify your implementation ===\n');

% ===================== FUNCTIONS =====================

function val = coeff_x(C, k, yv, max_deg)
    val = 0;
    for b = 0:max_deg
        if (k + b) <= max_deg
            val = val + C(k+1, b+1) * yv^b;
        end
    end
end

function S = build_sylvester(M, N, yv, max_deg)
    deg = max_deg;
    sz = 2 * deg;
    S = zeros(sz, sz);

    pm = zeros(1, deg+1);
    pn = zeros(1, deg+1);
    for k = 0:deg
        pm(deg+1-k) = coeff_x(M, k, yv, max_deg);
        pn(deg+1-k) = coeff_x(N, k, yv, max_deg);
    end

    for i = 1:deg
        S(i, i:(i+deg)) = pm;
    end
    for i = 1:deg
        S(deg+i, i:(i+deg)) = pn;
    end
end

function val = eval_poly(C, xv, yv, max_deg)
    val = 0;
    for a = 0:max_deg
        for b = 0:(max_deg - a)
            val = val + C(a+1, b+1) * xv^a * yv^b;
        end
    end
end
