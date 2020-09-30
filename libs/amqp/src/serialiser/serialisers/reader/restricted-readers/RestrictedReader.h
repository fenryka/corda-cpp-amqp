#pragma once

/******************************************************************************/

#include "serialisers/reader/Reader.h"

#include <any>
#include <vector>

#include "restricted-types/Restricted.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp::internal::serialiser::reader {

    class RestrictedReader : public Reader {
        public :
            RestrictedReader() = default;
            ~RestrictedReader() override = default;

            /*
             * XXX Clearly this needs actually implementing
             */
            std::any read (pn_data_t *) const override {
                return std::any (1);
            }

            /*
             * XXX Clearly this needs actually implementing
             */
            std::string readString (pn_data_t *) const override  {
                return "hello";
            }

            std::unique_ptr<amqp::serialiser::reader::IValue> dump(
                const std::string &,
                pn_data_t *,
                const amqp::schema::ISchema &) const override = 0;
    };

}

/******************************************************************************/


