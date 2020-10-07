#include <gtest/gtest.h>

#include "../include/types.h"

class A {
    public :
    int m_a;
    A * m_b;
    const A & m_c;
};

namespace net {
    class B {
        public :
            const A & m_a;
    };
}

TEST (Map, name1) {
    int status;
    std::cout << typeName<A>(status) << std::endl;
    std::cout << typeName<decltype(A::m_b)>(status) << std::endl;
    std::cout << typeName<net::B>(status) << std::endl;
    std::cout << typeName<decltype(net::B::m_a)>(status) << std::endl;
}
