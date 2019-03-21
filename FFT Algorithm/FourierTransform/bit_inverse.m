function y = bit_inverse(x)
    N = length(x);    
    v = log2(N);
    y = zeros(N, 1);
    for i = 0 : N - 1
        A = i;
        n_stract = 0;
        for j = 0 : v - 1
            a_j = mod(A, 2);
            A = fix(A/2);
            n_stract = n_stract + a_j*2^(v - 1 - j);
        end
         y(n_stract + 1) = x(i + 1);
    end
end
