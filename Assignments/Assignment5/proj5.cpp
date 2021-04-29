//Benjamin Bishop
//20 Mar. 2021
//Assignment 5, cop4530

#include "passserver.h"
#include "hashtable.h"

using namespace std;
using namespace cop4530;

unsigned long prime_below(unsigned long x);				// two helpful functions to determine the proper prime numbers used in setting up the vector size. Whenever you need to set hash table to a new size "sz", call prime_below(sz) to determine the new proper underlying vector size. These two functions have been provided in hashtable.h and hashtable.hpp.
void setPrimes(std::vector<unsigned long>& prime);
static const unsigned int max_prime = 1301081;

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

unsigned long prime_below (unsigned long n)
{
    if (n > max_prime)
    {
        std::cerr << "** input too large for prime_below()\n";
        return 0;
    }
    if (n == max_prime)
    {
        return max_prime;
    }
    if (n <= 1)
    {
        std::cerr << "** input too small \n";
        return 0;
    }

    // now: 2 <= n < max_prime
    std::vector <unsigned long> v (n+1);
    setPrimes(v);
    while (n > 2)
    {
        if (v[n] == 1)
            return n;
        --n;
    }

    return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n)
void setPrimes(std::vector<unsigned long>& vprimes)
{
    int i = 0;
    int j = 0;

    vprimes[0] = 0;
    vprimes[1] = 0;
    int n = vprimes.capacity();

    for (i = 2; i < n; ++i)
        vprimes[i] = 1;

    for( i = 2; i*i < n; ++i)
    {
        if (vprimes[i] == 1)
            for(j = i + i ; j < n; j += i)
                vprimes[j] = 0;
    }
}

int main(){
    int hashSize = 0;
    string choice;
    string file = " ";
    string username = " ";
    string password = " ";

    cout<<"Enter preferred hash table capacity: ";
    cin >> hashSize;

    if (hashSize <= 1){
        cout<<"** input too small\n";
        cout<<"set to default capacity\n";
        hashSize = 11;
    }
    cout << prime_below(hashSize)<<endl;

    PassServer server(hashSize); //passserver based on hash size

    do{
        Menu(); //display menu
        cin >> choice;

        if (choice == "l"){//load from file
            cout<<"Enter password file name to load from: ";
            cin>> file;
            if (!server.load(file.c_str())) //file doesn't exist or cannot be opened
                cout<<"Error: Cannot open file "<< file << endl;
        }
        else if (choice == "a"){//add user
            cout<<"Enter username: ";
            cin>>username;
            cout<<"Enter password: ";
            cin>>password;
            cout<<"\n";
            if (!server.addUser(make_pair(username, password)))
                cout<<"*****Error: User already exists. Could not add user.\n";
            else
                cout<<"User "<< username << "added.\n";
        }
        else if (choice == "r"){//remove user
            cout<<"Enter username: ";
            cin>>username;
            if (!server.removeUser(username))
                cout<<"*****Error: User not found. Could not delete user\n";
            else
                cout<<"User "<<username<<"deleted.\n";
        }
        else if (choice == "c"){//change user password
            string newPassword = " ";
            cout<<"Enter username: ";
            cin>>username;
            cout<<"Enter password: ";
            cin>>password;
            cout<<"Enter new password: ";
            cin>>newPassword;
            cout<<"\n";
            if (!server.changePassword(make_pair(username,password),newPassword))
                cout<<"*****Error: Could not change user password\n";
            else
                cout<<"Password changed for user "<<username<< endl;

        }
        else if (choice == "f"){//find user
            cout<<"Enter username: ";
            cin>>username;
            cout<<"\n";
            if (!server.find(username))
                cout<<"User '"<<username<<"' not found. \n";
            else
                cout<<"User '"<<username<<"' found.\n";
        }
        else if (choice == "d"){//dump table
            server.dump();
        }
        else if (choice == "s"){//table size
            cout<<"Size of hashtable: "<<server.size()<<endl;
        }
        else if (choice == "w"){
            cout<<"Enter password file name to write to: ";
            cin >> file;
            if (!server.write_to_file(file.c_str()))
                cout<<"Error: File write failure\n";
        }
        else if (choice == "x"){
            exit(0);
        }
        else
            cout<<"*****Error: Invalid entry. Try again";
    } while (choice != "x"); //run until exit option is selected.
    return 0;
}//end of main
