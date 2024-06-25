// Aryaman Gautam, agautam6, PA8
#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    // Check if two arguments (Infile and Outfile) are provided
    if (argc != 3) {
        cerr << "Should be provided two arguments: Infile and Outfile" << endl;
        return EXIT_FAILURE;
    }

    // Open input and output files
    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);

    // Check if the input file is successfully opened
    if (!infile) {
        cerr << "Unable to open infile" << endl;
        return EXIT_FAILURE;
    }

    // Check if the output file is successfully opened
    if (!outfile) {
        cerr << "Unable to open outfile" << endl;
        return EXIT_FAILURE;
    }

    Dictionary dictionary;
    string line;
    string key;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789"; 
    size_t begin;
    size_t end;
    while (getline(infile, line)) {
        size_t len = line.length();
        begin = line.find_first_not_of(delim, 0);
        while (begin < len) {
            end = line.find_first_of(delim, begin);
            key = line.substr(begin, end-begin);
            for (size_t i = 0; i < key.length(); i++) {
                key[i] = tolower(key[i]);
            }
            if (!key.empty()) {
                if (dictionary.contains(key)) {
                    dictionary.setValue(key, (dictionary.getValue(key) + 1));
                } else {
                    dictionary.setValue(key, 1);
                }
            }
            begin = line.find_first_not_of(delim, end);
        }
    }
    outfile << dictionary;
    infile.close();
    outfile.close();
    return 0;
}