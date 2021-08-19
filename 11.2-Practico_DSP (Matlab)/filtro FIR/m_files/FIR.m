function Hd = FIR
%FIR Returns a discrete-time filter object.

% MATLAB Code
% Generated by MATLAB(R) 9.2 and the DSP System Toolbox 9.4.
% Generated on: 09-Sep-2020 13:21:56

% FIR Window Bandpass filter designed using the FIR1 function.

% All frequency values are in Hz.
Fs = 44100;  % Sampling Frequency

N    = 50;       % Order
Fc1  = 300;      % First Cutoff Frequency
Fc2  = 3400;     % Second Cutoff Frequency
flag = 'scale';  % Sampling Flag
Beta = 7.5;      % Window Parameter
% Create the window vector for the design algorithm.
win = kaiser(N+1, Beta);

% Calculate the coefficients using the FIR1 function.
b  = fir1(N, [Fc1 Fc2]/(Fs/2), 'bandpass', win, flag);
Hd = dfilt.dffir(b);

% [EOF]
