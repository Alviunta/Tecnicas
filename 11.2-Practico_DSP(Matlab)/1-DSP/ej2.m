clear;
clc;
fs=10000;
F=100;
SNR=15;

t=(0:1/fs:3*1/F); %En vez de un segundo ponemks un limite de 3 ciclos de la señal%
y=sin(2*pi*F*t);
subplot(2,2,1);
plot(t,y),xlabel("t"),ylabel("Amp"),title("Senoidal muestreada");
[signal_n ,ruido] = my_awgn(y, SNR);
subplot(2,2,2)
plot(t,signal_n),xlabel('Tiempo'),ylabel('Amplitud'),title('Señal con ruido(propio)');
subplot(2,2,3)
plot(t,ruido),xlabel('Tiempo'),ylabel('Amplitud'),title('Ruido(propio)');
SNR_test = 10 * log10(var(y)/var(signal_n-y))
%Ahora vamos a comparar con la funcion ya implementada en matlab awgn
signal2_n = awgn(y,SNR);
subplot(2,2,4);
plot(t,signal2_n),xlabel('Tiempo'),ylabel('Amplitud'),title('Señal con ruido (awgn)');

% function [signal_n ,ruido]= my_awgn(signal, snr)
% %SNR = 10 * log(var_signal/var_ruido)
% var_sig = var(signal);                  %calculamos la varoamza de la señal
% var_r = (var_sig)/(10^(snr/10));        %calculamos la varianza del ruido
% desv_r=sqrt(var_r);                     %calculamos la desviacion estandar del ruido
% ruido = desv_r*randn(size(signal));     %generamos un vector de ruido con la desviacion apropiada
%                                         %Usamos la función randn, teniendo en cuenta que debe poseer el mismo
%                                         %tamaño de y, usando una media de 0
% signal_n = ruido + signal;              %sumamos el ruido a la señal
% end




