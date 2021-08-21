% Ejercicio 2 del trabajo practico Filtros IIR

clear
clc
close all

%% a) Cargar senial 

load Tchaikovsky.mat
signal=signal(:,1);
fs=44100;
%% b) Agregue ruido gaussiano a la senial

snr = 60;

[signal_n, var_n] = my_awgn (signal, snr);


% Verificar el valor de SNR
% SNR = 10 * log10 ( SIGNAL POWER / NOISE POWER )

SNR_test = 10 * log10(var(signal)/var(signal_n-signal))

%Diseñamos nuestro filtro
%Filtro IIR:
%y[n]=?*y[n-1]+(1-?)*x[n]

lambda=0.98;
b=1-lambda;
a=[1,-lambda];
signal_f=filter(b,a,signal_n);


%La frecuencia de corte:
fco=(-log(lambda)*fs)/pi;
fprintf("La frecuencia de corte es: fco = %f\n",fco);

%Respuesta en frecuencia y en el tiempo:
freqz(b,a);
figure
zplane(b,a);

[frq,mag]=my_dft(signal,fs);
[frq_n,mag_n]=my_dft(signal_n,fs);
[frq_f,mag_f]=my_dft(signal_f,fs);

figure 
subplot(3,2,1), plot((signal),'r'),grid on, title 'Señal original';
subplot(3,2,2), plot((signal_n),'-b'),grid on, title 'Señal con ruido';
subplot(3,2,3), plot((signal_f),'-g'),grid on, title 'Señal filtrada';
subplot(3,2,4), plot(frq,mag,'r'),grid on, title 'Señal original';
subplot(3,2,5), plot(frq_n,mag_n,'g'),grid on, title 'Señal con ruido';
subplot(3,2,6), plot(frq_f,mag_f,'b'),grid on, title 'Señal filtrada';
