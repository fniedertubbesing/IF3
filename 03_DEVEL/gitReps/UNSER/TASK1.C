/*
 * TASK1.C
 *
 *  Created on: 10.09.2019
 *      Author: aml
 */

#include <cstdlib>
#include <cstring>
#include <iostream>

#include "TASK1.H"

namespace TASK1{


string BlackBoxUnsafe::getSymbols(){
	return string(charSymbArray_);
};

BlackBoxUnsafe::BlackBoxUnsafe(int pwdLength, int symbSetSize){
	if((symbSetSize < 1) || (symbSetSize > SYMBOLS.length()) ){
		lengthSymbArray_ = SYMBOLS.length();
	}else{
		lengthSymbArray_ = symbSetSize;
	}
	// extract and save the subset of valid symbols
	charSymbArray_ = new char [lengthSymbArray_ + 1];
	strncpy(charSymbArray_, SYMBOLS.c_str(), lengthSymbArray_);
	// create and save random password
	pwd_ = this->randomPwd(pwdLength);
	return;
}

string BlackBoxUnsafe::input(string strPwd){
	if(strPwd.compare(pwd_) == 0){
		return string("ACCESS ACCEPTED");
	}
	return string("ACCESS DENIED");
}

string BlackBoxUnsafe::randomPwd(int l){
	int symbolIdx;
	if(l < MINIMAL_PWD_LENGTH){ l = MINIMAL_PWD_LENGTH;};
	pwd_ = string("");
	for(int i=0; i < l; i++){
		symbolIdx = rand() % lengthSymbArray_;
		pwd_ += charSymbArray_[symbolIdx];
	}
	return pwd_;
}
//_________________________________________________________________________________________________


string BlackBoxSafe::input(string strPwd){
    if(sha256(strPwd) == this->pwd_){ //compare encrypted passwords
        return "right password";
    }
    else{
        return "wrong password";
    }
}

string Server::checkPassword(string password){
    return pwdBox->input(password);
}

void Server::newPassword(int Length, int symbSet){
    if(pwdBox != nullptr){ //free allocated memory if pwdBox Object was already created
        delete pwdBox;
        pwdBox = nullptr;
    }
    BlackBoxSafe *pwdBox = new BlackBoxSafe(Length,symbSet);
}

Server::Server(){
    newPassword(4,4); //default values to start with
}

Server::~Server(){
    delete pwdBox;
}

void demoTASK1_00(){
	string pwd("meinpassword");
	cout << "pwd   : " << pwd << endl;
	cout << "SHA256: " << sha256(pwd) << endl;
	pwd = ("einpassword");
	cout << "pwd   : " << pwd << endl;
	cout << "SHA256: " << sha256(pwd) << endl;
	return;
}

void demoTASK1_01(){
	TASK1::BlackBoxUnsafe bs(4,4);
	cout << bs.pwd_ << endl;

	cout << bs.input(bs.pwd_) << endl;

	return;
}

}


