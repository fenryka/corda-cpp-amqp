#pragma once

/******************************************************************************/

#include "amqp/include/serialiser/ISerialiser.h"

#include <sstream>
#include <proton/codec.h>

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    class IntPropertySerialiserBase;
    class StringPropertySerialiserBase;

}

/******************************************************************************/

namespace amqp::internal::serialiser {

    template<typename prim>
    struct PrimToSerialiser {
        static void put(const prim &, pn_data_t *) {
            std::stringstream ss;
            ss << "NO MATCH FOR " << typeid(prim).name();
            throw std::runtime_error (ss.str());
        }
    };

    template<>
    struct PrimToSerialiser<int> {
        typedef serialisers::IntPropertySerialiserBase serialiser;

        static void put (const int * val_, pn_data_t * data_) {
            if (val_) {
                pn_data_put_int (data_, *val_);
            } else {
                pn_data_put_null (data_);
            }
        }
    };

    template<>
    struct PrimToSerialiser<std::string> {
        typedef serialisers::StringPropertySerialiserBase serialiser;

        static void put(const std::string * val_, pn_data_t * data_) {
            if (val_) {
                pn_data_put_string (data_, pn_bytes (val_->size (), val_->data ()));
            } else {
                pn_data_put_null (data_);
            }
        }
    };
}

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

