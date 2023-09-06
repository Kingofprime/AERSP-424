#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;
int main() {
    
    float m = 3.69;
    cout << "original number :" << m << '\n'; 
    // converitng into binary to string
    string b_string = bitset<32>(*(unsigned int*)&m).to_string();
    
    cout << "original binary: " << b_string << "\n";
    // getting the exponent part
    string exponent = b_string.substr(1,8);
    // flipping it
    string inverted_exponent = bitset<8>(exponent).flip().to_string();
    
    cout << inverted_exponent << '\n';
    // replacing the mantisa part with flipped exponent
    b_string.replace(9,8, inverted_exponent);
    
    cout << "modified binary: " << b_string << "\n";
    // converting string to binary
    unsigned int m_int = bitset<32>(b_string).to_ulong();
    //converting binary to float
    float m_float = *(float*)&m_int;
    
    cout << "modified decimal value: " << m_float;
    
    return 0;
}
