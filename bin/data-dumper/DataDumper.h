#pragma once

#include "amqp/include/AMQPBlob.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

class DataDumper {
    private :
        amqp::AMQPBlob m_blob;

    public :
        explicit DataDumper (amqp::CordaBytes &);

        std::string dump();
};

/******************************************************************************/
