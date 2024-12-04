#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
using namespace std;

struct trienode {
    unordered_map<char,trienode*> children;
    bool wordend;
    string condition;
    string review;
    string rating;
    string date;
    string usefulCount;
    trienode() : wordend(false) {}
};
class Trie {
    trienode* root;
    public:
    Trie() {
        root = new trienode;
    }
    void insert(string &drugName, string &condition, string &review, string rating, string &date, string usefulCount) {
        trienode* curr = root;
        for(char c : drugName) {
            if(curr->children.find(c) == curr->children.end()) {
                curr->children[c] = new trienode;
            }
            curr = curr->children[c];
        }
        curr->wordend = true;
        curr->condition = condition;
        curr->review = review;
        curr->rating = rating;
        curr->date = date;
        curr->usefulCount = usefulCount;
    }
    void search(string drugName) {
        trienode* curr = root;
        for(char c : drugName) {
            if(curr->children.find(c) == curr->children.end()) {
                cout << "Not found" << endl;
            }
            curr = curr->children[c];
        }
        if(curr->wordend) {
            cout << curr->condition << endl;
            cout << curr->review << endl;
            cout << curr->rating << endl;
            cout << curr->date << endl;
            cout << curr->usefulCount << endl;
        } else {
            cout << "Not found" << endl;
        }
    }
};
void parse(Trie &trie,string line) {
    stringstream ss(line);
    string drugName,id,condition,review,date,usefulCount,rating;
    getline(ss, id, '\t');
    getline(ss, drugName, '\t');
    getline(ss, condition, '\t');
    getline(ss, review, '\t');
    getline(ss, rating, '\t');
    getline(ss, date, '\t');
    getline(ss, usefulCount, '\t');
    trie.insert(drugName,condition,review,rating,date,usefulCount);
}

int main() {
    Trie trie;
    ifstream myfile("drugsComTest_raw.tsv");
    string line;
    while(getline(myfile, line)) {
        parse(trie, line);
    }
    string input = "";
    cout  << "enter a drug name, or type exit to stop."<< endl;
    while (getline(cin, input)) {
        if(input == "exit") {
            break;
        }
        trie.search(input);
        cout <<"enter a drug name, or type exit to stop."<<endl;
    }
    cout<< "thank you"<< endl;
return 0;
};

// https://www.digitalocean.com/community/tutorials/trie-data-structure-in-c-plus-plus
// https://algo.monster/liteproblems/208
// https://www.geeksforgeeks.org/implementation-of-trie-prefix-tree-in-c/
// https://www.baeldung.com/cs/tries-prefix-trees
// https://www.geeksforgeeks.org/introduction-to-trie-data-structure-and-algorithm-tutorials/