clear;
clc;

dh_parametri = [0 0 0 0;
                0 pi/2 0.12 0;% a=0m, α=90°, d=0.12, θ=0
                0.18 0 0 0;% a=0.18m, α=0°, d=0, θ=0
                0.12 0 0 0; % a=0.12m, α=0°, d=0, θ=0
                0.06 0 0 0];% a=0.06m, α=0°, d=0, θ=0


robot = rigidBodyTree('DataFormat','row');

%%pravim bazu
baza = rigidBody('baza');
trt = rigidBodyJoint('trt', 'revolute');
setFixedTransform(trt, dh_parametri(1,:), 'dh');
baza.Joint = trt;
addBody(robot, baza, "base")
baza.Mass = 0.16990036;
baza.CenterOfMass = [0 0 0];
baza.Inertia = [0.0001061875 0.0001061875 0.000212375 0 0 0]

%%pravim rame i kuciste
kuciste = rigidBody('kuciste');
rame = rigidBodyJoint('rame', 'revolute');
setFixedTransform(rame, dh_parametri(2,:), 'dh');
kuciste.Joint = rame;
addBody(robot, kuciste, 'baza')
kuciste.Mass = 0.16990036;
kuciste.CenterOfMass = [0 0 0];
kuciste.Inertia = [0.0001061875 0.0001061875 0.000212375 0 0 0];

%%pravim lakat
nadlaktica = rigidBody('nadlaktica');
lakat = rigidBodyJoint('lakat', 'revolute');
setFixedTransform(lakat, dh_parametri(3,:), 'dh');
lakat.HomePosition = pi/2;
lakat.PositionLimits = deg2rad([0, 180]);
nadlaktica.Joint = lakat;
addBody(robot, nadlaktica, 'kuciste')
nadlaktica.Mass = 0.154383751;
nadlaktica.CenterOfMass = [0.09 0 0];
nadlaktica.Inertia = [0 (nadlaktica.Mass * dh_parametri(2,1)^2)/3 (nadlaktica.Mass * dh_parametri(2,1)^2)/3 0 0 0];

%%pravim zglob sake
podlaktica = rigidBody('podlaktica');
zglob_sake = rigidBodyJoint('zglob_sake', 'revolute');
setFixedTransform(zglob_sake, dh_parametri(4,:), "dh");
zglob_sake.PositionLimits = deg2rad([-120, 120]);
podlaktica.Joint = zglob_sake;
addBody(robot, podlaktica, 'nadlaktica');
podlakrica.Mass = 0.1312973;
podlakrica.CenterOfMass = [0.06 0 0];
podlakrica.Inertia = [0 (podlakrica.Mass * dh_parametri(3,1)^2)/3 (podlakrica.Mass * dh_parametri(3,1)^2)/3 0 0 0];

%%pravim saku(end effector)
saka = rigidBody('saka');
end_eff = rigidBodyJoint('end_eff', 'revolute');
setFixedTransform(end_eff, dh_parametri(5,:), "dh");
saka.Joint = end_eff;
addBody(robot, saka, 'podlaktica');

show(robot, [pi/3 pi/6 0 0 0])