% fir_matlab_to_C: script to compare FIR filters implemented in C and MATLAB
% languages.
%
% Version: 003
% Date:    2020/09/03
% Author:  Rodrigo Gonzalez <rodralez@frm.utn.edu.ar>
% URL:     https://github.com/rodralez/control

clc
close all
clear
%Ejercicio 5
%Primero compilamos los archivos en c

mex fir_matlab_wrapper.c  fir_filter.c;
%% Parametros

fn1 = 300;   % Signal 1 frequency
fn2 = 600;   % Signal 2 frequency
fn3 = 50 ;   % Signal 3 frequency, interference
fs = 10000;  % Sampling frequency

%% a) Genere una señal senoidal 

dt = 1/fs;
t = (0:dt:dt*1000)';

signal = sin(2 * pi * fn1 * t) + sin(2 * pi * fn2 * t);
signal_n = signal + 0.75 * sin(2 * pi * fn3 * t);

%% b) Transformar la señal a punto flotante precision simple

signal_f = single(signal_n);

%% c) Filtrado en C
%PARA GENERAR LOS COEFICIENTES EN C:
% 1) Armar el filtro completo con el orden y las frecuencias de corte.
% 2) Ir a Targets > Generate C headers
% 3) Seleccionar exportar como Unsigned 16-bit integrer
% 4) Elegir el nombre coeficientes.h

signal_fir_c = fir_matlab_wrapper( signal_f )*(2^(-30));

%% d) Filtrado en MATLAB

Hd = FIR_K_100_800;
b = Hd.Numerator;
a = 1;

signal_fir_m = filter(b, a, signal_n);

%% Respuesta en el dominio del tiempo

figure
subplot(3,1,1)
plot(t, signal_n, '-r')
hold on
plot(t, signal, '-b')
grid on
legend('Con ruido','Original')

subplot(3,1,2)
plot(t, signal_n, '-g')
hold on
plot(t, signal_fir_c, '--b')
hold on


grid on
legend('Con ruido', 'Filtrada en C')

subplot(3,1,3)
plot(t, signal_n, '-g')

hold on
plot(t, signal_fir_m, '--m')
hold off

grid on
legend('Con ruido', 'Filtrada en MATLAB' )

%% Respuesta en el dominio de la frecuencia

[f1, mag_n] = my_dft(signal_n, fs);
[f2, mag_fir] = my_dft(signal_fir_c, fs);
[f3, mag_firm] = my_dft(signal_fir_m, fs);

figure
plot(f1, mag_n, '.-r')
hold on
plot(f2, mag_fir, '-b')
hold on
plot(f3, mag_firm, '-g')
hold off

grid on
legend('Con ruido', 'Filtrada en C','Filtrada en MATLAB')
