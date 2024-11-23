#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <gmpxx.h>

const long INVALID_STATE = 1365;
const int MAX = 1367;
const int POWEROF = 4;

bool hasAllChars(const std::string& str){
    const std::string subset = "abcd";
    for(int i = 0; i < subset.length(); i++){
        char ch = subset[i];
        bool found = false;
        for(int j = 0; j < str.length(); j++){
            if(str[j] == ch){
                found = true;
                break;
            }
        }
        if(!found){
            return false;
        }
    }
    return true;
}

std::string intToString(int value){
    std::string result;
    for(int i = 0; i < 5; i++){
        int remainder = (value - 1) % POWEROF;
        value = (value - 1) / POWEROF;
        if(remainder == 0){
            result = 'a' + result;
        }
        else if(remainder == 1){
            result = 'b' + result;
        }
        else if(remainder == 2){
            result = 'c' + result;
        }
        else if(remainder == 3){
            result = 'd' + result;
        }
    }
    return result;
}

int stringToInt(const std::string& str){
    int result = 0;
    for(int i = 0; i < str.length(); i++){
        int encodedValue;
        if(str[i] == 'a'){
            encodedValue = 1;
        }
        else if(str[i] == 'b'){
            encodedValue = 2;
        }
        else if(str[i] == 'c'){
            encodedValue = 3;
        }
        else if(str[i] == 'd'){
            encodedValue = 4;
        }
        result += encodedValue * pow(POWEROF, str.length() - i - 1);
    }
    return result;
}

long changeState(long curState, char inputChar){
    if(curState == INVALID_STATE){
        return INVALID_STATE;
    }
    std::string sequence = intToString(curState) + inputChar;
    if(sequence.length() > 6){
        return INVALID_STATE;
    }
    if(sequence.length() == 6){
        if(!hasAllChars(sequence)){
            return INVALID_STATE;
        }
        sequence.erase(sequence.begin());
    }
    return stringToInt(sequence);
}

mpz_class validStrings(long length) {
    if (length == 0){
        return 1;
    }
    mpz_class memo[length + 2][MAX];
    for(int i = 0; i < length + 2; i++){
        for(int j = 0; j < MAX; j++){
            memo[i][j] = -1;
        }
    }
    for(int i = 1; i <= length + 1; i++){
        for(int state = 0; state < MAX; state++){
            if(i == 1){
                memo[i][state] = (state != INVALID_STATE);
            }
            else{
                memo[i][state] = memo[i - 1][changeState(state, 'a')] +
                                 memo[i - 1][changeState(state, 'b')] +
                                 memo[i - 1][changeState(state, 'c')] +
                                 memo[i - 1][changeState(state, 'd')];
            }
        }
    }
    return memo[length + 1][stringToInt("")];
}

mpz_class binomialCoefficient(int n, int k){
    if(k > n){
        return 0;
    }
    mpz_class result = 1;
    for(int i = 0; i < k; i++){
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

// find number of strings with a in the middle
mpz_class countStringsWithMiddleA(int n){
    if(n % 2 == 0){
        return 0;
    }
    int halfLength = n / 2; // chars before/after 'a'
    mpz_class total = pow(3, halfLength * 2); // remaining chars are b, c, or d
    return total;
}

// find number of strings n that have exactly m amount of 'a'
mpz_class countStringsWithMAs(int n, int m){
    if (m > n || m < 0){
        return 0;
    }
    int otherChars = n - m; // remaining chars (b, c, d)
    mpz_class combinations = binomialCoefficient(n, m); // ways to place 'a'
    mpz_class total = combinations * pow(3, otherChars); // remaining filled with b, c, d
    return total;
}

int main(){
    int option;
    std::cout << "Select option:\n";
    std::cout << "1: Count strings with 'a' as middle symbol\n";
    std::cout << "2: Count strings with exactly m occurrences of 'a'\n";
    std::cin >> option;

    if (option == 1) {
        int n;
        std::cout << "Enter an odd length n: ";
        std::cin >> n;
        if(n % 2 == 0){
            std::cout << "Length must be odd.\n";
        }
        else{
            std::cout << "Number of strings: " << countStringsWithMiddleA(n) << "\n";
        }
    }
    else if(option == 2){
        int n, m;
        std::cout << "Enter length n: ";
        std::cin >> n;
        std::cout << "Enter number of occurrences m: ";
        std::cin >> m;
        std::cout << "Number of strings: " << countStringsWithMAs(n, m) << "\n";
    }
    else{
        std::cout << "Invalid option.\n";
    }

    return 0;
}