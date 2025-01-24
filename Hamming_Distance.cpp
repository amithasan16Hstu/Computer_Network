#include <bits/stdc++.h>
using namespace std;


int Parity( string data, bool evenParity = true) {
    int count_Ones = count(data.begin(), data.end(), '1');
    if (evenParity) {
        return (count_Ones % 2 == 0) ? 0 : 1; 
    } else {
        return (count_Ones % 2 == 0) ? 1 : 0; 
    }
}


int calculateHammingDistance(const string &str1, const string &str2) {
    if (str1.length() != str2.length()) {
        cerr << "Error: Strings must be of equal length to calculate Hamming distance." << endl;
        return -1;
    }
    int distance = 0;
    for (size_t i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) {
            distance++;
        }
    }
    return distance;
}

int main() {
    string data1, data2;
    cout << "Enter the binary data for parity calculation: ";
    cin >> data1;

    int evenParityBit = Parity(data1, true);
    int oddParityBit = Parity(data1, false);

    cout << "Even parity bit: " << evenParityBit << endl;
    cout << "Odd parity bit: " << oddParityBit << endl;


    cout << "\nEnter the first binary string for Hamming distance: ";
    cin >> data1;
    cout << "Enter the second binary string for Hamming distance: ";
    cin >> data2;
    int hammingDistance = calculateHammingDistance(data1, data2);
    if (hammingDistance != -1) {
        cout << "Hamming Distance: " << hammingDistance << endl;
    }

    return 0;
}
