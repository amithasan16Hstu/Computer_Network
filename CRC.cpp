#include <bits/stdc++.h>
using namespace std;


string convert( string polynomial) {
    int highest = 0;
    vector<int> binary;

   
    stringstream ss(polynomial);
    string term;
    while (getline(ss, term, '+')) {
        term.erase(remove_if(term.begin(), term.end(), ::isspace), term.end());
        int power = 0;
        if (term == "1") {
            power = 0;
        } else if (term == "x") {
            power = 1;
        } else if (term.substr(0, 2) == "x^") {
            power = stoi(term.substr(2));
        }

        highest = max(highest, power);
        if (binary.size() <= power) {
            binary.resize(power + 1, 0);
        }
        binary[power] = 1;
    }

    reverse(binary.begin(), binary.end());
    string binaryString;
    for (int bit : binary) binaryString += (bit ? '1' : '0');
    return binaryString;
}


string xorOperation( string a,  string b) {
    string result = "";
    cout << "XOR between: " << a << " and " << b << endl;
    for (int i = 1; i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    cout << "Result:      " << result << endl;
    return result;
}


string CRC(string data, string generator) {
    int genlength = generator.length();
    string dividend = data.substr(0, genlength);

    cout << "\nPerforming CRC Division:\n";
    while (genlength < data.length()) {
        cout << "Dividend:   " << dividend << endl;
        if (dividend[0] == '1') {
            dividend = xorOperation(generator, dividend) + data[genlength];
        } else {
            dividend = xorOperation(string(genlength, '0'), dividend) + data[genlength];
        }
        genlength++;
        cout << "Updated Dividend: " << dividend << endl;
    }

    cout << "Final Dividend before XOR: " << dividend << endl;
    if (dividend[0] == '1') {
        dividend = xorOperation(generator, dividend);
    } else {
        dividend = xorOperation(string(genlength, '0'), dividend);
    }

    cout << "Final Remainder: " << dividend << endl;
    return dividend;
}

int main() {
    string data, generator;
    int choice;

    cout << "Enter the data to be transmitted: ";
    cin >> data;

    cout << "Choose input method for generator polynomial:\n";
    cout << "1. Binary string (e.g., 10011)\n";
    cout << "2. Polynomial function (e.g., x^4 + x + 1)\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter the generator polynomial as a binary string: ";
        cin >> generator;
    } else if (choice == 2) {
        string polynomialFunction;
        cout << "Enter the generator polynomial in terms of powers (e.g., x^4 + x + 1): ";
        cin.ignore();
        getline(cin, polynomialFunction);
        generator = convert(polynomialFunction);
        cout << "Converted generator polynomial to binary: " << generator << endl;
    } else {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    int generatorLength = generator.length();

    string appendedData = data + string(generatorLength - 1, '0');

   
    string remainder = CRC(appendedData, generator);

   
    string transmittedData = data + remainder;

    cout << "\nTransmitted message: " << transmittedData << endl;

    
    cout << "\nEnter the received data: ";
    string receivedData;
    cin >> receivedData;

    string receiverRemainder = CRC(receivedData, generator);

    if (receiverRemainder.find('1') == string::npos) {
        cout << "\nNo error detected in the received data." << endl;
    } else {
        cout << "\nError detected in the received data." << endl;
    }

    return 0;
}
