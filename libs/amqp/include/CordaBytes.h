#pragma once

/******************************************************************************/

#include <string>
#include <fstream>

#include "corda-utils/include/types.h"
#include "AMQPSectionId.h"
#include "amqp/include/AMQPConfig.h"

/******************************************************************************/

namespace amqp {

    class AMQPBlob;

}

/******************************************************************************/

namespace amqp {

    class CordaBytes {
        private :
            amqp::amqp_section_id_t m_encoding;
            size_t            m_size{};
            char            * m_blob{};
            uPtr<AMQPConfig>  m_config;
            int               m_version;

        public :
            explicit CordaBytes (const std::string &, uPtr<AMQPConfig>);
            explicit CordaBytes (const AMQPBlob &, uPtr<AMQPConfig>);

            ~CordaBytes() {
                delete[] m_blob;
            }

            [[nodiscard]] const decltype (m_encoding) &encoding() const {
                return m_encoding;
            }

            [[nodiscard]] decltype (m_size) size() const { return m_size; }

            [[nodiscard]] const char * bytes() const { return m_blob; }

            [[nodiscard]]  int version() const { return m_version; }

            void toFile (const std::string &) const;
    };

}

/******************************************************************************/
