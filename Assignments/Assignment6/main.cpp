/* Benjamin Bishop
 * 02 Apr. 2021
 * Assignment 6
 */
//Consistent bug of dupe listing of final character
//Inconsistent bug of words are not read or stored properly.

#include <string>
#include <iostream>
#include <map>
#include <fstream>



using namespace std;

void findDigit(map<string, pair<int,int>>&map, int loop){
    int counter = 0;
    auto itr = map.begin();

    loop = 10;//default loop size, used for finding most used numbers
    if (loop > map.size())
        loop = map.size();

    cout<<"\nTotal "<<map.size()<<" unique numbers, "<<loop<<" most used numbers: \n";
    for (int i = 0; i < loop; ++i) {
        int val = 0; //holds times occurred
        for (auto it = map.begin(); it != map.end();++it) { //sorting for the print
            if (it->second.first > val || (it->second.first == val && (it->second.second < itr->second.second))){
                val = it->second.first;
                itr=it;
                counter++;
            }
        }
        cout<<"Number "<< i+1 <<": "<<itr->first << " ,occurs (" <<val<<") time(s)"<<endl;
        map.erase(itr); //clear itr to pull new values
    }
}
void findWord(map<string, pair<int,int>>&map, int loop){
    int counter = 0;
    auto itr = map.begin();

    loop = 10;//default loop size, used for finding most used words
    if (loop > map.size())
        loop = map.size();

    cout<<"\nTotal "<<map.size()<<" unique words, "<<loop<<" most used words: \n";
    for (int i = 0; i < loop; ++i) {
        int val = 0;
        for (auto it = map.begin(); it != map.end();++it) { //sorting for the print
            if (it->second.first > val || (it->second.first == val && (it->second.second < itr->second.second))){
                val = it->second.first;
                itr=it;
                counter++;
            }
        }
        cout<<"Number "<< i+1 <<": "<<itr->first << " ,occurs (" <<val<<") time(s)"<<endl;
        map.erase(itr); //clear itr to pull new values
    }
}
void findChar(map<string, pair<int,int>>&map, int loop){
    int counter = 0;
    auto itr = map.begin();
    loop = 10; //for the 10 most used chars

    if (loop > map.size())
        loop = map.size();

    cout<<"\nTotal "<<map.size()<<" unique characters, "<<loop<<" most used characters: \n";
    for (int i = 0; i < loop; ++i) {
        int val = 0;
        for (auto it = map.begin(); it != map.end();++it) {
            if (it->second.first > val || (it->second.first == val && (it->second.second < itr->second.second))){
                val = it->second.first;
                itr=it;
                counter++;
            }
        }
        cout<<"Number "<< i+1 <<": ";
        if (itr->first == "\t")//tab
            cout<<"\\t"<<" ,occurs (" <<val<<") time(s)"<<endl;
        else if (itr->first == "\n")//tab
            cout<<"\\n"<<" ,occurs (" <<val<<") time(s)"<<endl;
        else
            cout<<itr->first<<" ,occurs (" <<val<<") time(s)"<<endl;
        map.erase(itr);
    }
}

int main() {
    //counters
    int numDigit;//counter for Digits
    int numChar; //counter for characters
    int numWord; // counter for words
    char c; //a char to hold each char read in while reading
    //strings to hold actual readable value
    string word; //string to hold words
    string character; //string to hold characters
    string digit; //string ot hold digits
    //maps to that can hold number of occurrence and order
    map<string, pair<int,int>> digitMap;
    map<string, pair<int,int>> charMap;
    map<string, pair<int,int>> wordMap;

    string fileName;
    cout<<"Enter in the file path\n";
    cin>>fileName;
    ifstream infile(fileName);

    while (!infile.is_open()) {
        cout<<"Error opening file: "<<fileName<<endl;
        cout<<"try raw address format of file";
        infile.clear();
        return 1;
    }
    //none so far
    while (!infile.eof()) {
        infile.get(c);
        ++numChar; //since we will count every character including spaces this should always increment
        if (isdigit(c) == 1) {//check if c is digit
            digit += c; //append to string
            if (!word.empty()) { //in the event of a number and had a word prior, it means we had a full word
                if (wordMap.find(word) == wordMap.end()) {//incrementing occurrence
                    wordMap.insert(make_pair(word, make_pair(1, numChar)));
                    ++numWord;
                }
                else {
                    ++wordMap[word].first;
                }
                word.clear();
            }
        }
        //glitch doesn't store words properly
        else if (isalpha(c) == 1) {//check if c is alphabetic
            word += c; //append to string words are case insensitive
            if (!digit.empty()) { //in the event of a word and had a number prior, it means we had a full number
                if (digitMap.find(digit) == digitMap.end()) {//incrementing occurrence
                    digitMap.insert(make_pair(digit, make_pair(1, numChar)));
                    ++numDigit;
                }
                else {
                    ++digitMap[digit].first;
                }
                digit.clear();
            }
        }
        else {//c is neither digit or alpha, likely a space, store the uniques away
            if (!digit.empty()) {
                if (digitMap.find(digit) == digitMap.end()) {//incrementing occurrence
                    digitMap.insert(make_pair(digit, make_pair(1, numChar)));
                    ++numDigit;
                }
                else {
                    ++digitMap[digit].first;
                }
                digit.clear();
            }
            if (!word.empty()) {
                if (wordMap.find(word) == wordMap.end()) {//incrementing occurrence
                    wordMap.insert(make_pair(word, make_pair(1, numChar)));
                    ++numWord;
                }
                else {
                    ++wordMap[word].first;
                }
                word.clear();
            }
        }
        character += c;//append c to characters
        ++charMap[character].first; //and to character then clear
        character.clear();
    }//end of while loop
    findDigit(digitMap, numDigit);
    findWord(wordMap, numWord);
    findChar(charMap, numChar);
    infile.close();
    return 0;
}//end of main
