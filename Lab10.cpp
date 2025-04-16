/*
Program name: calculator
Purpose: convert string to double and add -123.456 to the string
Input: user-input text file
Output: the addition of the string and -123.456
All collaborators: Copliot (GitHub AI), and ChatGPT
Author: Zhang Chen
Creation date: 4/16/25
*/
//Copliot (GitHub AI) were use for error checking and ChatGPT help defined padStrings and subtractUnsigned function
//imported required libraries
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

//declare the namespace to be used
using namespace std;

// Trim leading and trailing spaces
string trim(const string& s) {
    //find the first and last non-space characters
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    //return the substring from start to end
    //if start is not found, return an empty string
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

// Check if a string is a valid double
bool isValidDouble(const string& str) {
    //set index to 0
    int i = 0;
    //get the size of the string
    int n = str.size();
    //if the string is empty, return false
    if (n == 0) return false;
    //if the index is + or -, increment the index
    if (str[i] == '+' || str[i] == '-') i++;
    //set a flag to check if the string has digits
    bool hasDigits = false;
    // while the index is less than the size of the string and the character at the index is a digit, increment the index
    //set the hasDigits flag to true
    while (i < n && isdigit(str[i])) {
        hasDigits = true;
        i++;
    }
    //if the index is "." it will go through  this loop
    if (i < n && str[i] == '.') {
        //incurement the index
        i++;
        //set the hasDigits flag to false
        bool hasDecimalDigit = false;
        //while the index is less than the size of the string and the character at the index is a digit, increment the index
        while (i < n && isdigit(str[i])) {
            hasDecimalDigit = true;
            i++;
        }
        //if the hasDecimalDigit flag is false, return false
        if (!hasDecimalDigit) return false;
    }
    //return the hasDigits flag and the index is equal to the size of the string
    return hasDigits && i == n;
}

// Pad a string with leading zeros
void padStrings(string& a, string& b) {
    //find the index of the first "." in the string
    //if the index is not found, set it to the size of the string
    //set the preLen to the maximum of the two indices
    int dotA = a.find('.') == string::npos ? a.size() : a.find('.');
    int dotB = b.find('.') == string::npos ? b.size() : b.find('.');
    int preLen = max(dotA, dotB);
    //while the index of the first "." in the string is less than the preLen, add a "0" to the string
    while (a.find('.') == string::npos) a += ".0";
    while (b.find('.') == string::npos) b += ".0";

    //set the decA and decB to the size of the string minus the index of the first "." minus 1
    //set the postLen to the maximum of the two indices
    int decA = a.size() - a.find('.') - 1;
    int decB = b.size() - b.find('.') - 1;
    int postLen = max(decA, decB);
    //while int a.find(".") < preLen, add a "0" to the string + a
    //while int b.find(".") < preLen, add a "0" to the string + b   
    while ((int)a.find('.') < preLen) a = "0" + a;
    while ((int)b.find('.') < preLen) b = "0" + b;

    //while int a.size() - a.find(".") - 1 < postLen, add a "0" to the string + a
    //while int b.size() - b.find(".") - 1 < postLen, add a "0" to the string + b
    while ((int)(a.size() - a.find('.') - 1) < postLen) a += "0";
    while ((int)(b.size() - b.find('.') - 1) < postLen) b += "0";
}

// Remove sign and return sign
char stripSign(string& s) {
    //if the first character of the string is + or -, return the sign and remove it from the string
    //if the first character of the string is not + or -, return '+'
    if (s[0] == '+' || s[0] == '-') {
        char sign = s[0];
        s = s.substr(1);
        return sign;
    }
    return '+';
}

// Compare two strings representing unsigned decimal numbers
int compareUnsigned(const string& a, const string& b) {
    // initialize the sa and sb to the strings a and b
    string sa = a, sb = b;
    // pad the strings with leading zeros
    padStrings(sa, sb);
    //retrun the comparison of the two strings
    return sa.compare(sb);
}

// Add two unsigned strings of equal length
string addUnsigned(const string& a, const string& b) {
    string res;
    int carry = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] == '.') {
            res += '.';
            continue;
        }
        int sum = (a[i] - '0') + (b[i] - '0') + carry;
        carry = sum / 10;
        res += (sum % 10 + '0');
    }
    if (carry) res += (carry + '0');
    reverse(res.begin(), res.end());
    return res;
}

