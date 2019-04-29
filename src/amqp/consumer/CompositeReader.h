#pragma once

/******************************************************************************/

#include "Reader.h"

#include <any>
#include <vector>

/******************************************************************************/

namespace amqp {

    class CompositeReader : public Reader {
        private :
            std::vector<std::weak_ptr<amqp::Reader>> m_readers;

            static const std::string m_name;

            std::vector<std::unique_ptr<amqp::Value>> _dump (
                    pn_data_t * data_,
                    const std::unique_ptr<amqp::internal::schema::Schema> & schema_) const;

        public :
            explicit CompositeReader (
                std::vector<std::weak_ptr<amqp::Reader>> & readers_
            ) : m_readers (std::move (readers_)) { }

            ~CompositeReader() override = default;

            std::any read (pn_data_t *) const override;

            std::string readString(pn_data_t *) const override;

            std::unique_ptr<Value> dump(
                const std::string &,
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const override;

            std::unique_ptr<Value> dump(
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const override;

            const std::string & name() const override {
                return m_name;
            }
    };

}

/******************************************************************************/

