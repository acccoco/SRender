//
// Created by bigso on 2021/5/17.
//


#include <iostream>

template<class T>
class A {
public:
    T acc;
};

template<class T, template<class Elem> class TT>
class B {
public:
    T bili;
    void foo() {
        TT<T> emm{};
        emm.acc = bili;
        std::cout << emm.acc << std::endl;
    }

};

int main() {
    B<int, A> b{};
    b.bili = 123;

    b.foo();

    b.bili = 114514;
    b.foo();

    return 0;
}
