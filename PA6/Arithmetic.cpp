// Aryaman Gautam, agautam6, PA6
#include "List.h"
#include "BigInteger.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Should be provided two arguments: Infile and Outfile" << endl;
        return EXIT_FAILURE;
    }
    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);
    if (!infile) {
        cerr << "Unable to open infile" << endl;
        return EXIT_FAILURE;
    }
    if (!outfile) {
        cerr << "Unable to open outilfe" << endl;
        return EXIT_FAILURE;
    }
    string stringA;
    string stringB;
    infile >> stringA >> stringB;
    BigInteger A(stringA), B(stringB), two("2"), three("3"), nine("9"), sixteen("16");
    //A
    outfile << A << endl << endl;
    //B
    outfile << B << endl << endl;
    //A+B
    outfile << A+B << endl << endl;
    //A-B
    outfile << A-B << endl << endl;
    //A-A
    outfile << A-A << endl << endl;
    //3A-2B
    outfile << (three*A)-(two*B) << endl << endl;
    //AB
    outfile << A*B << endl << endl;
    //A^2
    outfile << A*A << endl << endl;
    //B^2
    outfile << B*B << endl << endl;
    //9A^4+16B^5
    outfile << (nine*A*A*A*A)+(sixteen*B*B*B*B*B) << endl << endl;

    infile.close();
    outfile.close();
    return 0;
}