%a) Cargue el archivo de audio provisto llamado Tchaikovsky.mat. 
%En el mismo encontrará dos variables, la matriz signal con dos canales (stereo) y la variable Fs. 
%Elija 1 de los 2 canales disponibles.

load Tchaikovsky.mat
subplot(2,2,1), plot(signal(:,1),'r'),grid on, title 'Señal original';

%Signal es una matriz de dos columnas por 623937 filas que contiene la
%informacion de los dos canales del audio. Con plot(signal(:,1)) le estamos
%indicando que grafique todos los elementos de la columna 1.

%b) Agregue ruido gaussiano a esta señal tal que 
%la relación señal-ruido entre la señal y la señal con ruido sea de 50 dB.
signal1=signal(:,1);   %Puesto que solo debemos usar una columna de signal
snr=10;
[signal_n, var_n] = my_awgn (signal1, snr);
SNR_test = 10 * log10(var(signal1)/var(signal_n-signal1))
subplot(2,2,2), plot((signal_n),'b'),grid on, title 'Señal con ruido';

%c) Calcule el valor máximo de N (N_max), con las frecuencias fs = Fs y fco = 22.050 Hz.
fco=22050;
dt = 1/Fs
N_max = (sqrt((((0.885894)^2)*((Fs)^2))/((fco)^2)-1));
fprintf("Orden maximo del filtro = %f\n",N_max);
M=round(N_max);
fprintf("Orden del filtro = %d\n",M);
N_window_time = N_max * dt;

%d) Aplique filtrado del tipo moving average a la señal 
%con ruido para un filtro MA con dimensión igual N = N_max. 
%Utilice la funcion filter().

a = 1;
b = ones(1, M) / M ; % Coeficientes de FIR MA

signal_ma = filter(b, a, signal_n);
subplot(2,2,3), plot((signal_ma),'m'),grid on, title 'Señal filtrada';

%e) Utilice la función sound(signal_n, Fs) para reproducir las señales sin ruido, con ruido y filtrada.

fprintf("Audio original\n");
sound(signal,Fs);
fprintf("Audio con ruido\n");
sound(signal_n,Fs);
fprintf("Audio filtrado\n");
sound(signal_ma,Fs);

%f) Grafique la respuesta en frecuencia de las senales original y filtrada y compare.
%Utilice la funcion provista my_dft.
figure
[frq, mag] = my_dft(signal, Fs);
subplot(2,2,1), plot(frq,mag,'r'),grid on, title 'Señal original';
[frq_n, mag_n] = my_dft(signal_n, Fs);
subplot(2,2,2), plot(frq_n,mag_n,'g'),grid on, title 'Señal con ruido';
[frq_ma, mag_ma] = my_dft(signal_ma, Fs);
subplot(2,2,3), plot(frq_ma,mag_ma,'b'),grid on, title 'Señal filtrada';







