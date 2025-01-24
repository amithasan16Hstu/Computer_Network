#include <bits/stdc++.h>
using namespace std;

string bitStuffing( string data) {
    string stuffedData;
    int count = 0;

    for (char bit : data) {
        stuffedData += bit;
        if (bit == '1') {
            count++;
            if (count == 5) {
                stuffedData += '0'; 
                count = 0;
            }
        } else {
            count = 0;
        }
    }
    return stuffedData;
}


string bitUnstuffing(string stuffedData) {
    string unstuffedData;
    int count = 0;

    for (size_t i = 0; i < stuffedData.length(); i++) {
        char bit = stuffedData[i];
        unstuffedData += bit;
        if (bit == '1') {
            count++;
            if (count == 5 && i + 1 < stuffedData.length() && stuffedData[i + 1] == '0') {
                i++; 
                count = 0;
            }
        } else {
            count = 0;
        }
    }
    return unstuffedData;
}

string byteStuffing(string data, char flag, char escape) {
    string stuffedData;

    for (char byte : data) {
        if (byte == flag || byte == escape) {
            stuffedData += escape; 
        }
        stuffedData += byte;
    }
    return stuffedData;
}

string byteUnstuffing( string stuffedData, char flag, char escape) {
    string unstuffedData;
    bool escapeNext = false;

    for (char byte : stuffedData) {
        if (escapeNext) {
            unstuffedData += byte;
            escapeNext = false;
        } else if (byte == escape) {
            escapeNext = true;
        } else {
            unstuffedData += byte;
        }
    }
    return unstuffedData;
}

int main() {
    string binaryData;
    cout << "Enter binary data for stuffing: ";
    cin >> binaryData;

   
    string bitStuffed = bitStuffing(binaryData);
    cout << "\nBit Stuffed Data: " << bitStuffed << endl;

    string bitUnstuffed = bitUnstuffing(bitStuffed);
    cout << "Bit Unstuffed Data: " << bitUnstuffed << endl;

   
    string charData;
    char flag = 'F'; 
    char escape = 'E'; 

    cout << "\nEnter character data for byte stuffing: ";
    cin >> charData;

    string byteStuffed = byteStuffing(charData, flag, escape);
    cout << "\nByte Stuffed Data: " << byteStuffed << endl;

    string byteUnstuffed = byteUnstuffing(byteStuffed, flag, escape);
    cout << "Byte Unstuffed Data: " << byteUnstuffed << endl;

    return 0;
}

// Enter binary data for stuffing: 1111101111110111
//Enter character data for byte stuffing: ABCDEFFEF

