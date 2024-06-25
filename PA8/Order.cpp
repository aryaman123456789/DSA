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

    // Create a Dictionary object to store key-value pairs
    Dictionary dictionary;

    // Variables to store the current line and line number
    string currLine;
    int currLineNumber = 1;

    // Read lines from the input file and insert them into the Dictionary
    while (getline(infile, currLine)) {
        dictionary.setValue(currLine, currLineNumber++);
    }

    // Write the first string representation (key-value pairs in alphabetical order)
    outfile << dictionary.to_string(); 

    // Write the second string representation (keys in pre-order traversal)
    outfile << dictionary.pre_string(); 

    // Close input and output files
    infile.close();
    outfile.close();

    return 0;
}