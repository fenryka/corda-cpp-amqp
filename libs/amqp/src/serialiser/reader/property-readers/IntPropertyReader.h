#pragma once

/******************************************************************************/

#include "PropertyReader.h"

/******************************************************************************/

namespace amqp::internal::serialiser::reader {

    class IntPropertyReader : public PropertyReader {
    private :
        static const std::string m_name;
        static const std::string m_type;

    public :
        ~IntPropertyReader() override = default;

        std::string readString (pn_data_t *) const override;

        std::any read(pn_data_t *) const override;

        uPtr <amqp::serialiser::reader::IValue> dump(
                const std::string &,
                pn_data_t *,
                const amqp::schema::ISchema &
        ) const override;

        uPtr <amqp::serialiser::reader::IValue> dump(
                pn_data_t *,
                const amqp::schema::ISchema &
        ) const override;

        const std::string &name() const override;
        const std::string &type() const override;
    };
}

/******************************************************************************/
