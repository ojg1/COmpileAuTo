#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::vector;
using std::string;

/*

    CarET

    ^ file format
    author: OrangeJuiceGuy
    version: 1.0

*/


struct cetContainer {
    vector<string> STRINGS;
    vector<int> INTEGERS;
    vector<bool> BOOLS;
    vector<cetContainer> CONTAINERS;
};

int main(){

    std::ifstream desigcet("test.cet");

    if (!desigcet) {
        std::cout << "caret: fatal error: parser unable to open document";
        return 0;
    };

    cetContainer root = {{},{},{},{}};

    cetContainer* dir = &root;
    bool startParse = false;
    string ln;

    while (std::getline(desigcet, ln)) {
        if (ln == "^S") startParse = true;
        if (ln == "^E") startParse = false;

        if (startParse) {

            if (ln.substr(0,4) == "str!") {
                size_t ind = ln.find("=");
                if (ind == string::npos) {continue;};
                dir->STRINGS.push_back(ln.substr(ind+1));
            } else if (ln.substr(0,4) == "int!") {
                size_t ind = ln.find("=");
                if (ind == string::npos) {continue;};
                dir->INTEGERS.push_back(std::stoi(ln.substr(ind+1)));
            } else if (ln.substr(0,5) == "bool!") {
                size_t ind = ln.find("=");
                if (ind == string::npos) {continue;};
                if (ln.substr(ind+1) == "true") {
                    dir->BOOLS.push_back(true);
                } else if (ln.substr(ind+1) == "false") {
                    dir->BOOLS.push_back(false);
                };
            };

        };
    };

    return 0; 
};