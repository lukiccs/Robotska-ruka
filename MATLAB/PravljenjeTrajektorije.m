function [x_putanja, y_putanja, z_putanja] = PravljenjeTrajektorije(pocetna_poz,krajnja_poz, n)
%PRAVLJENJE_TRAJEKTORIJE
%   Za zadati pocetni i krajnji polozaj daje putanje za x, y, z sa n tacaka
%   izmedju
t = [0 1];
tq = linspace(0, 1, n);
x_putanja = interp1(t, [pocetna_poz(1), krajnja_poz(1)], tq, 'spline');
y_putanja = interp1(t, [pocetna_poz(2), krajnja_poz(2)], tq, 'spline');
z_putanja = interp1(t, [pocetna_poz(3), krajnja_poz(3)], tq, 'spline');


end