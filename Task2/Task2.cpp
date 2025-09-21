#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

string units[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
string tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
string hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
string thousands[] = {"", "M", "MM", "MMM"};

string arabicToRoman(int num) {
    if (num <= 0 || num > 3999) return "";

    string result = "";
    result += thousands[num / 1000];
    result += hundreds[(num % 1000) / 100];
    result += tens[(num % 100) / 10];
    result += units[num % 10];

    return result;
}

string toUpper(const string& str) {
    string result = str;
    for (int i = 0; i < result.length(); i++) {
        result[i] = toupper(result[i]);
    }
    return result;
}

int getRomanDigitValue(const string& str) {
    for (int i = 3; i >= 1; i--) {
        if (str == thousands[i]) return i * 1000;
    }
    for (int i = 9; i >= 1; i--) {
        if (str == hundreds[i]) return i * 100;
    }
    for (int i = 9; i >= 1; i--) {
        if (str == tens[i]) return i * 10;
    }
    for (int i = 9; i >= 1; i--) {
        if (str == units[i]) return i;
    }
    return 0;
}

int romanToArabic(const string& roman) {
    if (roman.empty()) return 0;

    string upper = toUpper(roman);
    int result = 0;
    int pos = 0;

    for (int i = 3; i >= 1 && pos < upper.length(); i--) {
        if (upper.substr(pos, thousands[i].length()) == thousands[i]) {
            result += i * 1000;
            pos += thousands[i].length();
            break;
        }
    }

    for (int i = 9; i >= 1 && pos < upper.length(); i--) {
        if (upper.substr(pos, hundreds[i].length()) == hundreds[i]) {
            result += i * 100;
            pos += hundreds[i].length();
            break;
        }
    }

    for (int i = 9; i >= 1 && pos < upper.length(); i--) {
        if (upper.substr(pos, tens[i].length()) == tens[i]) {
            result += i * 10;
            pos += tens[i].length();
            break;
        }
    }

    for (int i = 9; i >= 1 && pos < upper.length(); i--) {
        if (upper.substr(pos, units[i].length()) == units[i]) {
            result += i;
            pos += units[i].length();
            break;
        }
    }

    return result;
}

bool isRomanChar(char c) {
    c = toupper(c);
    return c == 'I' || c == 'V' || c == 'X' || c == 'L' ||
           c == 'C' || c == 'D' || c == 'M';
}

pair<int, int> extractRomanNumber(const string& str, int start) {
    string upper = toUpper(str);
    int value = 0;
    int pos = start;

    for (int i = 3; i >= 1 && pos < upper.length(); i--) {
        if (pos + thousands[i].length() <= upper.length() &&
            upper.substr(pos, thousands[i].length()) == thousands[i]) {
            value += i * 1000;
            pos += thousands[i].length();
            break;
        }
    }

    for (int i = 9; i >= 1 && pos < upper.length(); i--) {
        if (pos + hundreds[i].length() <= upper.length() &&
            upper.substr(pos, hundreds[i].length()) == hundreds[i]) {
            value += i * 100;
            pos += hundreds[i].length();
            break;
        }
    }

    for (int i = 9; i >= 1 && pos < upper.length(); i--) {
        if (pos + tens[i].length() <= upper.length() &&
            upper.substr(pos, tens[i].length()) == tens[i]) {
            value += i * 10;
            pos += tens[i].length();
            break;
        }
    }

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

int plusMode(const string& input) {
    int total = 0;
    int i = 0;

    while (i < input.length()) {
        if (isRomanChar(input[i])) {
            pair<int, int> result = extractRomanNumber(input, i);
            if (result.second > i) {
                total += result.first;
                i = result.second;
            } else {
                i++;
            }
        } else {
            i++;
        }
    }

    return total;
}

int main(int argc, char* argv[]) {
    bool plusModeEnabled = false;

    if (argc > 1 && string(argv[1]) == "-plus") {
        plusModeEnabled = true;
    }

    string input;
    while (getline(cin, input)) {
        if (input.empty()) {
            cout << "0" << endl;
            continue;
        }

        if (plusModeEnabled) {
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
            } else {
                cout << plusMode(input) << endl;
            }
        } else {
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
            } else if (isRomanChar(input[0])) {
                int value = romanToArabic(input);
                cout << value << endl;
            } else {
                cout << "0" << endl;
            }
        }
    }

    return 0;
}