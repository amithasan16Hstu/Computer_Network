#include <bits/stdc++.h>
using namespace std;


int Parity(string data, bool evenParity = true) {
    int countOnes = count(data.begin(), data.end(), '1');
    if (evenParity) {
        return (countOnes % 2 == 0) ? 0 : 1; 
    } else {
        return (countOnes % 2 == 0) ? 1 : 0; 
    }
}


string encodeWithParity(string data, bool evenParity = true) {
    int parityBit = Parity(data, evenParity);
    return data + to_string(parityBit);
}


bool checkParity(string receivedData, bool evenParity = true) {
    int countOnes = count(receivedData.begin(), receivedData.end(), '1');
    if (evenParity) {
        return (countOnes % 2 == 0); 
    } else {
        return (countOnes % 2 != 0); 
    }
}


int main() {
    string data;
    bool evenParity;

    
    cout << "Enter the binary data to be transmitted: ";
    cin >> data;
    cout << "Use even parity? (1 for Yes, 0 for No): ";
    cin >> evenParity;

    
    string encodedData = encodeWithParity(data, evenParity);
    cout << "Encoded data with parity bit: " << encodedData << endl;

    
    cout << "Enter the received data: ";
    string receivedData;
    cin >> receivedData;

    
    if (checkParity(receivedData, evenParity)) {
        cout << "No error detected in the received data." << endl;
    } else {
        cout << "Error detected in the received data." << endl;
        if (abs((int)receivedData.size() - (int)data.size()) > 1 || count(receivedData.begin(), receivedData.end(), '1') > 1) {
            cout << "Parity can only detect single-bit errors." << endl;
        }
    }

    return 0;
}
