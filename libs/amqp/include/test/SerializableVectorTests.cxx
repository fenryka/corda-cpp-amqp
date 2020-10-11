#include <gtest/gtest.h>

#include "../serializable/SerializableVector.h"

/******************************************************************************/

TEST (serializableVector, test1) {
    amqp::serializable::SerializableVector<int> vi {
        "list<int>",
        "things123"};

    ASSERT_EQ(0, vi.size());
    ASSERT_EQ("list<int>", vi.name());
    ASSERT_EQ("things123", vi.fingerprint());

   vi.push_back(1);

    ASSERT_EQ (1, vi.size());
}

/******************************************************************************/

TEST (serializableVector, test2) {
    std::vector<int> a {1, 2, 3};
    amqp::serializable::SerializableVector<int> vi {
        "list<int>",
        "things123",
        std::move (a)
    };

    ASSERT_EQ(3, vi.size());
    ASSERT_EQ("list<int>", vi.name());
    ASSERT_EQ("things123", vi.fingerprint());

    vi.push_back(1);

    ASSERT_EQ (4, vi.size());
}

/******************************************************************************/

TEST (serializableVector, test3) {
    amqp::serializable::SerializableVector<int> vi {
        "list<int>",
        "things123",
        { 1, 2, 3, 4, 5, 6 }
    };

    ASSERT_EQ(6, vi.size());
    ASSERT_EQ("list<int>", vi.name());
    ASSERT_EQ("things123", vi.fingerprint());

    vi.push_back(1);

    ASSERT_EQ (7, vi.size());
}

/******************************************************************************/

