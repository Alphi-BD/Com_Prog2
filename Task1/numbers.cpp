#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


std::string dec_to_binary(int dec) {
    if (dec == 0) return  "0";
    std::string result = "";
    while (dec > 0) {
        result.push_back((dec % 2) + '0');
        dec /= 2;
    }
    std::reverse(result.begin(), result.end());
    return result;
}


int reverse_number(int n) {
    int rev = 0;
    while (n > 0) {
        rev = rev * 10 + (n % 10);
        n /= 10;
    }
    return rev;
     }


int reverse_plus(int first, int second) {
    int rev1 = reverse_number(first);
    int rev2 = reverse_number(second);
    int sum = rev1 + rev2;
    return reverse_number(sum);
}


std::string factorial(long n)
     {
    if (n < 0) return "undefined";
    if (n == 0 || n == 1) return "1";


    std::vector<int> result;
    result.push_back(1);

    for (int x = 2; x <= n; x++)
     {
        int carry = 0;
        for (size_t i = 0; i < result.size(); i++) {
            long long prod = (long long)result[i] * x + carry;
            result[i] = prod % 10;
            carry = prod / 10;
        }
        while (carry)
           {
            result.push_back(carry % 10);
            carry /= 10;
        }
        }

    std::string fact = "";
    for (auto it = result.rbegin(); it != result.rend(); ++it) {
        fact.push_back(*it + '0');
    }
    return fact;
   }


int main(int argc, char const *argv[]) {
    char *end;
    long which = 0;
    which = strtol(argv[1], &end, 10);
    switch (which) {
        case 1: {
            long dec = strtol(argv[2], &end, 10);
            std::cout << dec << " in binary = " << dec_to_binary(dec) << std::endl;
            break;
        }
        case 2: {
            long first = strtol(argv[2], &end, 10);
            long second = strtol(argv[3], &end, 10);
            std::cout << "reverse_plus(first, second) = " << reverse_plus(first, second) << std::endl;
            break;
        }
        case 3: {
            long limit = strtol(argv[2], &end, 10);
            std::cout << limit << "! = " << factorial(limit) << std::endl;
            break;
        }
        default: {
            std::cout << "invalid option: " << which;
            break;
        }
    }
    return 0;
}
