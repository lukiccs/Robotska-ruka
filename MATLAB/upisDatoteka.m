function [status] = upisDatoteka(podaci, imeDatoteke)
%UPISDATOTEKA 
%   Za datu matricu uglova za servo motore daje datoteku koja se moze
%   ucitati u Arduino IDE i te vrednosti se mogu dati motorima

fajl = fopen(imeDatoteke, 'a+');

if fajl == -1
    disp('Greska pri otvaranju fajla!');
    status = -1;
else
    fprintf(fajl, '%.0f %.0f %.0f %.0f\n', rad2servo(podaci));
    disp('Upisano!');
    status = 0;
end

fclose(fajl);

