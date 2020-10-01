#pragma once

/******************************************************************************/

#include "string"
#include <fstream>
#include "AMQPSectionId.h"

/******************************************************************************/

namespace amqp {

    class CordaBytes {
        private :
            amqp::amqp_section_id_t m_encoding;
            size_t m_size;
            char * m_blob;

    public :
        explicit CordaBytes (const std::string &);

        ~CordaBytes() {
            delete[] m_blob;
        }

        [[nodiscard]] const decltype (m_encoding) &encoding() const {
            return m_encoding;
        }

        [[nodiscard]] decltype (m_size) size() const { return m_size; }

        [[nodiscard]] const char * const bytes() const { return m_blob; }
    };

}

/******************************************************************************/
