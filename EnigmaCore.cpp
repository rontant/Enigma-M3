#include<string>
#include <array>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <fstream>
using namespace std;
// ****************************************
// My C++ version of the Enigma M3 Machine Engine Core
// by Ronnie Tantriady
// ****************************************

// Global Variables here

string TestText;

// These values will be replaced by values read from the file.
char RotorWheel[]= "DMZ";
char Ring[]="KLM";
int Wheel[]={5,3,1};
string plugboard="AT BG DV EW FR HN IQ JX KZ LU";
string pb=" "+plugboard+" ";
//pack my box with five dozen liquor jugs
string ukw[2][2]={	"YRUHQSLDPXNGOKMIEBFZCWVJAT", "UKW-B", //UKW-B
					"FVPJIAOYEDRZXWGCTKUQSBNMHL", "UKW-C"  // UKW-C
			
};

string WheelKeys [8][2] = {
	{"EKMFLGDQVZNTOWYHXUSPAIBRCJ","Q"},
	{"AJDKSIRUXBLHWTMCQGZNPYFVOE","E"},
	{"BDFHJLCPRTXVZNYEIWGAKMUSQO","V"},
	{"ESOVPZJAYQUIRHXLNFTGKDCMWB","J"},
	{"VZBRGITYUPSDNHLXAWMJQOFECK","Z"},
	{"JPGVOUMFYQBENHZRDKASXLICTW","ZM"},
	{"NZJHGRCXMYSWBOUFAIVLPEKQDT","ZM"},
	{"FKQHTLXOCBJSPDZRAMEWNIUYGV","ZM"}
};
string RotorCurrentKey [3];
string RotorCurrentTurnover[3];

int UkwNumber=0;
int WheelModel=0;


//-----------------------------------
int  AdvanceRotor(int RotorNum) {

	char NewRotChar;
    int i= ::RotorWheel[RotorNum];
	//std::cout<<"RotorNum is "<< RotorNum <<" value is "<< char(i)<< " or ASCII="<< i << "\n";

	if(i>=90) {
	     NewRotChar='A';
	} else {
		 NewRotChar=char(i+1);
	}
	RotorWheel[RotorNum]=NewRotChar;  
    //std::cout << "Wheel#" << RotorNum << " advanced to " << NewRotChar <<std::endl;
	
}

char PBEncrypt(char x) {

	char cipher;

	string tmp;
	if (pb.find(x)!= std::string::npos) {	

		int i=pb.find(x);
		if(pb.substr(i+1,1)==" ") {
			tmp=pb.substr(i-1,1);
		} else {
			tmp=pb.substr(i+1,1);
		}
		cipher=tmp[0];
		//std::cout<<"PB changed "<<x<<" to "<<cipher<<std::endl;
	} else {	
			cipher=x;    
	}

	return cipher;
}



