#pragma once

/******************************************************************************/

#include <string>
#include <proton/codec.h>

#include "schema/SchemaDumpTargets.h"
#include "CordaBytes.h"

/******************************************************************************/

namespace amqp {

    class AMQPBlob {
        private :
            pn_data_t * m_data;

        public :
            explicit AMQPBlob (CordaBytes &);
            std::string dumpContents() const;

        std::string dumpSchema (schema::DumpTarget) const;
        std::string dumpData () const;
    };

}
/******************************************************************************/

