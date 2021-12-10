#pragma once

/******************************************************************************/

#include <iosfwd>
#include "amqp/include/AMQPBlob.h"

/******************************************************************************/

namespace amqp {

    class CordaBytes;

}

/******************************************************************************/

class BlobInspector {
    private :
        amqp::AMQPBlob m_blob;

    public :
        explicit BlobInspector (amqp::CordaBytes &);

        std::string dump();
};

/******************************************************************************/
