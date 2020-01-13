#pragma once

#include "amqp/include/AMQPBlob.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

class SchemaDumper {
    private :
        amqp::AMQPBlob m_blob;

    public :
        explicit SchemaDumper (amqp::CordaBytes &);

        std::string dump (amqp::schema::DumpTarget);
};

/******************************************************************************/
