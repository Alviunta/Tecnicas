function [signal_n, var_n] = my_awgn(signal,snr)

var_signal = var(signal);
C1=var_signal;
C2=snr/10;
C3=10^C2;
var_n = C1/C3;
desv_n=sqrt(var_n);
ruido = desv_n*randn(size(signal));
signal_n = ruido + signal;