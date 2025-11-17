function uredjeniPar  = trajektorijaSimulink(pocetnaPoz,zeljenaPoz, brojTacakaInterp)
%PRAVLJENJE_TRAJEKTORIJE
%   Za zadati pocetni i krajnji polozaj daje putanje za x, y, z sa n tacaka
%   izmedju
uredjeniPar = zeros(brojTacakaInterp, 3);
t = [0 1];
tq = linspace(0, 1, brojTacakaInterp);
xPutanja = interp1(t, [pocetnaPoz(1), zeljenaPoz(1)], tq, 'spline');
yPutanja = interp1(t, [pocetnaPoz(2), zeljenaPoz(2)], tq, 'spline');
zPutanja = interp1(t, [pocetnaPoz(3), zeljenaPoz(3)], tq, 'spline');
for i = 1:brojTacakaInterp
    uredjeniPar(i, :) = [xPutanja(i), yPutanja(i), zPutanja(i)];
end


end