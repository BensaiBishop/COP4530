//Benjamin Bishop
//20 Mar. 2021
//Assignment 5, cop4530



#include "passserver.h"


PassServer::PassServer(size_t size) { //default constructor

}

PassServer::~PassServer() {
    pServer.clear();
}

bool PassServer::load(const char *filename) {
    return(pServer.load(filename));
}

bool PassServer::addUser(pair<string, string> &kv) {
    return(pServer.insert(make_pair(kv.first,encrypt(kv.second))));
}

bool PassServer::addUser(pair<string, string> &&kv) {
    return(pServer.insert(make_pair(kv.first,encrypt(kv.second))));
}

bool PassServer::removeUser(const string &k) {
    return(pServer.remove(k));
}

bool PassServer::changePassword(const pair<string, string> &p, const string &newpassword) {
    if (pServer.match(make_pair(p.first, encrypt(p.second))) && encrypt(p.second) != encrypt(newpassword)){ //encrypt password before inserting into table
        pServer.insert(make_pair(p.first, encrypt(newpassword)));
        return true;
    }
    return false;
}

bool PassServer::find(const string &user) {
    return(pServer.contains(user));
}

void PassServer::dump() {
    return(pServer.dump());
}

size_t PassServer::size() {
    return(pServer.getSize());
}

bool PassServer::write_to_file(const char *filename) {
    return(pServer.write_to_file(filename));
}

string PassServer::encrypt(const string &str) {
    char salt[] = "$1$########";
    char *password = new char[100];
    strcpy(password,str.c_str()); //convert str to char array
    string newPassword = crypt(password,salt);
    //string newPassword = (password,salt);
    return newPassword.substr(12);//remove first 12 characters (only need 22 of 34)
}


