clc;

Tau = zeros(brojTacakaInterp, 4);
Tau1 = zeros(brojTacakaInterp, 4);
M = zeros(4, 4, brojTacakaInterp);
C = zeros(brojTacakaInterp, 4);
G = zeros(brojTacakaInterp, 4);

for i = 1:brojTacakaInterp
    M(:,:,i) = massMatrix(robot, generalisaneKoordinate(i,:));
    C(i,:) = velocityProduct(robot, generalisaneKoordinate(i,:), generalisaneKoordinatedot(i,:));
    G(i,:) = gravityTorque(robot, generalisaneKoordinate(i,:));
end

%Koristeci Lagranzeve jednacine druge vrste
for i = 1:brojTacakaInterp
    Tau(i,:) = M(:,:,i)*generalisaneKoordinateddot(i,:)' + C(i,:)*generalisaneKoordinatedot(i,:)' + G(i,:)';
end
%Koristeci built in funkciju
for i = 1:brojTacakaInterp
    Tau1(i,:) = inverseDynamics(robot, generalisaneKoordinate(i,:), generalisaneKoordinatedot(i,:),generalisaneKoordinateddot(i,:))';
end


