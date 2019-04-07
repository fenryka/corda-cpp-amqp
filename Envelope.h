#pragma once

/******************************************************************************/

#include "AMQPDescribed.h"

/******************************************************************************
 *
 * Forward declarations
 *
 ******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp {


    class Envelope : public AMQPDescribed {
        public :
            const static uint8_t BLOB_IDX = 0;
            const static uint8_t SCHEMA_IDX = 1;
            const static uint8_t TRANSFORMS_SCHEMA_IDX = 2;

        public :
            Envelope ();

    };

}

/******************************************************************************/

