O0007 (DIAMOND SQUARE)
G21 G90 G17
G00 X0 Y0
M3
G01 X0 Y45 (SQUARE)
G01 X45 Y45
G01 X45 Y0
G01 X0 Y0
G01 X0 Y22.5 (DIAMOND)
X22.5 Y45
X45 Y22.5
X22.5 Y0
X0 Y22.5
G02 X22.5 Y45 I22.5 J0 
X45 Y22.5 I0 J-22.5
X22.5 Y0 I-22.5 J0
X0 Y22.5 I0 J22.5
M2
