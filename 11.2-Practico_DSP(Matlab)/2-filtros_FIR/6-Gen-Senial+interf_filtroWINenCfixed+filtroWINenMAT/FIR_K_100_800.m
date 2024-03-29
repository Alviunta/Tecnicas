function Hd = FIR_K_100_800
%FIR_K_100_800 Returns a discrete-time filter object.

% MATLAB Code
% Generated by MATLAB(R) 9.6 and DSP System Toolbox 9.8.
% Generated on: 10-Sep-2020 11:44:06

% FIR Window Bandpass filter designed using the FIR1 function.

% All frequency values are in Hz.
Fs = 10000;  % Sampling Frequency

N    = 100;      % Order
Fc1  = 100;      % First Cutoff Frequency
Fc2  = 800;      % Second Cutoff Frequency
flag = 'scale';  % Sampling Flag
Beta = 5;        % Window Parameter
% Create the window vector for the design algorithm.
win = kaiser(N+1, Beta);

% Calculate the coefficients using the FIR1 function.
b  = fir1(N, [Fc1 Fc2]/(Fs/2), 'bandpass', win, flag);
Hd = dfilt.dffir(b);
% Set the arithmetic property.
set(Hd, 'Arithmetic', 'fixed', ...
    'CoeffWordLength', 16, ...
    'CoeffAutoScale', true, ...
    'Signed',         true, ...
    'InputWordLength', 16, ...
    'inputFracLength', 15, ...
    'FilterInternals',  'FullPrecision');
denormalize(Hd);


% [EOF]
