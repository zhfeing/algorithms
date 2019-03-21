function X_k = FFT_zhf(x_t, is_invert)
    if is_invert
        X_k = FFT_stract_time(x_t, -1)/length(x_t);
    else
        X_k = FFT_stract_time(x_t, 1);
    end
end

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

function X_k = FFT_stract_time(x_t, rotation_factor)
    N = length(x_t);
    v = log2(N);
    X_k = bit_inverse(x_t);
%     generate rotate value
    W_N = zeros(N/2 - 1, 1);
    for i = 0 : N/2 - 1
        W_N(i + 1) = exp(-1i*2*pi*i/N*rotation_factor);
    end        
%     cauculate fft bottom up
    subBFn = N;
    for i = 0 : v - 1
        subBFn = subBFn/2;
        size = N/subBFn/2;
        for p = 0 : subBFn - 1
            for q = 0 : size - 1
%                 cauculate a sub butterfly
                k1 = 2*p*size + q;
                k2 = k1 + size;
%                 back up the value
                a = X_k(k1 + 1);
                b = X_k(k2 + 1)*W_N(q*subBFn + 1);
%                 cauculate the value
                X_k(k1 + 1) = a + b;
                X_k(k2 + 1) = a - b;
            end
        end
    end
end