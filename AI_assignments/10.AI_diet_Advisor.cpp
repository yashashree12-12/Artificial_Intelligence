#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Rule {
    vector<string> conditions;
    string conclusion;
};

bool conditionsSatisfied(const vector<string>& conditions, const map<string, bool>& facts) {
    for (auto& cond : conditions) {
        if (facts.find(cond) == facts.end() || facts.at(cond) == false)
            return false;
    }
    return true;
}

void forwardChaining(vector<Rule>& rules, map<string, bool>& facts) {
    bool newFactAdded = true;

    while (newFactAdded) {
        newFactAdded = false;
        for (auto& rule : rules) {
            if (conditionsSatisfied(rule.conditions, facts) && !facts[rule.conclusion]) {
                cout << "Applying rule: IF ";
                for (size_t i = 0; i < rule.conditions.size(); i++) {
                    cout << rule.conditions[i];
                    if (i != rule.conditions.size() - 1) cout << " AND ";
                }
                cout << " THEN " << rule.conclusion << endl;

                facts[rule.conclusion] = true;
                newFactAdded = true;
            }
        }
    }
}

int main() {
    map<string, bool> facts;
    string input;

    cout << "=== AI Diet Advisor ===\n";
    cout << "Answer yes/no for the following questions:\n\n";

    cout << "Do you want to lose weight? ";
    cin >> input; facts["Wants_Weight_Loss"] = (input == "yes");

    cout << "Do you want to gain muscle? ";
    cin >> input; facts["Wants_Muscle_Gain"] = (input == "yes");

    cout << "Are you vegetarian? ";
    cin >> input; facts["Vegetarian"] = (input == "yes");

    cout << "Do you have diabetes? ";
    cin >> input; facts["Has_Diabetes"] = (input == "yes");

    cout << "Do you have high blood pressure? ";
    cin >> input; facts["Has_BP"] = (input == "yes");

    // Initialize possible conclusions
    facts["Keto_Diet"] = false;
    facts["High_Protein_Diet"] = false;
    facts["Vegan_Diet"] = false;
    facts["Balanced_Diet"] = false;
    facts["Low_Sodium_Diet"] = false;

    // Define rules
    vector<Rule> rules = {
        { {"Wants_Weight_Loss", "Vegetarian"}, "Vegan_Diet" },
        { {"Wants_Weight_Loss", "Has_Diabetes"}, "Keto_Diet" },
        { {"Wants_Muscle_Gain", "Vegetarian"}, "High_Protein_Diet" },
        { {"Has_BP"}, "Low_Sodium_Diet" },
        { {"Wants_Muscle_Gain", "Has_BP"}, "Balanced_Diet" }
    };

    cout << "\nRunning inference...\n\n";
    forwardChaining(rules, facts);

    cout << "\n✅ Suggested Diet Plans:\n";
    bool found = false;
    for (auto& f : facts) {
        if (f.second && (f.first.find("_Diet") != string::npos)) {
            cout << "- " << f.first << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No specific diet plan found. Try a Balanced Diet.\n";

    return 0;
}

//o/p
// PS E:\AI_LAB> g++ AI_diet_Advisor.cpp -o diet
// >>
// PS E:\AI_LAB> ./diet
// === AI Diet Advisor ===
// Answer yes/no for the following questions:
//
// Do you want to lose weight? yes
// Do you want to gain muscle? no
// Are you vegetarian? yes
// Do you have diabetes? no
// Do you have high blood pressure? no
// Running inference...
// Applying rule: IF Wants_Weight_Loss AND Vegetarian THEN Vegan_Diet
//
// ✅ Suggested Diet Plans:
// - Vegan_Diet