%% initial
% clear; clc
% fs = 44100; %the song is 44100 kps ,namely 44100 points per second
% save('fs.mat', 'fs');
% load('Song_LeftChannel', 'Song_LeftChannel');
% load('Song_RightChannel', 'Song_RightChannel');
% start = 46000;
% last = 16384;
% n = 1 : last;
% t = n/fs;
% slice = Song_LeftChannel(start : start + last - 1);
% subplot(2, 1, 1);
% plot(t, slice);
% save('slice.mat', 'slice');
% save('start.mat', 'start');
% save('last.mat', 'last');
%% use
% clear; clc
% load('Song_LeftChannel', 'Song_LeftChannel');
% load slice
% load fs
% load start
% load last
% 
% n = 1 : last;
% t = n/fs*1000;
% slice = Song_LeftChannel(start : start + last - 1);
% subplot(2, 1, 1);
% plot(t, slice);
% axis([0, last/fs*1000, -1, 1]);
% 
% f_n_max = last/2;
% F = fft(slice);
% Spetrum = F(1 : f_n_max);
% f_n = (1 : f_n_max) - 1;
% f_x = f_n/f_n_max*fs/2;
% subplot(2, 1, 2);
% semilogx(f_x, 20*log(abs(Spetrum)));
% axis([20, fs/2, -120, 160]);
% 
% figure;
% %first-order lowpass filter
% f_l = 2500;
% w_l = f_l*2*pi;
% w_x = f_x*2*pi;
% 
% H_jw = 1./(1 + 1i*w_x/w_l);
% H_jw = H_jw.*H_jw;
% semilogx(w_x, abs(H_jw));
% H_jf = ones(size(F));
% H_jf(1:f_n_max) = H_jw';
% for i = last/2 + 1 : last
%     H_jf(i) = H_jw(last - i + 1);
% end%for
% Y_jf = F.* H_jf;
% % semilogx(abs(Y_jf));
% y_t = real(ifft(Y_jf));
% subplot(2, 1, 1);
% plot(t, y_t);
% axis([0, last/fs*1000, -1, 1]);
% 
% F_new = fft(y_t);
% Spetrum_new = F_new(1 : f_n_max);
% f_n_new = (1 : f_n_max) - 1;
% f_x_new = f_n_new/f_n_max*fs/2;
% subplot(2, 1, 2);
% semilogx(f_x_new, 20*log(abs(Spetrum_new)));
% axis([20, fs/2, -120, 160]);
%%
clear; clc
load fs
load('Song_LeftChannel', 'Song_LeftChannel');
N = 8192;
last = 8000;
M = N - last; %length of FIR signal of ystem
step = 70;

h_t = zeros(N, 1);
f_cutoff = 500;
a = f_cutoff/fs*2*pi;
t_h = (0 : M - 1);
h_t(1 : M) = exp(-t_h*a)*a;
H_jw = fft(h_t);

for start = 1 : step : size(Song_LeftChannel) - last
    n = 1 : N;
    t = n/fs*1000;
    slice = zeros(N, 1);
    slice(1 : last) = Song_LeftChannel(start : start + last - 1);
    subplot(2, 2, 1);
    plot(t(1 : last), slice(1 : last));
    axis([0, last/fs*1000, -1, 1]);
    f_n_max = N/2;
    F = fft(slice);
    Spetrum = F(1 : f_n_max);
    f_n = (1 : f_n_max) - 1;
    f_x = f_n/f_n_max*fs/2;
    subplot(2, 2, 3);
    semilogx(f_x, 20*log(abs(Spetrum)));
    axis([20, fs/2, -120, 160]);
        
    Y_jw = F.* H_jw;
    
    y_t = real(ifft(Y_jw));
    subplot(2, 2, 2);
    plot(t(1 : last), y_t(1 : last));
    axis([0, last/fs*1000, -1, 1]);

    Spetrum_new = Y_jw(1 : f_n_max);
    subplot(2, 2, 4);
    semilogx(f_x, 20*log(abs(Spetrum_new)));
    axis([20, fs/2, -120, 160]);
    
    
    ch = get(gcf,'CurrentCharacter');
    if strcmpi(ch,'e')
        return;
    end
    sprintf('now %.1fs, done %.1f %%',start/fs, start/112975.85)
    pause(0.001);
end


