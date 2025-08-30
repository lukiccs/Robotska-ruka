clc;

ik = inverseKinematics('RigidBodyTree', robot, 'SolverAlgorithm','LevenbergMarquardt');
weights = [1 1 1 1 1 1];
initialGuess = robot.homeConfiguration;

pocetnjaPozicija = [0 0 0.48];
zeljenjaPozicija = [0.15 0.2 0.3];
n = 30;

[xPutanja, yPutanja, zPutanja] = PravljenjeTrajektorije(pocetnjaPozicija, zeljenjaPozicija, n);

figure;
for i = 1:n
    pozicija = [xPutanja(i), yPutanja(i), zPutanja(i)];
    transformMatrica = trvec2tform(pozicija);
    [noviPolozaj, statusPolozaja] = ik('saka', transformMatrica, weights, initialGuess);
    upisDatoteka(noviPolozaj, 'podaci.txt');
    initialGuess = noviPolozaj;
    
    %provera da li je ugao unutar granica zadatih u RigidBodyModel.m
    if noviPolozaj(2) < min(lakat.PositionLimits) && noviPolozaj(2) > max(lakat.PositionLimits)
        disp('Položaj nije moguće postići.\n');
    end
    if noviPolozaj(3) < min(zglob_sake.PositionLimits) && noviPolozaj(4) > max(zglob_sake.PositionLimits)
        disp('Položaj nije moguće postići.\n');
    end
    %%%ovaj kod je samo peovera za sebe

    stvarniPolozaj = getTransform(robot, noviPolozaj, 'saka');
    stvarneKoordinate  = stvarniPolozaj(1:3, 4);
    if statusPolozaja.Status == "success"
        disp('Savrseno');
        show(robot, noviPolozaj, 'PreservePlot', false);
        camzoom(1.4);
        drawnow;
        %pause(0.03);
    elseif statusPolozaja.Status == "best available"
        fprintf('Ovo su zadate (%.3f, %.3f, %.3f), a ovo su stvarne: (%.3f, %.3f, %.3f)\n', zeljenjaPozicija, stvarneKoordinate);
        show(robot, noviPolozaj, 'PreservePlot', false);
        camzoom(1.4);
        drawnow;
        %pause(0.03);
    else
        disp('kurac');
    end
    
end
