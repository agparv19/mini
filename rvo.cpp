#include <bits/stdc++.h>

class MyObject {
public:
    MyObject() { std::cout << "Constructor called" << std::endl; }
    MyObject(const MyObject& other) { std::cout << "Copy constructor called" << std::endl; }
    void doWork() {std::cout << "doing work inside MyObject" << std::endl;}
    float getRandom() {return std::rand();}
    ~MyObject() { std::cout << "Destructor called" << std::endl; }
};

MyObject e() {
    MyObject obe1;
    MyObject obe2;
    return obe1.getRandom() > obe2.getRandom() ? obe1 : obe2;
}

MyObject f() {
    MyObject obf;
    obf.doWork();
    return obf;
}

void gf(){
    std::cout << "Starting gf()" << std::endl;
    MyObject obg(f()); // Copy constructor will NOT be called!
    std::cout << "Ending gf()" << std::endl;
}

void ge(){
    std::cout << "Starting ge()" << std::endl;
    MyObject obg(e()); // Copy constructor will be called!
    std::cout << "Ending ge()" << std::endl;
}

int main() {
    gf();
    std::cout << std::endl;
    ge();
}