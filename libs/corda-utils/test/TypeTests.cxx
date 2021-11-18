#include <gtest/gtest.h>

#include "../include/types.h"

/******************************************************************************/

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
            A ** m_b;
            const A ** m_c;
            const B & m_d;
            B & m_e;
    };
}

namespace a::b {
    class C {};
}

/******************************************************************************/

TEST (typeName, test1) {
    int status;

    EXPECT_EQ ("A", std::string (typeName<A>(status)));
    EXPECT_EQ ("A", std::string (typeName<decltype (A::m_b)>(status)));
    EXPECT_EQ ("net::B", std::string (typeName<net::B>(status)));

    EXPECT_EQ ("A", std::string (typeName<decltype(net::B::m_a)>(status)));
    EXPECT_EQ ("A", std::string (typeName<decltype(net::B::m_b)>(status)));
    EXPECT_EQ ("A", std::string (typeName<decltype(net::B::m_c)>(status)));
    EXPECT_EQ ("net::B", std::string (typeName<decltype(net::B::m_d)>(status)));
    EXPECT_EQ ("net::B", std::string (typeName<decltype(net::B::m_e)>(status)));
}

/******************************************************************************/

TEST (typeName, javaTypeName) {
    EXPECT_EQ ("A", javaTypeName<A>());
    EXPECT_EQ ("net.B", javaTypeName<net::B>());
    EXPECT_EQ ("a.b.C", javaTypeName<a::b::C>());
}

/******************************************************************************/

TEST (typeName, vectors) {
    typedef std::vector<int> V1;
    typedef std::vector<a::b::C> V2;

    EXPECT_EQ ("java.util.List<int>", javaTypeName<V1>());
    EXPECT_EQ ("java.util.List<a.b.C>", javaTypeName<V2>());
}

/******************************************************************************/

TEST (typeName, maps) {
    typedef std::map<int, int> V1;
    typedef std::map<int, std::vector<std::string>> V2;

    EXPECT_EQ ("java.util.Map<int,int>", javaTypeName<V1>());
    EXPECT_EQ ("java.util.Map<int,java.util.List<string>>", javaTypeName<V2>());
}

/******************************************************************************/

namespace {

    class Anon {
    public :
        class Anon2 {};
    };

}

TEST (typeName, anonNamespace) {
    EXPECT_EQ ("Anon", javaTypeName<Anon>());
    EXPECT_EQ ("Anon.Anon2", javaTypeName<Anon::Anon2>());
}

/******************************************************************************/