// Subtract smaller unsigned number from larger (a must >= b)
string subtractUnsigned(const string& a, const string& b) {
    string res; // Store final result
    int borrow = 0; // Borrow value
    // Process digits from right to left
    for (int i = a.size() - 1; i >= 0; i--) {
        // Preserve decimal point
        if (a[i] == '.') {
            res += '.';
            continue;
        }
        // Calculate digit difference with borrow
        int diff = (a[i] - '0') - (b[i] - '0') - borrow;
        // Handle negative difference by borrowing
        if (diff < 0) {
            diff += 10; // Add base (10 for decimal)
            borrow = 1; // Set borrow for next digit
        } else {
            borrow = 0; // Reset borrow
        }
        res += (diff + '0'); // Append computed digit
    }
    // Reverse to get correct digit order
    reverse(res.begin(), res.end());
    return res;
}

// Clean number string (remove unnecessary zeros)
string cleanNumber(const string& num) {
    int dot = num.find('.');// Find decimal point position
    int start = 0;// Start index for trimming
    // Trim leading zeros in integer part
    while (start < dot - 1 && num[start] == '0') start++;
    int end = num.size() - 1; // End index for trimming
    // Trim trailing zeros in fractional part
    while (end > dot && num[end] == '0') end--;
    if (end == dot) end--; // remove dot if no decimal
    return num.substr(start, end - start + 1);// Return cleaned substring
}

// Add two signed decimal numbers
string addSigned(string a, string b) {
    // Remove and store signs
    char signA = stripSign(a);
    char signB = stripSign(b);
    // Align numbers for processing
    padStrings(a, b);

    string result;// Final result string
    // Handle same signs
    if (signA == signB) {
        result = addUnsigned(a, b);// Add magnitudes
        // Reapply sign if negative
        if (signA == '-') result = '-' + cleanNumber(result);
        // Remove leading zeros if positive
        else result = cleanNumber(result);
        // Handle different signs
    } else {
        // Compare magnitudes
        int cmp = compareUnsigned(a, b);
        if (cmp == 0) {
            result = "0";// Equal magnitudes cancel out
        } else if (cmp > 0) {
            result = subtractUnsigned(a, b);// Subtract smaller from larger
            result = (signA == '-' ? "-" : "") + cleanNumber(result);
        } else {
            result = subtractUnsigned(b, a);// Subtract smaller from larger
            result = (signB == '-' ? "-" : "") + cleanNumber(result);
        }
    }
    //return the final result
    return result;
}

// Main function to read file and process numbers
int main() {
    // create a string to store the filename
    string filename;
    //prompt the user to enter the filename
    cout << "Enter filename: ";
    //read the filename from the user
    cin >> filename;
    //open the file
    ifstream infile(filename);
    //check if the file is open
    if (!infile) {
        //if the file is not open, print an error message and return 1
        cerr << "Error opening file.\n";
        return 1;
    }

    // create a string to store the line
    string line;
    //read the file line by line
    while (getline(infile, line)) {
        //trim the line
        string trimmed = trim(line);
        //check if the trimmed line is a valid double
        if (isValidDouble(trimmed)) {
            //if the trimmed line is a valid double, add it to the string "-123.456" and print the result
            string result = addSigned(trimmed, "-123.456");
            //print the original and the result
            cout << "Original: " << trimmed << ", After addition: " << result << "\n";
        } else {
            //if the trimmed line is not a valid double, print an error message
            cout << "Invalid double: " << trimmed << "\n";
        }
    }
    //close the file
    infile.close();
    //return 0 indicated the porgram successfully executed
    return 0;
}
