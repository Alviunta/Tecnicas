function Ej4
%-------------------Parte a) --------------------------
%{
Datos de Diseño: pasa-banda entre 300 y 3.400 Hz con 3 dB en la banda pasante.
%}
fc1 = 300;
fc2 = 3400;
fs = fc2 * 4;
T = 1/ fs;

%Calculo las fecuencias de corte digitales

wd1 = fc1 * 2 * pi / fs;
wd2 = fc2 * 2 * pi / fs;

%Obtengo las frecuencias analógicas precombadas

wa1 = 2/T * tan(wd1/2);
wa2 = 2/T * tan(wd2/2);

%Diseño el filtro pasabajos analógico mediante una función de Matlab
%{
 Para calcular el filtro de chev uso la función cheblap. Sus parámetros
 de entrada son: 
    1ro: el orden del filtro
    2do: los db del ripple en la banda pasante
The function returns the poles in the length n column vector p and the gain
 in scalar k. z is an empty matrix, because there are no zeros
%}

ordenDelFiltro = 10;
ripple = 3;
[z,p,k] = cheb1ap(ordenDelFiltro,ripple);       
[bs_lp, as_lp] = zp2tf(z,p,k); %sufijo lp de lowpass

%Diseño del pasabanda analógico a partir del prototipo de pasabajos
%calculado previamente

%{
[bt,at] = lp2bp(b,a,Wo,Bw) transforms an analog lowpass filter prototype given 
by polynomial coefficients into a bandpass filter with center 
frequency Wo and bandwidth Bw. Row vectors b and a specify the coefficients 
of the numerator and denominator of the prototype in descending powers of s.
%}

Wo = sqrt(wa1*wa2);
Bw = wa2 - wa1;

[bs_bp,as_bp] = lp2bp(bs_lp,as_lp,Wo,Bw); %sufijo bp de bandpass

%---------------------------- Parte b) -------------------------
%Grafique la respuesta en frecuencia y fase del filtro analógico. 
%Use la función freqs().

%{
h = freqs(b,a,w) returns the complex frequency response of the 
analog filter specified by the coefficient vectors b and a, evaluated at the 
angular frequencies w
[h,wout] = freqs(b,a,n) uses n frequency points to compute h and returns 
the corresponding angular frequencies in wout.

Para usar la primera forma, requerimos "w" que es un vector con las
frecuencias angulares de la señal. Este vector lo tenemos que crear.
Para crearlo usamos linspace.

y = linspace(x1,x2,n) generates n points. 
The spacing between the points is (x2-x1)/(n-1).Linspace is similar to the
colon operator, “:”, but gives direct control over the number of points and 
always includes the endpoints. “lin” in the name “linspace” refers to 
generating linearly spaced values as opposed to the sibling function 
logspace, which generates logarithmically spaced values.
%}

w=linspace(0.01,fs*4,10000); %Generamos vector de frecuencia
figure (1);
freqs(bs_bp,as_bp,w); %Respuesta en frecuencia




%--------------------------- Parte c) --------------------------
%Discretice el filtro analógico para una frecuencia de muestreo de 9600 Hz con el
%método de interpolación ‘tustin’. Use la función c2d().

%{
Debemos convertir los vectores de numerador y denominador dados por la
función lp2bp a una función de transferencia de una sola variable para
poder ingresarla a la función c2d, para esto usamos: sys = tf(numerator,denominator)

La función c2d discretiza la función de transferencia de un filtro
analógico. Recibe como parámetros de entrada 
sysd = c2d(sysc,Ts,method) specifies the discretization method.

sysc — Continuous-time dynamic system
Ts — Sample time
method — Discretization method:
'zoh' (default) | 'foh' | 'impulse' | 'tustin' | 'matched' | 'least-squares'
%}

sysc = tf(bs_bp,as_bp); 
sysd = c2d(sysc,1/fs,'tustin');

%-------------------------- Parte d) ---------------------------
%{
Para poder usar la función freqz, hay que extraer la información del
numerador y denominador de la variable sysd que está en formato función de
transferencia, para esto usamos tfdata con el argumento 'v' para que
devuelva numerador y denominador como arreglos.
[num,den] = tfdata(sys,arg) 
%}

[bd,ad] = tfdata(sysd,'v');
figure (2);
freqz(bd,ad);


%------------------------- Parte e) -----------------------------
%Compare con la respuestas de ambos filtros












end