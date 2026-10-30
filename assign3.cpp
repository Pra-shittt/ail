#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;
vector<string> states = {"Maharashtra", "Gujarat", "MadhyaPradesh","Chhattisgarh", "Goa", "Karnataka", "Telangana"};
vector<string> colors = {"Red", "Green", "Blue", "Yellow"};
map<string, vector<string>> neighbors = {
    {"Maharashtra", {"Gujarat", "MadhyaPradesh", "Chhattisgarh","Telangana", "Karnataka", "Goa"}},
    {"Gujarat", {"Maharashtra", "MadhyaPradesh"}},
    {"MadhyaPradesh", {"Gujarat", "Maharashtra", "Chhattisgarh"}},
    {"Chhattisgarh", {"MadhyaPradesh", "Maharashtra", "Telangana"}},
    {"Telangana", {"Maharashtra", "Chhattisgarh", "Karnataka"}},
    {"Karnataka", {"Goa", "Maharashtra", "Telangana"}},
    {"Goa", {"Maharashtra", "Karnataka"}}
};
string getMRVState(map<string, string>& assignment,map<string, set<string>>& domains) {
    string bestState = "";
    int minColors = 100;
    for (string state : states) {
        if (assignment.find(state) == assignment.end()) {
            if (domains[state].size() < minColors) {
                minColors = domains[state].size();
                bestState = state;
            }
        }
    }
    return bestState;
}
bool backtrack(map<string, string>& assignment,map<string, set<string>>& domains) {
    if (assignment.size() == states.size()) {
        return true;
    }
    string state = getMRVState(assignment, domains);
    for (string color : domains[state]) {
        assignment[state] = color;
        map<string, set<string>> newDomains = domains;
        bool valid = true;
        for (string neighbor : neighbors[state]) {
            if (assignment.find(neighbor) == assignment.end()) {
                newDomains[neighbor].erase(color);
                if (newDomains[neighbor].empty()) {
                    valid = false;
                    break;
                }
            }
        }
        if (valid && backtrack(assignment, newDomains)) {
            return true;
        }
        assignment.erase(state);
    }
    return false;
}
int main() {
    map<string, string> assignment;
    map<string, set<string>> domains;
    set<string> allColors;
    for (string color : colors) {
        allColors.insert(color);
    }
    for (string state : states) {
        domains[state] = allColors;
    }
    if (backtrack(assignment, domains)) {
        cout << "Map Coloring Solution:\n";
        for (string state : states) {
            cout << state << " : " << assignment[state] << endl;
        }
    }
    else {
        cout << "No valid coloring found.\n";
    }
    return 0;
}
