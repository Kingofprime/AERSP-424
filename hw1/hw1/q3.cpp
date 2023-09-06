#include <iostream>
#include <typeinfo>
#include <string>
using namespace std;

template<typename T>
void p(T arg) {
    cout << arg << endl;
}

template<typename T, typename... Args>
void p(T f, Args... args) {
  cout << f << endl;
  p(args...);
}
template<typename T>
void p(T* arg) {
  cout << arg << endl;
}
template<typename T, typename... Args>
void p(T* f, Args... args) {
  cout << f << endl;
  p(args...);
}


int main() 
{
    int x=18;
    double y=2.2;
    char a='a';
    string s ="ankit";
    bool b =true;
    int* xp = &x;
    double* yp =&y;
    char* ap=&a;
    bool* bp=&b;
    string* sp=&s;
  p(x,y,a,s,b,xp,yp,ap,bp,sp);
  return 0;
}
