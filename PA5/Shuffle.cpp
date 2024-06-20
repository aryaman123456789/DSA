#include "List.h"
#include <stdexcept>
#include <iomanip>
#include <iostream>
using namespace std;

void shuffle(List& D) {
    List firstHalf;
    List secondHalf;
    int elementX;
    int elementY;
    int totalElements = D.length();
    D.moveFront();

    // Split the deck into two halves
    while (D.position() < (totalElements / 2)) {
        elementX = D.moveNext();
        firstHalf.insertBefore(elementX);
    }
    while (D.position() < totalElements) {
        elementY = D.moveNext();
        secondHalf.insertBefore(elementY);
    }
    // Clear the original deck
    D.clear();
    firstHalf.moveFront();
    secondHalf.moveFront();
    while ((firstHalf.position() < firstHalf.length()) && (secondHalf.position() < secondHalf.length())) {
        elementY = secondHalf.moveNext();
        D.insertBefore(elementY);
        elementX = firstHalf.moveNext();
        D.insertBefore(elementX);
    }
    // Add any remaining elements from the first half
    while (firstHalf.position() < firstHalf.length()) {
        elementX = firstHalf.moveNext();
        D.insertBefore(elementX);
    }
    // Add any remaining elements from the second half
    while (secondHalf.position() < secondHalf.length()) {
        elementY = secondHalf.moveNext();
        D.insertBefore(elementY);
    }
}

int main(int argc, char* argv[]) {
    int n;
    int shuffleCount;
    int cardCount;
    List D;
    List CopyDeck;
    if (argc != 2) {
        throw invalid_argument("must be 2 arguments");
    }
    // Parse the card count from the command line
    cardCount = stoi(argv[1]);
    if (cardCount <= 0) {
        throw invalid_argument("card count must be positive, not negative");
    }
    cout << "deck size\tshuffle count" << endl;
    string div(30, '-');
    cout << div << endl;    
    // Loop through different deck sizes
    for (n = 1; n <= cardCount; n++) {
        shuffleCount = 0;
        // Prepare the original deck
        D.moveBack();
        D.insertBefore(n-1);
        // Copy the original deck for later comparison    
        CopyDeck = D;
        // Perform the initial shuffle
        shuffle(D);
        shuffleCount++;
        // Shuffle until the deck returns to its original order
        while (!(CopyDeck == D)) {
            shuffle(D);
            shuffleCount++;
        }
        // Output deck size and shuffle count
        cout << " " << left << setw(16) << n << shuffleCount << endl;
    }    
}
