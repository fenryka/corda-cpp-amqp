#pragma once

/******************************************************************************/

#include "AMQPHeader.h"

/******************************************************************************/

namespace amqp {

    class AMQPConfig {
        public :
            bool ignoreHeader = false;
            int header = header::AMQP_DEFAULT;
    };

}

/******************************************************************************/

