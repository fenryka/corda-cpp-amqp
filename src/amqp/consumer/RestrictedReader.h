#pragma once

/******************************************************************************/

#include "Reader.h"

#include <any>
#include <vector>

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp {

    class RestrictedReader : public Reader {
        private :
            static const std::string m_name;

        public :
            RestrictedReader () = default;

            ~RestrictedReader() final = default;

            std::any read(pn_data_t *) const override ;

            std::string readString(pn_data_t *) const override;

            std::unique_ptr<Pair> dump(
                const std::string &,
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const override;

            const std::string & name() const override;
    };

}

/******************************************************************************/

