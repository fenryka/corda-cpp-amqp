#pragma once

/******************************************************************************/

#include "Reader.h"

#include <any>
#include <vector>

#include "Restricted.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp {

    class RestrictedReader : public Reader {
        private :
            static const std::string m_name;

        public :
            RestrictedReader () = default;

            ~RestrictedReader() = default;

            std::any read(pn_data_t *) const override ;

            std::string readString(pn_data_t *) const override;

            std::unique_ptr<Value> dump(
                const std::string &,
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const override = 0;

            const std::string & name() const override;
    };

}

/******************************************************************************/

namespace amqp {

    class ListReader : public RestrictedReader {
        private :
            static const std::string m_name;

            // How to read the underlying types
            std::weak_ptr<amqp::Reader> m_reader;

            std::list<std::unique_ptr<amqp::Value>> dump_(
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const;

        public :
            ListReader (std::weak_ptr<amqp::Reader> reader_)
                : m_reader (reader_)
            { }

            ~ListReader() final = default;

            internal::schema::Restricted::RestrictedTypes type() const;

            std::unique_ptr<Value> dump(
                const std::string &,
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const override;

            std::unique_ptr<Value> dump(
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const override;
    };

}

/******************************************************************************/

