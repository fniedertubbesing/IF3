/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants

#include "SIMPLESOCKET.H"
#include "TASK1.H"

using namespace std;

class client : public TCPclient{
private:
    int pl_; // Passwortlänge
    int al_; // Alphabetlänge
public:
    void set(); // Setzen der Passwort.- unf Alphabetlänge
    client() : TCPclient(){};
    string pwdguess(); // Methode zum erraten eines Passworts
    string newpwd(); // Erzeugen eines Strings für den Server mit Passwort.- und Alphabetlänge

};

int main() {
	srand(time(NULL));
	client c;
	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 2022);

	/*int i=0;
	bool goOn=1;
	while(goOn){ // send and receive data
		if((rand() % 20) < i++){
			msg = string("BYEBYE");
			goOn = 0;
		}else{
			msg = string("client wants this");
		}
		cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msg = c.receive(32);
		cout << "got response:" << msg << endl;
		sleep(1);
*/

    c.set();
    c.sendData(c.newpwd());
    string imsg = c.receive(2);

    int i;

    if(imsg == "OK"){
    imsg = "FALSE";
    i = 0;

    while(imsg == "FALSE"){
    c.sendData(c.pwdguess());
    imsg = c.receive(5);
    i++;
    }
    }
    else{cout << "Fehler" << endl;
    }

    cout << "Das Passwort wurde nach " << i << " Versuchen erraten";


	return 0;
	}


string client::pwdguess(){
    string pwdGuess = TASK1::SYMBOLS.substr(0,pl_);

    for(int i = 0; i < pl_; i++){
        pwdGuess[i] = TASK1::SYMBOLS[rand()% al_];
    }
    return pwdGuess;
}

void client::set(){
cout << "Bitte geben Sie die Passwortlänge und die Alphabetlänge an:" << endl;
cin >> pl_;
cout << endl;
cin >> al_ ;
cout<< endl;
return;
}

string client::newpwd(){
return "NEWPWD[" + pl_ + ',' + al_ + ']';
}

