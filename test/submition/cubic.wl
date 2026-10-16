ClearAll[t1, t2, t3, f1, f2, f3];
f1 = (-1.0558)*t1^0*t2^0 + (-1.5873)*t1^0*t2^1 + (-0.4158)*t1^0*t2^2 + (-1.3801)*t1^0*t2^3 + (-1.7339)*t1^1*t2^0 + (-0.3936)*t1^1*t2^1 + (1.6718)*t1^1*t2^2 + (1.2018)*t1^2*t2^0 + (1.0607)*t1^2*t2^1 + (-1.1123)*t1^3*t2^0;
f2 = (0.1467)*t3^0*t1^0*t2^0 + (-0.8933)*t3^0*t1^1*t2^0 + (-1.3093)*t3^0*t1^2*t2^0 + (-1.5753)*t3^0*t1^3*t2^0 + (-1.1424)*t3^1*t1^0*t2^0 + (1.7099)*t3^1*t1^1*t2^0 + (1.3157)*t3^1*t1^2*t2^0 + (1.2266)*t3^2*t1^0*t2^0 + (1.2018)*t3^2*t1^1*t2^0 + (-1.2263)*t3^3*t1^0*t2^0;
f3 = (-0.7606)*t3^0*t1^0*t2^0 + (0.5079)*t3^0*t1^0*t2^1 + (0.9276)*t3^0*t1^0*t2^2 + (1.4186)*t3^0*t1^0*t2^3 + (1.5202)*t3^1*t1^0*t2^0 + (-1.6531)*t3^1*t1^0*t2^1 + (0.4234)*t3^1*t1^0*t2^2 + (0.6868)*t3^2*t1^0*t2^0 + (0.0238)*t3^2*t1^0*t2^1 + (-1.2888)*t3^3*t1^0*t2^0;
(* exact rational coefficients: the reference is not limited by machine precision *)
f1 = Rationalize[f1, 0]; f2 = Rationalize[f2, 0]; f3 = Rationalize[f3, 0];
h4 = Resultant[f2, f3, t3];
h5 = Resultant[f1, h4, t2];
Print["h5 degree in t1: ", Exponent[h5, t1]];
Print["h5 real roots: ", Sort[N[t1 /. NSolve[h5 == 0, t1, Reals, WorkingPrecision -> 50], 10]]];
sol = NSolve[{f1 == 0, f2 == 0, f3 == 0}, {t1, t2, t3}, Reals, WorkingPrecision -> 50];
Print["real solutions (t1, t2, t3):"];
Do[Print[s], {s, SortBy[N[{t1, t2, t3} /. sol, 8], First]}];
