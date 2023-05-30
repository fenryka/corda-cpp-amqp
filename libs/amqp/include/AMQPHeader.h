#pragma once

/******************************************************************************/

#include <array>

/******************************************************************************/

namespace amqp {

    namespace header {

        const int AMQP_V1 = 0;
        const int AMQP_V2 = 1;
        const int AMQP_V3 = 2;

        /**
         *
         */
        const int AMQP_DEFAULT = AMQP_V3;

    }

    /**
     * The 8th byte is used to store weather the stream is compressed or 
     * not
     */
    const std::array<char, 7> AMQP_HEADER_V1 {
        { 'c', 'o', 'r', 'd', 'a', 1, 0 }
    };

    const std::array<char, 7> AMQP_HEADER_DP {
        { 'c', 'o', 'r', 'd', 'a', 1, 0 }
    };

    const std::array<char, 7> AMQP_HEADER_C5 {
        { 'c', 'o', 'r', 'd', 'a', 4, 0 }
    };

    const std::array<std::array<char, 7>, header::AMQP_DEFAULT + 1> AMQP_HEADERS {
        AMQP_HEADER_V1,
        AMQP_HEADER_DP,
        AMQP_HEADER_C5
    };

    const std::array<std::string, header::AMQP_DEFAULT + 1> AMQP_HEADER_DESCS {
        "Corda Versions 1 through 4",
        "Corda 5 DP 1",
        "Corda 5.0 GA"
    };
}

/******************************************************************************/

