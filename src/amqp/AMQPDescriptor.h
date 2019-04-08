#pragma once

/******************************************************************************/

#include <map>
#include <string>
#include <iostream>

/******************************************************************************/

#include "AMQPDescribed.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp {
namespace internal {

    class AMQPDescriptor {
        protected :
            std::string m_symbol;
            int m_val;

        public :
            AMQPDescriptor()
                : m_symbol ("ERROR")
                , m_val (-1)
            { }

            AMQPDescriptor(const std::string & symbol_, int val_)
                : m_symbol (symbol_)
                , m_val (val_)
            { }

            virtual ~AMQPDescriptor() { }


            const std::string & symbol() const { return m_symbol; }

            void validateAndNext (pn_data_t * const ) const;

            virtual std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const = 0;
    };

}
}

/******************************************************************************/
