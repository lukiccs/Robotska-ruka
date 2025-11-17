vreme = (0:brojTacakaInterp-1)*dt;

TauSimulink = [vreme', Tau];

generalisaneKoordinateSimulink = [vreme', generalisaneKoordinate];
generalisaneKoordinatedotSimulink = [vreme', generalisaneKoordinatedot];
generalisaneKoordinateddotSimulink = [vreme', generalisaneKoordinatedot];