clc; clear;
N = 2^2;
x = rand(N, 1);

%% DFT1
% sprintf('DFT1')
% tic
% i =(1 : N)';
% j = 1 : N;
% W_N = exp(-1i*2*pi*(i - 1)*(j - 1)/N);
% X_w_dft1 = W_N*x;
% toc

%% DFT2
% sprintf('DFT2')
% tic
% X_w_dft2 = zeros(N, 1);
% for k = 1 : N
%     for n = 1 : N
%         X_w_dft2(k) = X_w_dft2(k) + x(n)*exp(-1i*2*pi*(k - 1)*(n - 1)/N);
%     end
% end
% toc

%% FFT1
sprintf('FFT1')
tic
X_w_fft1 = fft(x);
toc

%% FFT1
% base 2 fast fourier transform
sprintf('FFT2')
tic
    X_w_fft2 = FFT_zhf(x, false);    
toc

%% check
real(FFT_zhf(X_w_fft2, true))'
x'