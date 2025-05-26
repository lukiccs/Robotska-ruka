function [koraciServo] = rad2servo(ugloviServo)
%RAD2SERVO Podatke uglova koji su u radiijanima prebacuje u podatke koje
%servo razume
%   Za servo Waveshare ST3215-HS(4096 koraka)

normalizovanUgao = mod(ugloviServo, 2*pi);
koraciServo = round((normalizovanUgao / (2 * pi)) * 4096);
end