//------------------------------------------------------------------
char WheelIt(char inp, string Key, char rot, char RingSetTo, bool Reverse) {
	if(inp<'A' || inp>'Z') {
		return 0;
	}
	
	char cipherTo;
	//std::cout<<"WheelIt para:"<< Key <<":"<<rot<<":"<<RingSetTo<<std::endl;
	
	int inpAsc=inp;
	int Shift=rot-65;
	int Shift2=RingSetTo-65;
	int MapEntryPointAsc=inpAsc + Shift - Shift2;
	// A->65 Z->90
	if(MapEntryPointAsc>90) {
	   MapEntryPointAsc -= 26;
	} else if(MapEntryPointAsc<65) {
	   MapEntryPointAsc += 26;
	}

	char MapToChar=MapEntryPointAsc;
	
	
	//std::cout<<"MapEntryPointAsc:"<<MapEntryPointAsc<<MapToChar<<std::endl;
	char cipherChar;
	if(Reverse) {
		int i=Key.find(MapToChar)+65;
		cipherChar=i;
			
	} else {
		int i=MapEntryPointAsc-65;
		string tmp = Key.substr(i,1); //--
		cipherChar=tmp[0];
		//cipherChar=Key.substr(i,1); //-----------------------------------------------

	}
	int ofset= cipherChar-MapToChar;
    int cipherToAsc=inpAsc+ofset;
	if(cipherToAsc>90) {
		cipherToAsc-=26;
	} else if (cipherToAsc<65) {
		cipherToAsc+=26;
	}
	
	cipherTo=cipherToAsc;
	
	//std::cout<<"---------------"<<std::endl;
	//std::cout << "Input:"<< inp<<  " ascii: "<<inpAsc<<std::endl;
	//std::cout << "Rotor shift relative to A:"<<Shift<<std::endl;
	//std::cout << MapEntryPointAsc<<std::endl;
	//std::cout << "Entry point:"<<MapToChar<<" which is linked to "<< cipherChar <<" Offset: "<<+ofset <<std::endl;
	//std::cout<< "Ciphered to:"<< cipherTo<<" ascii:"<< cipherToAsc <<std::endl;

    return cipherTo;
}

//--------------------------------------
char MainEncryption(char InputChar) {

	// Check if Rotor wheel 1 and/or Rotor wheel 2 must be turned
	int xx=::WheelKeys[Wheel[1]-1][1].find(::Wheel[1]);
	//std::cout<< xx << ::WheelKeys[Wheel[1]-1][1] <<::Wheel[1]<<std::endl;
	if (::WheelKeys[Wheel[1]-1][1].find(::Wheel[1]) != std::string::npos) {	
	   //std::cout<<"2 WHEEL TURN"<< std::endl;
	   AdvanceRotor(0);
	   AdvanceRotor(1);

	}
	// Check if Rotor Wheel 2 needs to be turned
	xx=::WheelKeys[Wheel[2]-1][1].find(::RotorWheel[2]);
	//std::cout<< xx << ::WheelKeys[Wheel[2]-1][1] <<::RotorWheel[2]<<std::endl;
	if (::WheelKeys[Wheel[2]-1][1].find(::RotorWheel[2]) != std::string::npos) {	
	   //std::cout<<"1 WHEEL TURN"<<std::endl;
	   AdvanceRotor(1);
	}
	AdvanceRotor(2);
	
	//std::cout << "Input: " << InputChar<<std::endl;
	char pbe= PBEncrypt(InputChar);
	//std::cout << "Plugboard 1 Out: " << pbe <<std::endl;
	// std::cout<<"Current Wheel 3 model is:"<<Wheel[2]<<std::endl;
	char t = WheelIt(pbe, ::WheelKeys[Wheel[2]-1][0],::RotorWheel[2],::Ring[2],false); // Right Rotor
	//std::cout<< "Right Wheel (3) Out: " << t <<std::endl;
	
	char u = WheelIt(t, ::WheelKeys[Wheel[1]-1][0],::RotorWheel[1],::Ring[1],false); // Middle Rotor
	//std::cout<< "Middle Wheel (2) Out: " << u <<std::endl;
	
	char v = WheelIt(u, ::WheelKeys[Wheel[0]-1][0],::RotorWheel[0],::Ring[0],false); // Left Rotor
	//std::cout<< "Left Wheel (1) Out: " << v <<std::endl;
	
	char w = WheelIt(v, ::ukw[::UkwNumber][0],'A','A',false); // // Because this is a reflector, the wheel position is fixed, thus always start with "A"
	//std::cout<< "Reflector out: " << w <<std::endl;
	
	char v1 = WheelIt(w, ::WheelKeys[Wheel[0]-1][0],::RotorWheel[0],::Ring[0],true); // Left Rotor
	//std::cout<< "Left Wheel (1) Out: " << v1 <<std::endl;
	
	char v2 = WheelIt(v1, ::WheelKeys[Wheel[1]-1][0],::RotorWheel[1],::Ring[1],true); // Middle Rotor
	//std::cout<< "Middle Wheel (2) Out: " << v2 <<std::endl;
	
	char v3 = WheelIt(v2, ::WheelKeys[Wheel[2]-1][0],::RotorWheel[2],::Ring[2],true); // Right Rotor
	//std::cout<< "Right Wheel (3) Out: " << v3 <<std::endl;

	char v4= PBEncrypt(v3);
	//std::cout<< "Pluboard 2 Out: " << v4 <<std::endl;
	//std::cout<<"---------------"<< std::endl;
	return (v4);
}

