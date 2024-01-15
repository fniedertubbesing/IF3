/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include <string>

#include "SIMPLESOCKET.H"

#include "TASK1.H"


using namespace std;


class myServer : public TCPserver{
protected:
    TASK1::BlackBoxSafe *pwdBox_ = nullptr;

    string checkPassword(string password);
    void newPassword(int Length, int symbSet);

    public:

    string myResponse(string input);

    myServer(int port, int maxDataSizeRecv_) : TCPserver(port, maxDataSizeRecv_) {};
};


int main(){

	srand(time(nullptr));
	TCPserver srv(2022,25);
	srv.run();
}


string myServer::checkPassword(string password){
    return pwdBox_->input(password);
}

/*
void myServer::newPassword(int Length, int symbSet) {
    if (pwdBox_ != nullptr) {
        delete pwdBox_;
        pwdBox_ = nullptr;
    }
    this->pwdBox_ = new TASK1::BlackBoxSafe(Length, symbSet);
}
*/

string myServer::myResponse(string input){
int length, symbSet;
string pwd;
    if(input.compare(0, 7, "NEWPWD[")==0){
        sscanf(input.c_str(), "NEWPWD[%i,%i]", &length, &symbSet);
        //myServer::newPassword(length, symbSet);
        return "OK";
    }
    else if(input.compare(0,4, "PWD[") == 0){
        pwd = input.substr(4,input.size()-5);
        return checkPassword(pwd);
    }
    else{
        return "ERROR: unknown command";
    }

}

