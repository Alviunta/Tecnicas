fs=10000;
F=100;
t=(0:1/fs:3*1/F); %En vez de un segundo ponemos un limite de 3 ciclos de la señal%
%El vector t empieza en 0, hace saltos de 1/fs y termina en 3 periodos de
%la señal muestreada
y=sin(2*pi*F*t);
subplot(1,1,1),plot(t,y),xlabel("t"),ylabel("Amp"),title("Senoidal muestreada");
%subplot(m,n,p) genera una ventana de m por n y ubica la figura en la
%posicion p