% Ejercicio 1 del trabajo practico Filtros IIR

clear
clc
close all

%% a) Genere una señal senoidal 

fs = 44100;
fn = 100;

dt = 1/fs;
P = 1/fn;
t = 0:dt:P*4; 
t = t';

signal = sin(2 * pi * fn * t) ;

%% b) Agregue ruido gaussiano a la señal senoidal

snr = 15;

[signal_n, var_n] = my_awgn (signal, snr);


% Verificar el valor de SNR
% SNR = 10 * log10 ( SIGNAL POWER / NOISE POWER )

SNR_test = 10 * log10(var(signal)/var(signal_n-signal))

%Dise�amos nuestro filtro
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
figure
plot(t, signal, '--b')
hold on
plot(t, signal_n, '-r')
plot(t, signal_f, '-g')
hold off

grid on

legend('Señal original', 'Con ruido', 'Filtrada')

[frq,mag]=my_dft(signal,fs);
[frq_n,mag_n]=my_dft(signal_n,fs);
[frq_f,mag_f]=my_dft(signal_f,fs);

figure
plot(frq,mag, '--b')
hold on
plot(frq_n,mag_n, '-r')
plot(frq_f,mag_f, '-g')
hold off 
grid on
legend('Señal original', 'Con ruido', 'Filtrada')


