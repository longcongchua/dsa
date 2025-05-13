#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

typedef long long ll;
using namespace std;

struct company
{
    string name;
    string profit_tax;
    string address;
};

struct Node
{
    company company;
    Node *next;
};

typedef Node *HashTable[2000];

vector<company> readCompanyList(string file_name)
{
    ifstream file(file_name);
    if (!file.is_open())
    {
        cerr << "can not open file";
    }
    vector <company> companies;
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1+ 1);
        string name = line.substr(0, pos1);
        string profit_tax = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string address = line.substr(pos2 + 1);
        companies.push_back({name, profit_tax , address});
    }
    file.close();
    return companies;
}

ll hashString(string company_name) {
    const ll p = 31;    
    const ll m = 2000;   

    string last20;
    if (company_name.size() >= 20) {
        last20 = company_name.substr(company_name.size() - 20); 
    } else {
        last20 = company_name; 
    }
    ll hashValue = 0;
    for (size_t i = 0; i < last20.size(); ++i) {
        char c = last20[i];              
        hashValue = (hashValue * p + (ll)c) % m;  
    }
    return hashValue;
}


HashTable* createHashTable(const vector<company>& list_company) {
    HashTable* newhash = new HashTable[2000];
    for (int i = 0; i < 2000; ++i) {
       (*newhash)[i] = nullptr;
    }
    for (const company& company : list_company) {
        ll index = hashString(company.name);
        Node* new_node = new Node;
        new_node->company = company;
        new_node->next = (*newhash)[index];
        (*newhash)[index] = new_node;
    }
    return newhash;
}

void insert(HashTable* hash_table, company company){
    ll index = hashString(company.name);
    Node* p =new Node();
    p -> company = company;
    p -> next = *hash_table[index];
    *hash_table[index] = p;
}

company* search(HashTable* hash_table, string company_name){
    ll index = hashString(company_name);
    Node* p = *hash_table[index];
    while(p){
        if(p -> company.name == company_name){
            return &p -> company;
        }
        p = p -> next;
    }   
    return nullptr; 
}

void freeHashTable(HashTable* hash_table) {
    if (hash_table == nullptr) return;
    for (int i = 0; i < 2000; ++i) {
        Node* current = *hash_table[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        *hash_table[i] = nullptr;
    }
    delete[] hash_table;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: ./main MST.txt input.txt output.txt\n";
        return 1;
    }

    string mst_file = argv[1];
    string input_file = argv[2];
    string output_file = argv[3];

vector<company> company_list = readCompanyList(mst_file);
if (company_list.empty()) {
    cerr << "Company list is empty or could not be read from: " << mst_file << endl;
    return 1;
}

HashTable* hash_table = createHashTable(company_list);
if (hash_table == nullptr) {
    cerr << "Failed to create hash table." << endl;
    return 1;
}

ifstream fin(input_file);
if (!fin.is_open()) {
    cerr << "Could not open input file: " << input_file << endl;
    freeHashTable(hash_table);
    return 1;
}

ofstream fout(output_file);
if (!fout.is_open()) {
    cerr << "Could not open output file: " << output_file << endl;
    fin.close();
    freeHashTable(hash_table);
    return 1;
}

string company_name;
while (getline(fin, company_name)) {
    company* result = search(hash_table, company_name);
    if (result != nullptr) {
        fout << result->name << "|" << result->profit_tax << "|" << result->address << "\n";
    }
}

fin.close();
fout.close();
freeHashTable(hash_table);

    return 0;
}
