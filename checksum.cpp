#include <bits/stdc++.h>
using namespace std;


string onesComplementAddition(string a, string b) {
    int carry = 0;
    string result = "";

    for (int i = a.length() - 1; i >= 0; i--) {
        int bit1 = a[i] - '0';
        int bit2 = b[i] - '0';

        int sum = bit1 + bit2 + carry;
        result = char((sum % 2) + '0') + result;
        carry = sum / 2;
    }

    if (carry == 1) {
        string carryBit = "";
        carryBit += '1';
        result = onesComplementAddition(result, carryBit);
    }

    return result;
}

string calculateChecksum(vector<string> &data) {
    string checksum = data[0];

    for (size_t i = 1; i < data.size(); i++) {
        checksum = onesComplementAddition(checksum, data[i]);
    }

   
    for (char &bit : checksum) {
        bit = (bit == '0') ? '1' : '0';
    }

    return checksum;
}


bool verifyChecksum(vector<string> &data, string receivedChecksum) {
    string sum = receivedChecksum;

    for (const string &block : data) {
        sum = onesComplementAddition(sum, block);
    }

    
    for (char bit : sum) {
        if (bit != '1') {
            return false;
        }
    }

    return true;
}

int main() {
    int blockSize;
    cout << "Enter the block size (number of bits in each block): ";
    cin >> blockSize;

    int numBlocks;
    cout << "Enter the number of blocks: ";
    cin >> numBlocks;

    vector<string> data(numBlocks);
    cout << "Enter the binary data blocks (each " << blockSize << " bits):\n";
    for (int i = 0; i < numBlocks; i++) {
        cin >> data[i];
        if (data[i].length() != blockSize) {
            cout << "Error: Each block must be " << blockSize << " bits long.\n";
            return 1;
        }
    }

    
    string checksum = calculateChecksum(data);
    cout << "\nCalculated Checksum: " << checksum << endl;

 
    cout << "\nTransmitting data with checksum appended...\n";
    vector<string> transmittedData = data;
    transmittedData.push_back(checksum);


    cout << "\nEnter received data blocks (simulate transmission with or without errors):\n";
    vector<string> receivedData(numBlocks + 1);
    for (int i = 0; i <= numBlocks; i++) {
        cin >> receivedData[i];
    }

    
    string receivedChecksum = receivedData.back();
    receivedData.pop_back();

    
    bool isValid = verifyChecksum(receivedData, receivedChecksum);
    if (isValid) {
        cout << "\nChecksum verification successful. No errors detected." << endl;
    } else {
        cout << "\nChecksum verification failed. Errors detected in the received data." << endl;
    }

    return 0;
}