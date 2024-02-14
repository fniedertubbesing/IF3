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



/**
 *
 * \class client
 *
 * \brief Implementiert die von der Aufgabenstellung geforderten Funktionen
 *
 */

class client : public TCPclient{
private:
    int pl_; // Passwortlänge
    int al_; // Alphabetlänge
public:
    void set(int pl, int al); // Setzen der Passwort.- unf Alphabetlänge
    client() : TCPclient(){};
    string pwdguess(); // Methode zum erraten eines Passworts
    string newpwd(); // Erzeugen eines Strings für den Server mit Passwort.- und Alphabetlänge

};

int main() {
	srand(time(NULL));
	client c;
	string host = "localhost";
	string msg;
	string imsg;

	long int i;

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



    for(int pl = TASK1::MINIMAL_PWD_LENGTH; pl<=7; pl++){
        for(int al = 2; al<=7; al++){

            c.set(pl, al);

            for(int v = 1; v<=10;v++){
                c.sendData(c.newpwd());
                imsg = c.receive(3);

                if(imsg.compare("OK") == 0){

                }
                else{
                    cout << "Fehler bei der Passwortgenerierung" << endl;
                    exit(0);
                }
                i = 0;
                do{
                    i++;
                    c.sendData(c.pwdguess());
                    imsg = c.receive(6);
                    if(imsg.compare("TRUE") == 0){
                        cout << "pl = " << pl << "  " << "al = " << al << " " << "i = " << i << endl;
                        break;
                    }
                }while(1);


            }
        }
    }
    c.sendData("BYEBYE");



	return 0;
	}


/**
 *
 * \brief Methode erzeugt ein zufällig generiertes Passwort mit der Länge pl und aus dem Alphabet al.
 *
 */

string client::pwdguess(){
    string pwdGuess = TASK1::SYMBOLS.substr(0,pl_);

    for(int i = 0; i < pl_; i++){
        pwdGuess[i] = TASK1::SYMBOLS[rand()% al_];
    }
    return "PWD[" + pwdGuess + ']';
}

/**
 *
 * \brief Methode setzt die Passwort- und die Alphabetlänge.
 *
 */

void client::set(int pl, int al){

pl_= pl;
al_= al;
return;
}

/**
 *
 * \brief Methode erzeugt den Befehl zum erstellen eines neues Passworts.
 *
 */

string client::newpwd(){

string test;

test = "NEWPWD[" + to_string(pl_) + ',' + to_string(al_) + ']';

//cout << test<< endl;

return test;
}

