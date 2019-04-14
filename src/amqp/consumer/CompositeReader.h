#pragma once

/******************************************************************************/

#include "Reader.h"

#include <any>
#include <vector>

/******************************************************************************/

namespace amqp {

    class CompositeReader : public Reader {
        private :
            std::vector<std::shared_ptr<amqp::Reader>> m_readers;

        public :
            CompositeReader (
                std::vector<std::shared_ptr<amqp::Reader>> & readers_
            ) : m_readers (std::move (readers_))
            { }

            virtual ~CompositeReader() = default;

            std::any    read (pn_data_t *) const override;
            std::string readString(pn_data_t *) const override;
            std::string dump(pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const override;
    };

}

/******************************************************************************/

