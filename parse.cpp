#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    ifstream in("test.txt");
    ofstream out("test1.txt");
    string s;
    while(getline(in,s)) {
    
    stringstream ss;
    ss << s;
    double n1,n2,n3;
    ss >> n1 >> n2 >> n3;
    string s1, s2, s3;
    s1 = to_string(n1);
    s2 = to_string(n2);
    s3 = to_string(n3);
    s1 = "("+s1+")";
    s2 = "("+s2+")";
    s3 = "("+s3+")";
    out << s1 << " " << s2 << " " << s3 << "\n";
    }
}