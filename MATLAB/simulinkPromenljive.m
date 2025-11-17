vreme = (0:brojTacakaInterp-1)*dt;

TauSimulink = [vreme', Tau];
%MSimulink = [vreme', M];
CSimulink = [vreme', C];
GSimulink = [vreme', G];

generalisaneKoordinateSimulink = [vreme', generalisaneKoordinate];
generalisaneKoordinatedotSimulink = [vreme', generalisaneKoordinatedot];
generalisaneKoordinateddotSimulink = [vreme', generalisaneKoordinatedot];