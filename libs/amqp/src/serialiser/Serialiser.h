#pragma once

/******************************************************************************/

#include "amqp/include/serialiser/ISerialiser.h"

/******************************************************************************/

namespace amqp::internal::serialiser {

    template<class Reader>
    class Serialiser : public amqp::serialiser::ISerialiser, public Reader {
        public :
            const std::string & name() const override = 0;
            const std::string & type() const override = 0;

            std::any read (pn_data_t * data_) const override  {
                return Reader::read (data_);
            }

            std::string readString (pn_data_t * data_) const override {
                return Reader::readString (data_);
            }

            std::unique_ptr<amqp::serialiser::reader::IValue> dump(
                const std::string & property_,
                pn_data_t * data_,
                const amqp::schema::ISchema & schema_
            ) const override {
                return Reader::dump (property_, data_, schema_);
            }

            std::unique_ptr<amqp::serialiser::reader::IValue> dump(
                pn_data_t * data_,
                const amqp::schema::ISchema & schema_
            ) const override {
                return Reader::dump (data_, schema_);
            }
    };

}

/******************************************************************************/
