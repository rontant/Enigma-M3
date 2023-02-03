# Enigma-M3
Enigma M3 Machine Engine Core<p>

Compile:<br>
g++ -o enigma EnigmaCore.cpp<p>

Example of usage: enigma myinputfile.txt<br>

The input file must follow the format below:<p>

<code>
InputText=[OLGS OUOIJSXIBYJEDXCDFWZBAOAGAIYZ]
UkwNumber=[1]
Wheel=[431]
RotorWheel=[SQL]
Ring=[DMZ]
Plugboard=[AT BG DV EW FR HN IQ JX KY LU]
</code>
<p>
There are 2 reflectors supported i.e. UKW-A and UKW-C.<br>
UkwNumber: 0=UKW-A, 1=UKW-B<p>

Rotor Wheels supported: 1 to 8.<p>

https://en.wikipedia.org/wiki/Enigma_machine
