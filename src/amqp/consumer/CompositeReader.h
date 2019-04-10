#pragma once

/******************************************************************************/

#include "Reader.h"

/******************************************************************************/

namespace amqp {

    class CompositeReader : public StringReader {
        public :
            std::string read(pn_data_t *) const override;
    };

}

/******************************************************************************/

