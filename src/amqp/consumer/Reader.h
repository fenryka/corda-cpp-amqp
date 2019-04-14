#pragma once

/******************************************************************************/

#include <any>
#include <string>

#include "amqp/schema/Schema.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp {

    class Reader {
        public :
            virtual ~Reader() = default;
            virtual std::any read(pn_data_t *) const = 0;
            virtual std::string readString(pn_data_t *) const = 0;
            virtual std::string dump(pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const = 0;
    };

}

/******************************************************************************/

