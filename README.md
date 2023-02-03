# Enigma-M3
Enigma M3 Machine Engine Core

Compile:
g++ -o enigma EnigmaCore.cpp

Usage:
<quote>enigma followed by the input file name</quote>
e.g. enigma myinputfile.txt

The input file must follow the format below:

<code>
InputText=[OLGS OUOIJSXIBYJEDXCDFWZBAOAGAIYZ]
UkwNumber=[1]
Wheel=[431]
RotorWheel=[SQL]
Ring=[DMZ]
Plugboard=[AT BG DV EW FR HN IQ JX KY LU]
</code>

There are 2 reflectors supported i.e. UKW-A and UKW-C.
UkwNumber: 0=UKW-A, 1=UKW-B

Rotor Wheels supported: 1 to 8.

https://en.wikipedia.org/wiki/Enigma_machine
