#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

const string PASSWORD = "PASSWORD";

void CaesarCipher(int& num, int shift){//num>=-25,num<=25
	num+=26;
	num+=shift;
	num%=26;//make sure it's within range
}

string encrypt(string text, string keyphrase){
	int keyval, keypos = 0;
	int currentChar;
	for (int i = 0;i<text.length();i++){
		keyval=toupper(keyphrase[keypos])-'A';
		currentChar = text[i];
		if(isupper(text[i])){
			currentChar-='A';
			CaesarCipher(currentChar, -3);
			currentChar*=2;
			if(currentChar>25)currentChar-=25;
			CaesarCipher(currentChar,keyval);
			CaesarCipher(currentChar,7);
			currentChar+='A';
		}
		else if(islower(text[i])){
			currentChar-='a';
			CaesarCipher(currentChar, -3);
			currentChar*=2;
			if(currentChar>25)currentChar-=25;
			CaesarCipher(currentChar,keyval);
			CaesarCipher(currentChar,7);
			currentChar+='a';
		}
		text[i]=char(currentChar);
		keypos = (keypos+1)%keyphrase.length();
	}
	return text;
}

string decrypt(string text, string keyphrase){
	int keyval, keypos = 0;
	int currentChar;
	for (int i = 0;i<text.length();i++){
		keyval=toupper(keyphrase[keypos])-'A';
		currentChar = text[i];
		if(isupper(text[i])){
			currentChar-='A';
			CaesarCipher(currentChar, -7);
			//cout<<currentChar;
			CaesarCipher(currentChar,-(keyval));
			//cout<<currentChar;
			if(currentChar%2!=0)
				currentChar+=25;
			currentChar/=2;
			CaesarCipher(currentChar,3);
			currentChar+='A';
		}
		else if(islower(text[i])){
			currentChar-='a';
			CaesarCipher(currentChar, -7);
			//cout<<currentChar;
			CaesarCipher(currentChar,-(keyval));
			//cout<<currentChar;
			if(currentChar%2!=0)
				currentChar+=25;
			currentChar/=2;
			CaesarCipher(currentChar,3);
			currentChar+='a';
		}
		text[i]=char(currentChar);
		keypos = (keypos+1)%keyphrase.length();
	}
	return text;
}

int main(int argc, char** argv) {
	string usertext,keyphrase,optext;
	string holdenter, userkey = "";
	int userchoice;
	char c;
	
	
	cout<<"Enter passkey: ";
	while(true){
		if(_kbhit()){
			c=_getche();
			if(c=='\r'){
				cout<<'\n';
				//cout<<userkey;
				break;
			}	
			else if(userkey.length()!=0&&c =='\b'){
				userkey = userkey.substr(userkey.length()-1);
				cout<<'\b';
			}
			else if (c!='\b'){
				cout<<"\b*";
				userkey+=c;
			}
		}
	}
	if (userkey!=PASSWORD)
		return 0;
	
	while(true){
		cout<<"Enter message: ";
		getline(cin, usertext);
		do{
			cout<<"Enter keyphrase(not case-sensitive): ";
			getline(cin, keyphrase);
		}while(keyphrase=="");
		
		do{
			cout<<"Enter 1 to encrypt or 2 to decrypt: ";
			cin>>userchoice;
		}while(!(userchoice==1||userchoice==2));
		if(userchoice==1)
			optext = encrypt(usertext,keyphrase);
		else
			optext = decrypt(usertext,keyphrase);
		cout<<optext<<'\n';
		getline(cin,holdenter);
	}
	return 0;
	
}
