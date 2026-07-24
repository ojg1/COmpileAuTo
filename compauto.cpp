#include <iostream>
#include <vector>
#include <unordered_map>
#include <ranges>
#include <cstdlib>
#include <filesystem>

/*

       ___            _   
      / __\___   __ _| |_ 
     / /  / _ \ / _` | __|
    / /__| (_) | (_| | |_ 
    \____/\___/ \__,_|\__|
                      

    COmpileAuTo
    Version: 0.1.0
    Author: OrangeJuiceGuy (ojg1)
    Required: a operating system

*/

using std::cin;
using std::cout;
using std::getline;

using std::string;
using std::vector;
using std::unordered_map;

struct keywTypes {
    string Alias;
    string PathName;
    string Version;
    string ProgramLangSupport;
    bool Found;
};

void ParsePathCompiler(string os, vector<string> &comps) {

    if (os == "Windows") {

        unordered_map<string,keywTypes> keyw = {
            {"gcc",   {"GNU Compiler Collection",           "gcc.exe",      "N/A", "C, Universal",                                   false}},
            {"g++",   {"GNU C++ Compiler",                  "g++.exe",      "N/A", "C++",                                            false}},
            {"clang", {"C Language Family Frontend",        "clang.exe",    "N/A", "Variants of C, C++ (including objective-c<++>)", false}},
            {"msvc",  {"Microsoft Visual C++ Compiler",     "cl.exe",       "N/A", "C++",                                            false}},
            {"nvcc",  {"NVIDIA Cuda Compiler",              "nvcc.exe",     "N/A", "C++/CUDA",                                       false}}
        };


        string WinPath = std::getenv("PATH");
        string seperator = ";";

        auto split_view = WinPath | std::views::split(seperator);
        vector<string> pathVars = split_view | std::ranges::to<vector<string>>();

        for (const auto &dir : pathVars) {
            if (std::filesystem::exists(dir) && std::filesystem::is_directory(dir)) {
                for (const auto &entry : std::filesystem::directory_iterator(dir)) {

                    if () {

                    };

                };
            };
        };

    } else if (os == "Linux") {

    } else if (os == "MacOS") {

    };

    return;
};  

int main(int argc, char *argv[]){

    vector<string> args = {};

    for (int i;i<argc;i++) {
        args.push_back(argv[i]);
    };  

    vector<string> comps = {};
    string SelectedLanguage = "detectFileExtension";
    string CurrentCompiler = "";
    string OperatingSystem = "";

    if (args[0] != "compauto" || args[0] != "coat") {return 0;}

    #ifdef _WIN32
        OperatingSystem = "Windows";
    #elif __linux__
        OperatingSystem = "Linux";
    #elif __APPLE__
        OperatingSystem = "MacOS"
    #endif

    if (args[1] == "pickcomp") {

        cout << "These compilers were found in your PATH environment variable. \n";
        cout << "Select compiler: \n";

        string path = std::getenv("PATH");


    };

    return 0;
};