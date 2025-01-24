#include <bits/stdc++.h>
using namespace std;

// Function to calculate single-bit parity for specific positions
int calculateParity(const vector<int> &data, const vector<int> &positions) {
    int count = 0;
    for (int pos : positions) {
        if (pos < data.size() && data[pos] == 1) {
            count++;
        }
    }
    return count % 2; // Return parity (0 for even, 1 for odd)
}

// Function to encode data using Hamming code
vector<int> hammingEncode(const string &data) {
    int m = data.size(); // Original data size
    int r = 0;           // Number of redundant bits
    while ((1 << r) < (m + r + 1)) r++; // Calculate number of redundant bits

    vector<int> encoded(m + r + 1, 0); // Create encoded data (1-based indexing)
    int j = 0;

    // Place data bits in non-parity positions
    for (int i = 1; i < encoded.size(); i++) {
        if ((i & (i - 1)) != 0) { // Not a power of 2
            encoded[i] = data[j++] - '0';
        }
    }

    // Calculate parity bits
    for (int i = 0; i < r; i++) {
        int parityPosition = (1 << i); // 1, 2, 4, ...
        vector<int> positions;
        for (int j = parityPosition; j < encoded.size(); j += (2 * parityPosition)) {
            for (int k = 0; k < parityPosition && (j + k) < encoded.size(); k++) {
                positions.push_back(j + k);
            }
        }
        encoded[parityPosition] = calculateParity(encoded, positions);
    }

    return encoded;
}

// Function to detect and correct errors in Hamming code
int hammingDetectAndCorrect(vector<int> &received) {
    int r = 0;
    while ((1 << r) < received.size()) r++;

    int errorPosition = 0;

    // Check parity bits
    for (int i = 0; i < r; i++) {
        int parityPosition = (1 << i);
        vector<int> positions;
        for (int j = parityPosition; j < received.size(); j += (2 * parityPosition)) {
            for (int k = 0; k < parityPosition && (j + k) < received.size(); k++) {
                positions.push_back(j + k);
            }
        }
        int parity = calculateParity(received, positions);
        if (parity != 0) {
            errorPosition += parityPosition;
        }
    }

    // Correct error if found
    if (errorPosition != 0 && errorPosition < received.size()) {
        cout << "Error detected at position: " << errorPosition << endl;
        received[errorPosition] ^= 1; // Flip the bit
    } else {
        cout << "No error detected." << endl;
    }

    return errorPosition;
}

int main() {
    string data;
    cout << "Enter the binary data to be encoded: ";
    cin >> data;

    // Encode the data using Hamming code
    vector<int> encoded = hammingEncode(data);
    cout << "Encoded data with Hamming code: ";
    for (int i = 1; i < encoded.size(); i++) {
        cout << encoded[i];
    }
    cout << endl;

    // Simulate error
    cout << "Enter the received data (simulate an error by flipping one bit): ";
    vector<int> received(encoded.size());
    for (int i = 1; i < received.size(); i++) {
        cin >> received[i];
    }

    // Detect and correct errors
    int errorPosition = hammingDetectAndCorrect(received);

    // Display corrected data
    if (errorPosition != 0) {
        cout << "Corrected data: ";
        for (int i = 1; i < received.size(); i++) {
            cout << received[i];
        }
        cout << endl;
    }

    return 0;
}
