#include <iostream>
#include <vector>
#include <unordered_map>
#include <ranges>
#include <cstdlib>
#include <filesystem>
#include <regex>
#include 

/*

       ___            _   
      / __\___   __ _| |_ 
     / /  / _ \ / _` | __|
    / /__| (_) | (_| | |_ 
    \____/\___/ \__,_|\__|
                      

    COmpileAuTo
    Version: 0.1.1
    Author: OrangeJuiceGuy (ojg1)
    Required: a operating system

*/

using std::cin;
using std::cout;
using std::getline;

using std::string;
using std::vector;
using std::unordered_map;
using std::regex;
using std::smatch;

struct keywTypes {
    string Alias;
    string FileAlias;
    string Version;
    string Path;
    string ProgramLangSupport;
    bool Found;
};

struct COATConfig {
    string CurrentCompiler;
    string Language;

};

void ParsePathCompiler(string os,  unordered_map<string,keywTypes> &comps) {

    if (os == "Windows") {

        unordered_map<string,keywTypes> keyc = {
            {"gcc.exe",   {"GNU Compiler Collection",           "gcc",      "N/A", "N/A", "C, Universal",                                   false}},
            {"g++.exe",   {"GNU C++ Compiler",                  "g++",      "N/A", "N/A", "C++",                                            false}},
            {"clang.exe", {"C Language Family Frontend",        "clang",    "N/A", "N/A", "Variants of C, C++ (including objective-c<++>)", false}},
            {"msvc.exe",  {"Microsoft Visual C++ Compiler",     "cl",       "N/A", "N/A", "C++",                                            false}},
            {"nvcc.exe",  {"NVIDIA Cuda Compiler",              "nvcc",     "N/A", "N/A", "C++/CUDA",                                       false}}
        };

        vector<string> ekeyc = {
            "gcc.exe",
            "g++.exe",
            "clang.exe",
            "cl.exe",
            "nvcc.exe"
        };


        string WinPath = std::getenv("PATH");
        string seperator = ";";

        auto split_view = WinPath | std::views::split(seperator);
        vector<string> pathVars = split_view | std::ranges::to<vector<string>>();

        for (const auto &dir : pathVars) {
            if (std::filesystem::exists(dir) && std::filesystem::is_directory(dir)) {
                for (const auto &entry : std::filesystem::directory_iterator(dir)) {

                    string filename = entry.path().filename().string();

                    if (std::find(ekeyc.begin(), ekeyc.end(), filename) == ekeyc.end()) {

                        keyc[filename].FileAlias = filename;
                        keyc[filename].Path = entry.path().parent_path().string() + filename;
                        keyc[filename].Found = true;

                        string pathComm = keyc[filename].Path + "--version";

                        string result = "";
                        char buffer[128];

                        FILE* output = _popen(pathComm.c_str(), "r");

                        while (fgets(buffer, sizeof(buffer), output) != nullptr) {
                            result += buffer;
                        };

                        regex p("\d+\.\d+(\.\d+)*");
                        smatch match;

                        if (std::regex_match(result, match, p)) {
                            keyc[filename].Version = match[0];
                        };

                    };

                };
            };
        };

        comps = keyc;

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

    unordered_map<string,keywTypes> comps = {};
    string SelectedLanguage = "detectFileExtension";
    string SearchCompilerMethod = "fullFilename";
    string CurrentCompiler = "";
    string OperatingSystem = "";

    string RunString = "";

    if (args[0] != "compauto" || args[0] != "coat") {return 0;}

    #ifdef _WIN32
        OperatingSystem = "Windows";
    #elif __linux__
        OperatingSystem = "Linux";
    #elif __APPLE__
        OperatingSystem = "MacOS";
    #endif

    if (args[1] == "pickcomp") {

        cout << "These compilers were found in your PATH environment variable. \n";
        cout << "Select compiler: \n";

        vector<string> available = {};

        int i = 0;

        for (const auto& [key,value] : comps) {
            if (value.Found) {
                available.push_back(key);
                cout << "[" << std::to_string(i) << "] " << value.FileAlias << " (" << value.Alias << ")\n";
            };
        };

        cout << ":";
   
        int choice;
        cin >> choice;
        


    };

    return 0;
};