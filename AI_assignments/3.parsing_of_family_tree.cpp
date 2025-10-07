#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

map<string, string> gender;                   
map<string, vector<string>> parentOf;         
map<string, vector<string>> childOf;       

void addParent(string parent, string child) {
    parentOf[parent].push_back(child);
    childOf[child].push_back(parent);
}

bool isFather(string p, string c) {
    if (gender[p] != "male") return false;
    for (auto &ch : parentOf[p]) if (ch == c) return true;
    return false;
}

bool isMother(string p, string c) {
    if (gender[p] != "female") return false;
    for (auto &ch : parentOf[p]) if (ch == c) return true;
    return false;
}

bool isSibling(string x, string y) {
    if (x == y) return false;
    for (auto px : childOf[x]) {
        for (auto py : childOf[y]) {
            if (px == py) return true;
        }
    }
    return false;
}

bool isBrother(string x, string y) {
    return gender[x] == "male" && isSibling(x, y);
}

bool isSister(string x, string y) {
    return gender[x] == "female" && isSibling(x, y);
}

bool isGrandparent(string gp, string c) {
    for (auto p : parentOf[gp]) {
        for (auto gc : parentOf[p]) {
            if (gc == c) return true;
        }
    }
    return false;
}

bool isAncestor(string a, string d) {
    for (auto p : parentOf[a]) {
        if (p == d) return true;
        if (isAncestor(p, d)) return true;
    }
    return false;
}

int main() {
   
    gender["Yashraj"] = "male";
    gender["Yash"] = "male";
    gender["Jay"] = "male";

    gender["Yashashree"] = "female";
    gender["Muskan"] = "female";
    gender["Sakshi"] = "female";
    gender["Hetal"] = "female";

    addParent("Yashraj", "Yash");       
    addParent("Hetal", "Yash");          
    addParent("Yashraj", "Sakshi");      
    addParent("Hetal", "Sakshi");      

    addParent("Yash", "Muskan");        
    addParent("Yashashree", "Muskan");  
    addParent("Sakshi", "Jay");          

    cout << "Is Yashraj father of Yash? " << (isFather("Yashraj", "Yash") ? "Yes" : "No") << endl;
    cout << "Is Hetal mother of Sakshi? " << (isMother("Hetal", "Sakshi") ? "Yes" : "No") << endl;
    cout << "Are Yash and Sakshi siblings? " << (isSibling("Yash", "Sakshi") ? "Yes" : "No") << endl;
    cout << "Is Yashraj grandfather of Muskan? " << (isGrandparent("Yashraj", "Muskan") ? "Yes" : "No") << endl;
    cout << "Is Hetal ancestor of Jay? " << (isAncestor("Hetal", "Jay") ? "Yes" : "No") << endl;

    return 0;
}
