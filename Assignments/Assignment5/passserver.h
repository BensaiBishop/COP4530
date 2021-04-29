//Benjamin Bishop
//20 Mar. 2021
//Assignment 5, cop4530

#ifndef PROJ5_PASSSERVER_H
#define PROJ5_PASSSERVER_H

#include "hashtable.h"

using namespace std;
using namespace cop4530;

class PassServer{
public:
    PassServer(size_t size=101); //constr

    ~PassServer(); //deconstructor

    bool load(const char *filename); //load a password file into the hash table

    bool addUser(std::pair<string, string> & kv); // add a new user name and password

    bool addUser(std::pair<string, string> && kv); // move version of add user

    bool removeUser(const string & k); // delete an existing user

    bool changePassword(const pair<string, string> &p, const string &newpassword);// change existing users password

    bool find(const string & user);// check if the user exists

    void dump(); // display entire hash table

    size_t size(); // return the size of the hast table

    bool write_to_file(const char *filename); // write username and password to file with filename.

private:
    string encrypt(const string & str); //encrpytion parameter str return encrypted string.

    HashTable<string, string> pServer;
};

#include "passserver.cpp"

#endif //PROJ5_PASSSERVER_H
