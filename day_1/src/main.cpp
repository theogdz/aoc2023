#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>

using namespace std;

// Function for Part 1: Find first and last numerical digits
int solvePart1(ifstream& inputFile) {
    inputFile.clear(); // Reset the state of the stream
    inputFile.seekg(0); // Go back to the start of the file
    string line;
    int sum = 0;

    while (getline(inputFile, line)) {
        char firstDigit = '0', lastDigit = '0';

        // Find the first digit
        for (char ch : line) {
            if (isdigit(ch)) {
                firstDigit = ch;
                break;
            }
        }

        // Find the last digit
        for (int i = line.length() - 1; i >= 0; i--) {
            if (isdigit(line[i])) {
                lastDigit = line[i];
                break;
            }
        }

        // Combine and add to sum
        sum += (firstDigit - '0') * 10 + (lastDigit - '0');
    }

    return sum;
}

// Function to map spelled-out digits to their numerical values
int getDigitValue(const string& digitWord) {
    static const map<string, int> digitMap = {
        {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
        {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
    };

    auto it = digitMap.find(digitWord);
    return it != digitMap.end() ? it->second : -1;
}


// Function for Part 2: Find first and last digits (numerical or spelled-out)
int solvePart2(ifstream& inputFile) {
    inputFile.clear(); // Reset the state of the stream
    inputFile.seekg(0); // Go back to the start of the file
    string line;
    int sum = 0;

    while (getline(inputFile, line)) {
        int firstDigit = -1, lastDigit = -1;

        // Scan forwards for the first digit
        for (int i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) {
                firstDigit = line[i] - '0';
                break;
            }
            else if (isalpha(line[i])) {
                string currentWord;
                for (int j = i; j < line.length() && isalpha(line[j]); j++) {
                    currentWord += line[j];
                    int value = getDigitValue(currentWord);
                    if (value != -1) {
                        firstDigit = value;
                        break;
                    }
                }
                if (firstDigit != -1) {
                    break;
                }
            }
        }

        // Scan backwards for the last digit
        for (int i = line.length() - 1; i >= 0; i--) {
            if (isdigit(line[i])) {
                lastDigit = line[i] - '0';
                break;
            }
            else if (isalpha(line[i])) {
                string currentWord;
                for (int j = i; j >= 0 && isalpha(line[j]); j--) {
                    currentWord = line[j] + currentWord;
                    int value = getDigitValue(currentWord);
                    if (value != -1) {
                        lastDigit = value;
                        break;
                    }
                }
                if (lastDigit != -1){
                    break;
                }
            }
        }
        sum += firstDigit * 10 + lastDigit;
    }
    
    return sum;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    int sumPart1 = solvePart1(inputFile);
    cout << "Sum of calibration values (Part 1): " << sumPart1 << endl;

    int sumPart2 = solvePart2(inputFile);
    cout << "Sum of calibration values (Part 2): " << sumPart2 << endl;

    inputFile.close();
    return 0;
}
