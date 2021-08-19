V=5; % Rango de voltaje
b=12; % Cantidad de bits
q=(2*V)/(2^12); % La precisión o el valor de cada salto en voltios 
disp(q); 
SNR=20*log10(1/sqrt(2))+4.77+6.02*b;
disp(SNR); 

Vp=7; %Ahora el valor pico sera de 7 V

q1=(2*Vp)/(2^12); % La precisión o el valor de cada salto en voltios 
disp(q1); 
SNR1=20*log10(1/sqrt(2))+4.77+6.02*b;
disp(SNR1); 

%Aumentando la cantidad de bits a 16 bits

b1=16;
SNR2=20*log10(1/sqrt(2))+4.77+6.02*b1;
disp(SNR2); 