// luhn.cpp
#include <vector>
#include "luhn.h"
#include <iostream>
using namespace std;

/**
 * Verifies if the prefix and length match credit card company standards
 * @param card - The credit card number being verified
 * @return - a boolean that defines whether the credit card has a valid prefix and size
 */
bool Luhn::hasValidPrefixAndSize(long long int card) {
    string card_string = to_string(card);
    switch (card_string[0]) {
        case '4': // Visa
            return card_string.length() == 13 || card_string.length() == 16;
        case '5': // Mastercard
        case '6': // Discover
            return card_string.length() == 16;
        case '3':
            switch (card_string[1]) {
                case '4': // AMEX
                case '7':
                    return card_string.length() == 15;
                case '0':
                case '6':
                case '8':
                    return card_string.length() == 14;
                default:
                    return false;
            }
        default:
            return false;
    }
}

/**
 * Uses the luhn algorithm to verify that the card numbers are valid
 * @param card - The credit card number being verified
 * @return - a boolean that defines whether the credit card is valid according to the luhn algorithm
 */
bool Luhn::followsLuhn(long long int card) {
    int size = to_string(card).length();
    int oddSum = 0;
    int evenSum = 0;
    for (int i = 0; i < size; ++i) {
        if (i%2 == 0)
            evenSum += card%10;
        else {
            int doubleDigit = 2*(card%10);
            if (doubleDigit > 9)
                doubleDigit = ((doubleDigit - (doubleDigit%10))/10) + (doubleDigit%10);
            oddSum += doubleDigit;
        }
        card = card /10;
    }
    return (evenSum + oddSum) % 10 == 0;
}

/**
 * Checks if the credit card is valid
 * @param card  - The credit card number being verified
 * @return a boolean that defines whether the credit card is valid overall
 */
bool Luhn::isValidCard(long long int card) {
    return hasValidPrefixAndSize(card) && followsLuhn(card);
}

/**
 * Runs and outputs test cases on isValidCard
 * @return 0
 */
int main() {
    const long long int cards[10] = { // Test cases
            4532939889381396, // True
            4024007100464741, // True
            5575179819908399, // True
            348250579806417, // True
            358250579806417, // False
            6011579466480693, // True
            9011579466480693, // False
            4123456789101112, // False
            9011579466480693, // False
            3482505798064177, // False
    };
    for (long long card : cards) {
        cout << card;
        if (Luhn::isValidCard(card)) {
            std::cout << "\tValid\n";
        } else {
            std::cout << "\tInvalid\n";
        }
    }
    return 0;
}
