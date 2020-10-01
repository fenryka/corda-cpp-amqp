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

            /*
             *
             */
            [[nodiscard]] std::string dumpContents() const;
            [[nodiscard]] std::string dumpSchema (schema::DumpTarget) const;
            [[nodiscard]] std::string dumpData () const;
    };

}
/******************************************************************************/

