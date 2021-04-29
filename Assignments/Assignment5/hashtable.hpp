//Benjamin Bishop
//20 Mar. 2021
//Assignment 5, cop4530

template<typename K, typename V>
cop4530::HashTable<K, V>::HashTable(size_t size) { //constructor
    hTableSize = 0;
    hTable.resize(prime_below(size));
}

template<typename K, typename V>
HashTable<K, V>::~HashTable() { //deconstructor
    makeEmpty();
}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K &k) const{ // check if k is in the table
    for(auto i = hTable[myhash(k)].begin(); i != hTable[myhash(k)].end();i++){
        if (i->first == k)
            return true;
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::match(const pair<K, V> &kv) const{//sourced from fig 5.9
    auto & whichList = hTable[myhash(kv.first)];
    return find (begin(whichList),end(whichList), kv ) != end(whichList);
}

template<typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V> &kv) { //sourced from fig 5.10
    int temp = hTableSize +1;
    auto & whichList = hTable[myhash(kv.first)];
    if(find(begin(whichList), end(whichList),kv) != end(whichList)) // if its in the table return false
         return false;

    if(contains(kv.first) == true){
        remove(kv.first);
    }

    whichList.push_back(kv);
    hTableSize++;

    if(temp > hTable.size())
         rehash();
    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(pair<K, V> &&kv) { //sourced from fig 5.10
    int temp = hTableSize +1;
    auto & whichList = hTable[myhash(kv.first)];
    if(find(begin(whichList), end(whichList),kv) != end(whichList)) // if its in the table return false
        return false;

    if(contains(kv.first) == true){
        remove(kv.first);
    }

    whichList.push_back(kv);
    hTableSize++;

    if(temp > hTable.size())
        rehash();
    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K &k) { //delete k and associated value; modified from fig 5.9,
    auto & whichList = hTable[myhash(k)];
    for (auto itr = whichList.begin(); itr  != whichList.end() ; ++itr) {// iterate through list, find k and v if in list.
        if(itr == end(whichList)) //not in the list return false
            return false;
        if (itr->first == k){
            whichList.erase(itr); // else we found it erase it.
            --hTableSize;
            return true;
        }
    }
}

template<typename K, typename V>
void HashTable<K, V>::clear() {
    makeEmpty();
}

template<typename K, typename V>
bool HashTable<K, V>::load(const char *filename) { //load contents of filename
    ifstream instream;
    instream.clear();
    instream.open(filename);
    K key;
    V value;

    if(!instream) //couldn't open file return false
        return false;

    while(!instream.eof()){ //while not end of file insert pairs of kv
        instream >> key >> value;
        insert(make_pair(key,value));
    }
    instream.close();
    return true;
}

template<typename K, typename V>
void HashTable<K, V>::dump() { // 'dump' the contents of the table on the screen
    for (int i = 0; i < hTable.size(); i++) { //use for loops to cout the table.
        cout << "v["<< i << "]: ";
        for(auto itr = hTable[i].begin(); itr != hTable[i].end(); ++itr){
            if(itr != hTable[i].begin()) //use the colon the separate multiple pairs.
                cout << ":";
            cout << itr->first << " " << itr->second;
        }
        cout << endl;
    }
}
template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) {
    ofstream outstream;
    outstream.open(filename);
    K key;
    V value;

    if(!outstream) // couldn't create file return false
        return false;

    for(int i = 0; i < hTable.size(); i++){
        auto& newList = hTable[i];
        auto itr = newList.begin();

        if(!newList.empty()){
            outstream << itr->first << " " << itr->second << endl;
            while(++itr != newList.end()){
                outstream << itr->first << " " << itr->second << endl;
            }
        }
    }
    outstream.close();
    return true;
}
}

template<typename K, typename V>
int cop4530::HashTable<K, V>::getSize() {
    return hTableSize;
}

template<typename K, typename V>
void cop4530::HashTable<K, V>::makeEmpty() { //delete all elements from the table ; sourced from fig 5.9
    hTableSize = 0;                 //set the size to 0
    for(auto & x : hTable){ // for all, interate through and clear.
        x.clear();
    }
}

template<typename K, typename V>
void cop4530::HashTable<K, V>::rehash() { //code sourced from fig 5.22 ,rehashing
    auto oldList = hTable;
    hTable.resize(prime_below(2*hTable.size()));
    makeEmpty();
    for(auto& thisList : oldList)
        for(auto& x: thisList)
            insert(move(x));
}

template<typename K, typename V>
size_t cop4530::HashTable<K, V>::myhash(const K &k) const { //return the index of where k is stored; sourced from fig 5.7
    static hash<K> hash;
    return hash(k) % hTable.size();
}
///////////////////
//given
///////////////////
// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long cop4530::HashTable<K, V>::prime_below (unsigned long n)
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
template <typename K, typename V>
void cop4530::HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
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
