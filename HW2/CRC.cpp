#include <bits/stdc++.h>
#include <ctime> // Add this header for time function

using namespace std;

// Function to flip a bit
char bitFlip(char x) {
    if (x == '0') {
        return '1';
    }
    return '0';
}

// Function to generate a random bit message
string Msg(int k) {
    string msg = "";
    while(k--) {
        msg += (rand() % 2 == 0) ? '0' : '1';
    }
    return msg;
}

// Function to perform XOR operation
string XOR(const string& a, const string& b) {
    string result = "";
    for (size_t i = 0; i < a.length(); ++i) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// Function to perform division
string division(const string& a, const string& b) {
    int p = b.length();
    int m = a.length();

    string rem = a.substr(0, p - 1);
    for (int i = 0; i < m - p + 1; ++i) {
        rem += a[i + p - 1];
        if (rem[0] == '1') {
            rem = XOR(rem, b);
            rem = rem.substr(1);
        } else {
            rem = rem.substr(1);
        }
    }
    return rem;
}

// Function to compute CRC frame
string compFrame(const string& msg, const string& P) {
    string dividend = msg + string(P.length() - 1, '0');
    return msg + division(dividend, P);
}

// Function to insert errors in the frame
void error(const string& frame, pair <string,string>& result) {
    string err = "";
    string rec = "";
    for (char c : frame) {
        if (rand() % 16 == 0) { 
            rec += bitFlip(c);
            err += '1';
        } else {
            rec += c;
            err += '0';
        }
    }
    result = make_pair(rec, err);
} 

// Function to verify CRC
string status(const string& rec, const string& P) {
    string remExp(P.length() - 1, '0');

    if (remExp == division(rec, P)) {
        return "Accept";
    }
    return "Reject";
}

int main() {
    srand(time(0)); // Seed for random number generation

    // string P = "101001";
    // string P = "101010";

    string P = "110101";
    int k = 10;
    string msg = Msg(k);

    string frame = compFrame(msg, P);
    pair<string, string> result;
    error(frame, result);
    string rec = result.first;
    string err = result.second;
    string stat = status(rec, P);
    
    cout << "Message: " << msg << ", Pattern:" << P << endl;
    cout << "15 bit Trasmission Frame T: " << frame << endl;
    cout << "Introduced Error: " << err << endl;
    cout << "Received Frame after Introducing Error: " << rec << endl;
    cout << "Received Frame Status: " << stat << endl;

    return 0;
}