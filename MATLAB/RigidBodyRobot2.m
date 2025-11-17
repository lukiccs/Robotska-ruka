clear;
clc;

robot = rigidBodyTree('DataFormat','row','MaxNumBodies',4);

% DH parametri [a alpha d theta]
dh = [0      pi/2  0.12  0;   % rame
      0.18   0     0     0;   % nadlaktica
      0.12   0     0     0];  % podlaktica


%% 1. RAME
rame = rigidBody('rame');
jRame = rigidBodyJoint('jRame','revolute');
setFixedTransform(jRame, dh(1,:), 'dh');
rame.Joint = jRame;
addBody(robot, rame, 'base');

%% 2. NADLAKTICA
nadlaktica = rigidBody('nadlaktica');
jNadlaktica = rigidBodyJoint('jNadlaktica','revolute');
setFixedTransform(jNadlaktica, dh(2,:), 'dh');
nadlaktica.Joint = jNadlaktica;
addBody(robot, nadlaktica, 'rame');

%% 3. PODLAKTICA
podlaktica = rigidBody('podlaktica');
jPodlaktica = rigidBodyJoint('jPodlaktica','revolute');
setFixedTransform(jPodlaktica, dh(3,:), 'dh');
podlaktica.Joint = jPodlaktica;
addBody(robot, podlaktica, 'nadlaktica');

%% 4. END EFFECTOR
saka = rigidBody('saka');
tformEE = trvec2tform([0.06 0 0]); % mala dužina za šaku
setFixedTransform(saka.Joint, tformEE);
addBody(robot, saka, 'podlaktica');

%% Prikaz
show(robot, 'Frames', 'on', 'Visuals', 'off');
view(120, 20);
axis equal;
