#include <iostream>
#include <string>
#include <cmath>
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

int main(){
    int testCases[] = {6, 56, 287, 299};
    int length;
    for (int testLength : testCases){
        std::cout << "Number of valid strings of length " << testLength << ": " << validStrings(testLength) << std::endl;
    }

    std::cout << "Enter the length of the strings (0 to 300). n = ";
    std::cin >> length;
    if(length >= 0 && length <= 300){
        std::cout << "Number of valid strings of length " << length << ": " << validStrings(length) << std::endl;
    }
    else{
        std::cerr << "Error: Invalid input. Please provide a length between 0 to 300." << std::endl;
        return 1;
    }
    return 0;
}