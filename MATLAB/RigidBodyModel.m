clear;
clc;

dh_parametri = [0 0 0.08 0;% a=0m, α=0°, d=0, θ=0
                0 pi/2 0.04 0; % a=0.12m, α=0°, d=0, θ=0
                0.18 0 0 0;
                0.12 0 0 0;
                0.06 0 0 0];% a=0.06m, α=0°, d=0, θ=0

robot = rigidBodyTree('DataFormat','row');
robot.Gravity = [0 0 -9.81];


%pravim kuciste
kuciste = rigidBody('kuciste');
rotKucista = rigidBodyJoint('rotKucista', 'fixed');
setFixedTransform(rotKucista, dh_parametri(1,:), 'dh');
kuciste.Joint = rotKucista;
addBody(robot, kuciste, 'base');
kuciste.Mass = 0.16990036;
kuciste.CenterOfMass = [0 0 0];
kuciste.Inertia = [0.0001061875 0.0001061875 0.000212375 0 0 0];

%pravim rame i nosac za motor ramena
nosacMotora1 = rigidBody('nosacMotora1');
rame = rigidBodyJoint('rame', 'revolute');
setFixedTransform(rame, dh_parametri(2,:), 'dh');
nosacMotora1.Joint = rame;
addBody(robot, nosacMotora1, 'kuciste');
nosacMotora1.Mass = 0;
nosacMotora1.CenterOfMass = [0 0 0];
nosacMotora1.Inertia = [0 0 0 0 0 0];

%pravim lakat i nadlakticu
nadlaktica = rigidBody('nadlaktica');
lakat = rigidBodyJoint('lakat', 'revolute');
setFixedTransform(lakat, dh_parametri(3, :), 'dh');
lakat.PositionLimits = deg2rad([0, 180]);
nadlaktica.Joint = lakat;
addBody(robot, nadlaktica, 'nosacMotora1');
nadlaktica.Mass = 0.154383751;
nadlaktica.CenterOfMass = [0.09 0 0];
nadlaktica.Inertia = [0 (nadlaktica.Mass * dh_parametri(3,1)^2)/3 (nadlaktica.Mass * dh_parametri(3,1)^2)/3 0 0 0];

%pravim zglob sake i podlakticu
podlaktica = rigidBody('podlaktica');
zglobSake = rigidBodyJoint('zglobSake', 'revolute');
setFixedTransform(zglobSake, dh_parametri(4, :), 'dh');
zglobSake.PositionLimits = deg2rad([-120, 120]);
podlaktica.Joint = zglobSake;
addBody(robot, podlaktica, 'nadlaktica');
podlaktica.Mass = 0.13129731;
podlaktica.CenterOfMass = [0.06 0 0];
podlaktica.Inertia = [0 (podlaktica.Mass * dh_parametri(4,1)^2)/3 (podlaktica.Mass * dh_parametri(4,1)^2)/3 0 0 0];

%pravim end eff
endEff = rigidBody('endEff');
kraj = rigidBodyJoint('kraj', 'revolute');
setFixedTransform(kraj, dh_parametri(5, :), 'dh');
endEff.Joint = kraj;
addBody(robot, endEff, 'podlaktica');
endEff.Mass = 0.02216277;
endEff.CenterOfMass = [0.06 0 0];
endEff.Inertia = [0 (endEff.Mass * dh_parametri(5,1)^2)/3 (endEff.Mass * dh_parametri(5,1)^2)/3 0 0 0];
