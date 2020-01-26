#pragma once

/******************************************************************************/

#include <any>

#include "amqp/include/serialiser/writer/IWriter.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp::internal::serialiser::writer {

    class Writer : public amqp::serialiser::writer::IWriter {
        public :
            ~Writer() override = default;

            void write (std::any, pn_data_t *) const override;
    };

}

/******************************************************************************/
