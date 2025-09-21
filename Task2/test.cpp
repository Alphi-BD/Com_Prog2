#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

// Arrays storing Roman numeral representations for units, tens, hundreds, and thousands
// The index of the array corresponds to the Arabic number
string units[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
string tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
string hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
string thousands[] = {"", "M", "MM", "MMM"};

// Converts an Arabic number (integer) to its Roman numeral representation
string arabicToRoman(int num) {
    if (num <= 0 || num > 3999) return ""; // Roman numerals are valid only from 1 to 3999

    string result = "";
    // Extract thousands, hundreds, tens, and units separately
    result += thousands[num / 1000];              // Thousands place
    result += hundreds[(num % 1000) / 100];       // Hundreds place
    result += tens[(num % 100) / 10];             // Tens place
    result += units[num % 10];                    // Units place

    return result; // Final Roman numeral string
}

// Converts a string to uppercase (to handle both lowercase and uppercase Roman numerals)
string toUpper(const string& str) {
    string result = str;
    for (int i = 0; i < result.length(); i++) {
        result[i] = toupper(result[i]);
    }
    return result;
}

// Returns the Arabic value of a single Roman numeral "digit" (I, IV, V, IX, etc.)
int getRomanDigitValue(const string& str) {
    // Check thousands
    for (int i = 3; i >= 1; i--) {
        if (str == thousands[i]) return i * 1000;
    }
    // Check hundreds
    for (int i = 9; i >= 1; i--) {
        if (str == hundreds[i]) return i * 100;
    }
    // Check tens
    for (int i = 9; i >= 1; i--) {
        if (str == tens[i]) return i * 10;
    }
    // Check units
    for (int i = 9; i >= 1; i--) {
        if (str == units[i]) return i;
    }
    return 0; // Not a valid Roman digit
}

// Converts a Roman numeral string into its Arabic (integer) equivalent
int romanToArabic(const string& roman) {
    if (roman.empty()) return 0;

    string upper = toUpper(roman); // Convert to uppercase for consistency
    int result = 0;
    int pos = 0; // Current position in the string

    // Match thousands
    for (int i = 3; i >= 1 && pos < upper.length(); i--) {
        if (upper.substr(pos, thousands[i].length()) == thousands[i]) {
            result += i * 1000;
            pos += thousands[i].length();
            break;
        }
    }
    // Match hundreds
    for (int i = 9; i >= 1 && pos < upper.length(); i--) {
        if (upper.substr(pos, hundreds[i].length()) == hundreds[i]) {
            result += i * 100;
            pos += hundreds[i].length();
            break;
        }
    }
    // Match tens
    for (int i = 9; i >= 1 && pos < upper.length(); i--) {
        if (upper.substr(pos, tens[i].length()) == tens[i]) {
            result += i * 10;
            pos += tens[i].length();
            break;
        }
    }
    // Match units
    for (int i = 9; i >= 1 && pos < upper.length(); i--) {
        if (upper.substr(pos, units[i].length()) == units[i]) {
            result += i;
            pos += units[i].length();
            break;
        }
    }

    return result;
}

// Checks whether a character is a valid Roman numeral character
bool isRomanChar(char c) {
    c = toupper(c);
    return c == 'I' || c == 'V' || c == 'X' || c == 'L' ||
           c == 'C' || c == 'D' || c == 'M';
}

// Extracts a Roman numeral substring starting from a given position
// Returns its value and the new position after extraction
pair<int, int> extractRomanNumber(const string& str, int start) {
    string upper = toUpper(str);
    int value = 0;
    int pos = start;

    // Check thousands
    for (int i = 3; i >= 1 && pos < upper.length(); i--) {
        if (pos + thousands[i].length() <= upper.length() &&
            upper.substr(pos, thousands[i].length()) == thousands[i]) {
            value += i * 1000;
            pos += thousands[i].length();
            break;
        }
    }
    // Check hundreds
    for (int i = 9; i >= 1 && pos < upper.length(); i--) {
        if (pos + hundreds[i].length() <= upper.length() &&
            upper.substr(pos, hundreds[i].length()) == hundreds[i]) {
            value += i * 100;
            pos += hundreds[i].length();
            break;
        }
    }
    // Check tens
    for (int i = 9; i >= 1 && pos < upper.length(); i--) {
        if (pos + tens[i].length() <= upper.length() &&
            upper.substr(pos, tens[i].length()) == tens[i]) {
            value += i * 10;
            pos += tens[i].length();
            break;
        }
    }
    // Check units
    for (int i = 9; i >= 1 && pos < upper.length(); i--) {
        if (pos + units[i].length() <= upper.length() &&
            upper.substr(pos, units[i].length()) == units[i]) {
            value += i;
            pos += units[i].length();
            break;
        }
    }

    return make_pair(value, pos);
}

// "Plus mode": scans an input string, extracts all Roman numerals,
// converts them to Arabic numbers, and sums them up
int plusMode(const string& input) {
    int total = 0;
    int i = 0;

    while (i < input.length()) {
        if (isRomanChar(input[i])) {
            pair<int, int> result = extractRomanNumber(input, i);
            if (result.second > i) {       // Found a valid Roman numeral
                total += result.first;     // Add its value
                i = result.second;         // Move to the end of the matched numeral
            } else {
                i++; // Skip invalid Roman character
            }
        } else {
            i++; // Skip non-Roman characters
        }
    }

    return total;
}

int main(int argc, char* argv[]) {
    bool plusModeEnabled = false;

    // Check if program was run with "-plus" option
    if (argc > 1 && string(argv[1]) == "-plus") {
        plusModeEnabled = true;
    }

    string input;
    // Read input line by line until EOF
    while (getline(cin, input)) {
        if (input.empty()) { // Empty line gives output "0"
            cout << "0" << endl;
            continue;
        }

        if (plusModeEnabled) {
            // If input starts with a digit, treat it as an Arabic number
            if (isdigit(input[0])) {
                int num = 0;
                int i = 0;
                while (i < input.length() && isdigit(input[i])) {
                    num = num * 10 + (input[i] - '0');
                    i++;
                }
                string roman = arabicToRoman(num);
                if (roman.empty()) {
                    cout << "0" << endl;
                } else {
                    cout << roman << endl;
                }
            } else { // Otherwise, extract and sum all Roman numerals in input
                cout << plusMode(input) << endl;
            }
        } else { // Normal mode: only single conversions
            if (isdigit(input[0])) { // Arabic to Roman
                int num = 0;
                int i = 0;
                while (i < input.length() && isdigit(input[i])) {
                    num = num * 10 + (input[i] - '0');
                    i++;
                }
                string roman = arabicToRoman(num);
                if (roman.empty()) {
                    cout << "0" << endl;
                } else {
                    cout << roman << endl;
                }
            } else if (isRomanChar(input[0])) { // Roman to Arabic
                int value = romanToArabic(input);
                cout << value << endl;
            } else { // Invalid input
                cout << "0" << endl;
            }
        }
    }

    return 0;
}
