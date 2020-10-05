#pragma once

/******************************************************************************/

#include <string>

#include "schema/SchemaDumpTargets.h"

/******************************************************************************/

struct pn_data_t;

namespace amqp {

    class CordaBytes;

}

/******************************************************************************/

namespace amqp {

    class AMQPBlob {
        private :
            pn_data_t * m_data;

        protected :
            /*
             * Want [[ModifiableAMQPBlob]] to be able to construct
             * empty instances but in general don't want that functionality
             * exposed
             */
            AMQPBlob();

        public :
            explicit AMQPBlob (CordaBytes &);
            explicit AMQPBlob (pn_data_t *);

            [[nodiscard]] std::string dumpContents() const;
            [[nodiscard]] std::string dumpSchema (schema::DumpTarget) const;
            [[nodiscard]] std::string dumpData () const;

            pn_data_t * data() const;
    };

}

/******************************************************************************/

