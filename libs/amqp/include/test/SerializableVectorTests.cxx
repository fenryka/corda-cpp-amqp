#pragma clang diagnostic push
#pragma clang diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>
#include <string>

#include "corda-utils/include/types.h"

#include "../serializable/SerializableVector.h"

/******************************************************************************/

template<> const std::string amqp::serializable::Fingerprint<std::vector<int>>::val = "IntVector";

/******************************************************************************/

TEST (serializableVector, test1) {
    amqp::serializable::SerializableVector<int> vi;

    ASSERT_EQ(0, vi.size());
    ASSERT_EQ("java.util.List<int>", vi.name());
    ASSERT_EQ("things123", vi.fingerprint());

   vi.push_back(1);

    ASSERT_EQ (1, vi.size());
}

/******************************************************************************/

TEST (serializableVector, test2) {
    std::vector<int> a {1, 2, 3};
    amqp::serializable::SerializableVector<int> vi {
        std::move (a)
    };

    ASSERT_EQ(3, vi.size());
    ASSERT_EQ("java.util.List<int>", vi.name());
    ASSERT_EQ("things123", vi.fingerprint());

    vi.push_back(1);

    ASSERT_EQ (4, vi.size());
}

/******************************************************************************/

TEST (serializableVector, test3) {
    amqp::serializable::SerializableVector<int> vi {
        { 1, 2, 3, 4, 5, 6 }
    };

    ASSERT_EQ(6, vi.size());
    ASSERT_EQ("java.util.List<int>", vi.name());
    ASSERT_EQ("things123", vi.fingerprint());

    vi.push_back(1);

    ASSERT_EQ (7, vi.size());
}

/******************************************************************************/

TEST (serializableVector, autoName) {
    amqp::serializable::SerializableVector<int> vi;

    ASSERT_EQ(0, vi.size());
    ASSERT_EQ("java.util.List<int>", vi.name());
    ASSERT_EQ("things123", vi.fingerprint());

    vi.push_back(1);

    ASSERT_EQ (1, vi.size());
}

/******************************************************************************/

TEST (serializableVector, javaTypeName) {
    typedef amqp::serializable::SerializableVector<std::string> T;

    [[maybe_unused]] T * l; // It isn't unused byt clang seems to not see it
    T   l2;

    std::cout << typeName<T>() << std::endl;
    std::cout << typeName<decltype(l2)>() << std::endl;
    std::cout << typeName<decltype(&l2)>() << std::endl;

    ASSERT_EQ("java.util.List<String>", javaTypeName<T>());
    ASSERT_EQ("java.util.List<String>", javaTypeName<std::remove_pointer_t<decltype (l)>>());
    ASSERT_EQ("java.util.List<String>", javaTypeName<decltype (l2)>());
    ASSERT_EQ("java.util.List<String>", javaTypeName<std::remove_pointer_t<decltype (&l2)>>());
}

/******************************************************************************/

TEST (serializableVector, javaTypeName2) {
    struct Test {
        amqp::serializable::SerializableVector<std::string> m_list;

        Test() : m_list() {}

        void fun() {
            ASSERT_EQ("java.util.List<String>", javaTypeName<decltype (m_list)>());
            ASSERT_EQ("java.util.List<String>", javaTypeName<std::remove_pointer_t<decltype (&m_list)>>());
        }
    };

    Test t;
    t.fun();
}

/******************************************************************************/

TEST (serializableVector, javaTypeName3) {
    class Test {
        private :
            amqp::serializable::SerializableVector<std::string> m_list;
        public :

            Test() : m_list () {}

            void fun() {
                std::cout << javaTypeName<decltype (m_list)>() << std::endl;
                std::cout << javaTypeName<std::remove_pointer_t<decltype (&m_list)>>() << std::endl;

                ASSERT_EQ("java.util.List<String>", javaTypeName<decltype (m_list)>());
                ASSERT_EQ("java.util.List<String>", javaTypeName<std::remove_pointer_t<decltype (&m_list)>>());
            }
    };

    Test t;
    t.fun();
}

/******************************************************************************/

#pragma clang diagnostic pop

/******************************************************************************/
