function [Cum_conv] = func_conv(u, v)
    m = length(u);
    n = length(v);

    for k = 1:n
        F = 0;
        for j = max(1, k + 1 - n):min(k, m)
            F = F + u(j) * v(k + 1 - j);
        end
        Cum_conv(k) = F / min(k, m);
    end
end

function [C4x_uv] = func_cum4uni_vertical(x)
    x = x - mean(x);
    N = length(x);

    for m = 1:N
        F = 0;
        F1 = 0;

        for k = 1:(N + 1 - m)
            F = F + x(k) * x(k) * x(k) * x(k - 1 + m);
            F1 = F1 + x(k) * x(k - 1 + m);
        end

        C4xx(m) = F / (N + 1 - m);
        Rxx(m) = F1 / (N + 1 - m);
    end
    C4x_uv = C4xx - 3 * Rxx * Rxx(1);
end

% Main script
clear all;
close all;
xt = 0;
px = 0;
pn = 0;
pxot = 0;
pxit = 0;
Fs = 1000;  % Sample frequency
fc = 50;    % Carrier frequency
T = 1/Fs;   % Sample period
KB = 1024;
L = 1 * 1024;
t = (0:L-1) * T;
A = 1;
nfft = 2^nextpow2(L);
wc = 2 * pi * fc;

xt = cos(2 * pi * fc * t + pi / 4);

figure(1);
plot(t, xt, 'k');
title('Useful Signal')
xlabel('Time(s)')
ylabel('Amplitude(u)')
grid on;

xt_fft = fft(xt, nfft) / L;
f = Fs * linspace(0, 1, nfft);

figure(2)
plot(f, abs(xt_fft), 'k')
xlabel('Frequency(Hz)')
ylabel('Amplitude(u)')
title('Useful Signal Spectrum')
grid on;

stream = RandStream("mrg32k3a");
noise = 2.2 * randn(stream, 1, length(xt))';
xt_noise = xt + noise;
figure(3);
plot(t, xt_noise, 'k');
title('Noisy Signal')
xlabel('Time(s)')
ylabel('Amplitude(u)')
grid on;

xt_noise_fft = fft(xt_noise, nfft) / L;

figure(4)
plot(f, abs(xt_noise_fft), 'k')
xlabel('Frequency(Hz)')
ylabel('Amplitude(u)')
title('Noisy Signal Spectrum')
grid on;

tic
C4x_uv=func_cum4uni_vertical(xt_noise);
Cum_conv = func_conv(C4x_uv, xt_noise);
Cum_conv = (-1) * Cum_conv;

conv_fft = fft(Cum_conv, nfft) / L;

ajuste = ((16/3) * abs(conv_fft)).^(1/5);  % amplitude adjustment

ajuste_mean = mean(ajuste);

for qq = 1:1  % correction by mean
    for q = 1:length(ajuste)
        ajuste(q) = ajuste(q) - ajuste_mean;
        if ajuste(q) < 0
            ajuste(q) = 1;
        end
    end
end
nuevo_num = ajuste .* exp(i * angle(conv_fft));  % combining the new number

ajuste_ifft = ifft(nuevo_num, nfft) * L;  % antitransformation

atn = real(ajuste_ifft);

mod_atn = 2 * atn .* atn;  % envelope detection
b = firpm(20, [0 0.03 0.1 1], [1 1 0 0]);
sal = filter(b, 1, mod_atn);
sal = sqrt(sal);
atn_final = atn ./ sal;

t_cum = toc;

figure(5);
hold on
plot(t, atn_final, 'r');
title('Comparison in time Useful Signal- Proposed algorithm')
xlabel('Time(s)')
ylabel('Amplitude(u)')
grid on;

atn_final_fft = fft(atn_final, nfft) / L;

figure(6)
plot(f, abs(xt_fft), 'b')
hold on
plot(f, abs(atn_final_fft), 'r')
xlabel('Frequency(Hz)')
ylabel('Amplitude(u)')
title('Comparison of the spectrum of the Useful Signal-Proposed algorithm')
grid on;
legend('Useful', 'Output')

figure(7)
plot(f, abs(xt_noise_fft), 'b')
hold on
plot(f, abs(atn_final_fft), 'r')
xlabel('Frequency(Hz)')
ylabel('Amplitude(u)')
title('Comparison of the spectrum of the Noisy Signal-Proposed algorithm')
grid on;
legend('Noisy', 'Output')

for i = 1:length(xt)
    px = px + ((abs(xt(i)))^2 / length(xt));
end
for i = 1:length(noise)
    pn = pn + ((abs(noise(i)))^2 / length(noise));
end

SNR = 10 * log(px / pn);

for i = 1:length(atn_final)
    pxot = pxot + ((abs(atn_final(i)))^2 / length(atn_final));
end
pno = pxot - px;
SNRO = 10 * log(px / pno);
length(xt)
length(xt_noise)

CORRE_INICIAL = corrcoef(xt, xt_noise)
CORRE_FINAL = corrcoef(xt, atn_final)
