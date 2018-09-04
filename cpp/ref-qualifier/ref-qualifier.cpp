#include <iostream>
struct S {
    void f() & { std::cout << "lvalue\n"; }
    void f() && { std::cout << "rvalue\n"; }
    // && can bind to const & so this allows calling on a temporary
    // unless we delete it
    // https://herbsutter.com/2008/01/01/gotw-88-a-candidate-for-the-most-important-const/
    void g() const & { std::cout << "lvalue\n"; }
    void g() const && = delete
};

S make_s() {
  return S();
}

int main(){
    S s;
    s.f();           // prints "lvalue"
    make_s().f();    // prints "rvalue"
    s.g();    // prints "lvalue"
    //make_s().g();    // does not compile
}
