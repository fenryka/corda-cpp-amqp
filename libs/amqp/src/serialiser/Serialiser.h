#pragma once

/******************************************************************************/

#include "amqp/include/serialiser/ISerialiser.h"

#include "corda-utils/include/debug.h"

/******************************************************************************/

namespace amqp::internal::serialiser {

    template<class Reader, class Writer>
    class Serialiser
            : public amqp::serialiser::ISerialiser
            , public Reader
            , public Writer
     {
        public :
            [[nodiscard]] const std::string & name() const override = 0;
            [[nodiscard]] const std::string & type() const override = 0;

            /******************************************************************
             *
             * Reader Interface
             *
             ******************************************************************/

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

            /******************************************************************
             *
             * Writer Interface
             *
             ******************************************************************/

            void write (std::any val_, pn_data_t * data_) const override {
                Writer::write (val_, data_);
            }
    };

}

/******************************************************************************/

