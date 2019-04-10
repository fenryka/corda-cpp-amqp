#pragma once

/******************************************************************************/

#include "Reader.h"

/******************************************************************************/

namespace amqp {

    class PropertyReader : public StringReader {
        public :
            std::string read(pn_data_t *) const override;
    };

}

/******************************************************************************/

