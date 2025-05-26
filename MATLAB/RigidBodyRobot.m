clear;
clc;

dh_parametri = [0 pi/2 0.12 0;% a=0m, α=90°, d=0.12, θ=0
                0.18 0 0 0;% a=0.18m, α=0°, d=0, θ=0
                0.12 0 0 0; % a=0.12m, α=0°, d=0, θ=0
                0.06 0 0 0];% a=0.06m, α=0°, d=0, θ=0


robot = rigidBodyTree('DataFormat','row');

%pravim oslonac
%oslonac = rigidBody('oslonac');
%prva_osa = rigidBodyJoint('prva_osa', 'revolute');
%setFixedTransform(prva_osa, dh_parametri(1,:), 'dh');
%oslonac.Joint = prva_osa;
%addBody(robot, oslonac, 'base');
%0 0 0 0;% a=0m, α=0°, d=0.08, θ=0

%pravim rame
razmak_izmedju = rigidBody('razmak izmedju');
rame = rigidBodyJoint('rame', 'revolute');
setFixedTransform(rame, dh_parametri(1,:), 'dh');
razmak_izmedju.Joint = rame;
addBody(robot, razmak_izmedju, 'base')

%pravim lakat
nadlaktica = rigidBody('nadlaktica');
lakat = rigidBodyJoint('lakat', 'revolute');
setFixedTransform(lakat, dh_parametri(2,:), 'dh');
lakat.HomePosition = pi/2;
lakat.PositionLimits = deg2rad([0, 180]);
nadlaktica.Joint = lakat;
addBody(robot, nadlaktica, 'razmak izmedju')

%pravim zglob sake
podlaktica = rigidBody('podlaktica');
zglob_sake = rigidBodyJoint('zglob_sake', 'revolute');
setFixedTransform(zglob_sake, dh_parametri(3,:), "dh");
zglob_sake.PositionLimits = deg2rad([-120, 120]);
podlaktica.Joint = zglob_sake;
addBody(robot, podlaktica, 'nadlaktica');

%pravim saku(end effector)
saka = rigidBody('saka');
end_eff = rigidBodyJoint('end_eff', 'revolute');
setFixedTransform(end_eff, dh_parametri(4,:), "dh");
saka.Joint = end_eff;
addBody(robot, saka, 'podlaktica');

