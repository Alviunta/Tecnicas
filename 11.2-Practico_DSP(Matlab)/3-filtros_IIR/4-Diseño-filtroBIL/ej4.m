%Ejercicio 4

fc1=300;
fc2=3400;
fs=fc2*4;
T=1/fs;

%Frecuencias digitales

wd1=fc1*2*pi/fs;
wd2=fc2*2*pi/fs;

%Precombado

wa1=2/T * tan(wd1/2);
wa2=2/T * tan(wd2/2);

%Diseño del filtro pasabajo analógico

[z,p,k]=cheb1ap(10,3);         %%Nos devuelve los ceros, polos y ganancia de un filtro Chebyshev 
                               %tipo 1 de orden 10 con 3 dB en la banda pasante
[bs_lp, as_lp]=zp2tf(z,p,k);

%Diseño del filtro pasabanda analogico

BW=wa2-wa1;
Wo=sqrt(wa1*wa2);

[bs_bp,as_bp]=lp2bp(bs_lp, as_lp,Wo,BW);  %Pasamos del filtro pasabajos al pasabanda

H=tf(bs_bp,as_bp);

w=linspace(0.01,fs*4,10000); %Generamos vector de frecuencia
hs=freqs(bs_bp,as_bp,w); %Respuesta en frecuencia

figure
semilogy(w/2/pi, abs(hs),'linewidth',3) %Ploteamos la magnitud vs frecuencia
grid on
hold on

%Diseño del filtro pasabanda digital

Hd=c2d(H,1/fs,'tustin'); %Pasamos del pasabanda analogico al digital
%bz=Hd.Numerator(1,1);
%az=Hd.Denominator(1,1);
bz=[7.20030377490484e-05,0,-0.000720030377490484,0,0.00324013669870718,0,-0.00864036452988580,0,0.0151206379273002,0,-0.0181447655127602,1.33019212105641e-17,0.0151206379273002,6.13934825102959e-17,-0.00864036452988574,3.78593142146825e-17,0.00324013669870719,1.66274015132051e-18,-0.000720030377490484,-1.27903088563116e-19,7.20030377490484e-05];
az=[1,-12.6440894069122,78.4432294037807,-319.143359684830,958.893703313876,-2268.21939485429,4390.71178994281,-7129.22803506197,9865.94743214953,-11753.2222102256,12119.1190564904,-10834.6299845059,8382.57722298424,-5581.13880698730,3165.75842596846,-1505.64647453562,585.921272647860,-179.583801123655,40.7058353135996,-6.06750026898441,0.445688646011624];
[hz,f] = freqz(bz,az,10000,fs);

semilogy(f,abs(hz),'-g','linewidth',3);

[l1,l2]=meshgrid(fc1,[10^(-25) 1]);
plot(l1,l2,'-m','linewidth',2);

[l1,l2]=meshgrid(fc2,[10^(-25) 1]);
plot(l1,l2,'-m','linewidth',2);

xl=xlabel('Frecuencia[Hz]');
yl=ylabel('Magnitus');
grid on

ll=legend('Filtro pasabanda analogico','Filtro pasabanda digital','Frec, de corte 1','Frec. de corte 2');

%font_label=23;
%font_tick=17;
%font_legend=23;

%set(gca,'XTickMode','auto','YTickMode','auto','FontSize',font_tick);

%set(xl,'FontSize',font_label);
%set(yl,'FontSize',font_label);
%set(ll,'FontSize',font_legend);
