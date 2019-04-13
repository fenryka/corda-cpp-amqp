#pragma once

/******************************************************************************/

#include "Reader.h"

/******************************************************************************/

namespace amqp {

    class CompositeReader : public StringReader {
        public :
            virtual ~CompositeReader() = default;

            std::string read(pn_data_t *) const override;
    };

}

/******************************************************************************/

