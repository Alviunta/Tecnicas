%Ejercicio 4

load Tchaikovsky.mat
signal1=signal(:,1);

%%%%% Aplicamos el filtro diseñado
a=1;  %Puesto que no hay realimentacion en el sistema, no tiene polos y por lo tanto su denominador es 1
hd=FIR; %El filtro diseñado nos devuelve la funcion de transferencia del filtro
b=hd.Numerator;  %Guardanos en b los coeficientes del numerador
signal_ma=filter(b,a,signal1);  

%%%%% Respuesta en frecuencia

freqz(b,a);

[frq,mag]=my_dft(signal,Fs);
[frq_ma,mag_ma]=my_dft(signal_ma,Fs);

figure

plot(frq,mag, '-b');
hold on;
plot(frq_ma,mag_ma, '--g');
hold off;
grid on;
legend('Senal Original','Senal filtrada');

%%%% Escuchamos la señal original y la filtrada

%sound(signal,Fs);

sound(signal_ma,Fs);








