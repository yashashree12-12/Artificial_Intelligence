#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

vector<string> vars = {"WA", "NT", "SA", "Q", "NSW", "V", "T"};
vector<string> colors = {"Red", "Green", "Blue"};

map<string, vector<string>> neighbor = {
    {"WA", {"NT", "SA"}},
    {"NT", {"WA", "SA", "Q"}},
    {"SA", {"WA", "NT", "Q", "NSW", "V"}},
    {"Q", {"NT", "SA", "NSW"}},
    {"NSW", {"SA", "Q", "V"}},
    {"V", {"SA", "NSW"}},
    {"T", {}}
};

bool forwardCheck(map<string, vector<string>> &domains, string var, string value, map<string, string> &assign) {
    for (string nb : neighbor[var]) {
        if (assign.find(nb) == assign.end()) { 
            auto &d = domains[nb];
            d.erase(remove(d.begin(), d.end(), value), d.end());
            if (d.empty()) return false; 
        }
    }
    return true;
}

bool backtrack(map<string, string> &assign, map<string, vector<string>> domains) {
    if (assign.size() == vars.size()) return true; 

    string var;
    for (auto &v : vars) {
        if (assign.find(v) == assign.end()) {
            var = v;
            break;
        }
    }

    for (string color : domains[var]) {
        bool ok = true;
        for (string nb : neighbor[var]) {
            if (assign.find(nb) != assign.end() && assign[nb] == color) {
                ok = false; 
                break;
            }
        }
        if (!ok) continue;

        auto newDomains = domains; 
        assign[var] = color;

        if (forwardCheck(newDomains, var, color, assign)) {
            if (backtrack(assign, newDomains)) return true;
        }
        assign.erase(var); 
    }
    return false;
}

int main() {
    map<string, vector<string>> domains;
    for (auto &v : vars) domains[v] = colors;

    map<string, string> assign;

    if (backtrack(assign, domains)) {
        cout << "Solution:\n";
        for (auto &p : assign) {
            cout << p.first << " = " << p.second << "\n";
        }
    } else {
        cout << "No solution found.\n";
    }
}
