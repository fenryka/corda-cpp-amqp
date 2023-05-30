#include <gtest/gtest.h>
#include <memory>

#include "amqp/include/AMQPHeader.h"

/******************************************************************************/


/******************************************************************************/

TEST (Header, a) { // NOLINT
    EXPECT_FALSE(
            std::find (amqp::AMQP_HEADERS.begin(), amqp::AMQP_HEADERS.end(),
                       amqp::AMQP_HEADER_V1) == amqp::AMQP_HEADERS.end());
}

/******************************************************************************/

TEST (Header, b) { // NOLINT
    EXPECT_FALSE(
            std::find (amqp::AMQP_HEADERS.begin(), amqp::AMQP_HEADERS.end(),
                       amqp::AMQP_HEADER_DP) == amqp::AMQP_HEADERS.end());
}

/******************************************************************************/

TEST (Header, c) { // NOLINT
    EXPECT_FALSE(
            std::find (amqp::AMQP_HEADERS.begin(), amqp::AMQP_HEADERS.end(),
                       amqp::AMQP_HEADER_C5) == amqp::AMQP_HEADERS.end());

}

/******************************************************************************/
