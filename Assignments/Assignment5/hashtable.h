//Benjamin Bishop
//20 Mar. 2021
//Assignment 5, cop4530

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <list>
#include <algorithm>
#include <vector>
#include <crypt.h> //crypt.h file not found

using namespace std;
namespace cop4530 {
    template<typename K, typename V>
    class HashTable {

    public:
        HashTable(size_t size = 101); //constructor

        ~HashTable(); //deconstructor

        bool contains(const K &k) const; //check if key is in the hash table

        bool match(const std::pair<K, V> &kv) const; // check if key value pair is in table

        bool insert(const std::pair<K, V> &kv); // add key value pair into the table

        bool insert(std::pair<K, V> &&kv); // move version of insert

        bool remove(const K &k); // delete key value pair

        void clear(); // delete all elements of the hashtable

        bool load(const char *filename); // load contents of file with filename

        void dump(); // display all entries in the hash table

        bool write_to_file(const char *filename); // write all elemens in table to file with filename

        int getSize(); // function to return size of table

    private:

        vector<list<pair<K, V>>> hTable; // vector of lists for hashtable

        int hTableSize;

        void makeEmpty(); //delete elements in hash table

        void rehash(); //rehash function

        size_t myhash(const K &k) const; // return index of vector entry where k is stored

        unsigned long
        prime_below(unsigned long x); // helper functions to determine proper prime numbers when setting vector size.

        void setPrimes(std::vector<unsigned long> &prime);

        static const unsigned int max_prime = 1301081; // max_prime is used by the helpful functions provided to you.

        static const unsigned int default_capacity = 11; // the default_capacity is used if the initial capacity of the underlying vector of the hash table is zero.
    };

#include "hashtable.hpp"


#endif
