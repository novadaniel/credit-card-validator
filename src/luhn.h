// luhn.h

#ifndef CREDIT_CARD_VALIDATOR_LUHN_H
#define CREDIT_CARD_VALIDATOR_LUHN_H
class Luhn {
public:
    static bool isValidCard(long long int card);
private:
    static bool hasValidPrefixAndSize(long long int card);
    static bool followsLuhn(long long int card);
};
#endif
