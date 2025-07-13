function [status] = WiFiKomunikacija(fajl)
%SLANJESERIAL Salje podatke iz fajla u ESP32 preko WiFi 

%WifiKom = tcpclient("192.168.1.5", 1234);%Beograd
WifiKom = tcpclient("192.168.0.34", 1234);%Cacak


podaci = load(fajl);


for i = 1:size(podaci, 1)
    linijaPodataka = sprintf('%.0f %.0f %.0f %.0f\n', podaci(i, 1), podaci(i, 2), podaci(i, 3), podaci(i, 4));
    write(WifiKom, linijaPodataka, "string");
    pause(0.1);
    %handshake protokol
    while true
        if WifiKom.NumBytesAvailable > 0
            konfirmacija = read(WifiKom, WifiKom.NumBytesAvailable,"string");
            if contains(konfirmacija, "nastavi")
                pause(0.05);
                break;
            end
        end
    end
end

end

%handshake protocol je koriscen