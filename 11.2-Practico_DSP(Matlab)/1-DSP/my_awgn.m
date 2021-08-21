function [signal_n ,ruido]= my_awgn(signal, snr)
%SNR = 10 * log(var_signal/var_ruido)
var_sig = var(signal);                  %calculamos la varoamza de la señal
var_r = (var_sig)/(10^(snr/10));        %calculamos la varianza del ruido
desv_r=sqrt(var_r);                     %calculamos la desviacion estandar del ruido
ruido = desv_r*randn(size(signal));     %generamos un vector de ruido con la desviacion apropiada
                                        %Usamos la función randn, teniendo en cuenta que debe poseer el mismo
                                        %tamaño de y, usando una media de 0
signal_n = ruido + signal;              %sumamos el ruido a la señal
end