void ReadFile(string FilNam){
	string theText, fileContent;
	int p,q;

	//std::cout <<"Reading file "<<FilNam<<"....."<<std::endl;
	std::getline(std::ifstream(FilNam), fileContent, '\0');

    string KeyWord[]={"InputText", "UkwNumber", "Wheel", "RotorWheel","Ring","Plugboard"};
	int i,z;
	string TheValue;
	string tmp;
	for(i=0;i<(sizeof(KeyWord) / sizeof(KeyWord[0]));i++) {
		p=fileContent.find(KeyWord[i]+"=");
		z=KeyWord[i].length();

		if (p != std::string::npos) {
			q=fileContent.find("]",p+1);
			TheValue=fileContent.substr(p+z+2, q-p-z-2);

			//std::cout <<i+1<<"."<< KeyWord[i] << ":<" << TheValue <<">"<<std::endl;
			
			if (KeyWord[i]=="InputText") {
				::TestText=TheValue;
			}
			if (KeyWord[i]=="Wheel") {
				::Wheel[0]=stoi(TheValue.substr(0,1));
			    ::Wheel[1]=stoi(TheValue.substr(1,1));
				::Wheel[2]=stoi(TheValue.substr(2,1));
			}
			if (KeyWord[i]=="UkwNumber") {
				::UkwNumber=stoi(TheValue.substr(0,1));
			}
			if (KeyWord[i]=="RotorWheel") {
				strcpy(RotorWheel, TheValue.c_str());
			}		
			if (KeyWord[i]=="Ring") {
				strcpy(Ring, TheValue.c_str());
			}
			if (KeyWord[i]=="Plugboard") {
				plugboard=TheValue;
				pb=" "+plugboard+" ";
			}
		}
	}


}
string EnigmaIt(string txt) {
  char Za;
  int k;
  string tmp;
  string Op;
  for(k=0;k<TestText.length();k++) {
	  tmp=TestText.substr(k,1);
	  Za=toupper(tmp[0]);
	  if(Za>='A' && Za<='Z') { 
		Op+=MainEncryption(Za);
	  } else {
		Op+=Za;
	  }
  }

  return(Op);
}

// Main starts
int main(int argc,char* argv[]) {
  
  cout << "Enigma Thingy by Ronnie Tantriady\n\n";
  if(argc==1) {
	  cout<<"Usage: "<<argv[0]<<" <Text file name>\n";
	  return (0);
  }
  //cout << ukw[UkwNumber] << "\n";
  //cout << WheelKeys[5][0] << "\n";
  ReadFile(argv[1]);
  string CipheredText;
  cout << "Reflector:"<<ukw[UkwNumber][1]<<std::endl;
  cout << "Wheel:"<< Wheel[0]<<"-"<<Wheel[1]<< "-"<<Wheel[2] << "\n";
  cout << "Ring:" << Ring[0]<< Ring[1]<< Ring[2] << "\n";
  cout << "Rotor:"<< RotorWheel[0]<< RotorWheel[1]<< RotorWheel[2] << "\n";
  cout << "Plugboard:" << plugboard << "\n\n";
  cout << TestText<<std::endl;
  cout << "---------------------------------------"<<"\n";
  CipheredText=EnigmaIt(::TestText);
  cout<<CipheredText<<std::endl;
  return 0;
}