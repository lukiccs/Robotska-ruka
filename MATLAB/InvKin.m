clc;

ik = inverseKinematics('RigidBodyTree', robot, 'SolverAlgorithm','LevenbergMarquardt');
weights = [1 1 1 1 1 1];
initialGuess = robot.homeConfiguration;


dt = 0.3;
pocetnaPozicija = [0 0 0.48];
zeljenjaPozicija = [0.15 0.2 0.3];
brojTacakaInterp = 297;
[xPutanja, yPutanja, zPutanja] = PravljenjeTrajektorije(pocetnaPozicija, zeljenjaPozicija, brojTacakaInterp);
generalisaneKoordinate = zeros(brojTacakaInterp, 4);
generalisaneKoordinatedot = zeros(brojTacakaInterp, 4);
generalisaneKoordinateddot = zeros(brojTacakaInterp, 4);

for i = 1:brojTacakaInterp
    pozicija = [xPutanja(i), yPutanja(i), zPutanja(i)];
    transformMatrica = trvec2tform(pozicija);
    [generalisanaKoordinata, statusPolozaja] = ik('endEff', transformMatrica, weights, initialGuess);
    initialGuess = generalisanaKoordinata;
    generalisaneKoordinate(i, :) = generalisanaKoordinata;
    
    %provera da li je ugao unutar granica zadatih u RigidBodyModel.m
    if generalisanaKoordinata(2) < min(lakat.PositionLimits) && generalisanaKoordinata(2) > max(lakat.PositionLimits)
        disp('Položaj nije moguće postići.\n');
    end
    if generalisanaKoordinata(3) < min(zglobSake.PositionLimits) && generalisanaKoordinata(4) > max(zglobSake.PositionLimits)
        disp('Položaj nije moguće postići.\n');
    end
end

%numericka diferencijacija
for i = 2:brojTacakaInterp-1
    generalisaneKoordinatedot(i,:) = (generalisaneKoordinate(i+1,:) - generalisaneKoordinate(i-1,:)) / (2*dt);
    generalisaneKoordinateddot(i,:) = (generalisaneKoordinatedot(i+1,:) - generalisaneKoordinatedot(i-1,:)) / (2*dt);

end

