fs=10000;
F=100;
t=(0:1/fs:3*1/F); %En vez de un segundo ponemks un limite de 3 ciclos de la señal%
y=sin(2*pi*F*t);
subplot(2,2,1),plot(t,y),xlabel("t"),ylabel("Amp"),title("Senoidal muestreada");

%agregamos ruido definiendo previamente una SNR=15
SNR=15;
%calculamos la varianza de los valores almacenados en y
var_y = var(y);
var_r = (var_y)/(10^(SNR/10));
desv_r=sqrt(var_r); %calculamos la desviacion estandar del ruido

%Ahora generamos el ruido a partir de la desviación estandar obtenida
%Usamos la función randn, teniendo en cuenta que debe poseer el mismo
%tamaño de y, usando una media de 0
ruido = desv_r*randn(size(y));

%Ahora sumamos el ruido generado a la funcion senoidal
signal_n = ruido + y;
subplot(2,2,2)
plot(t,signal_n),xlabel('Tiempo'),ylabel('Amplitud'),title('Señal con ruido(propio)');
subplot(2,2,3)
plot(t,ruido),xlabel('Tiempo'),ylabel('Amplitud'),title('Ruido(propio)');
SNR_test = 10 * log10(var(y)/var(signal_n-y))
%Ahora vamos a comparar con la funcion ya implementada en matlab awgn
signal2_n = awgn(y,SNR);
subplot(2,2,4);
plot(t,signal2_n),xlabel('Tiempo'),ylabel('Amplitud'),title('Señal con ruido (awgn)');


