#pragma once

/******************************************************************************/

#include <sstream>
#include <proton/codec.h>

#include "proton-wrapper/include/proton_wrapper.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    class IntPropertySerialiserBase;
    class BoolPropertySerialiserBase;
    class LongPropertySerialiserBase;
    class FloatPropertySerialiserBase;
    class DoublePropertySerialiserBase;
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

        [[maybe_unused]] static void get (prim *, pn_data_t *) {
            std::stringstream ss;
            ss << "NO MATCH FOR " << typeid(prim).name();
            throw std::runtime_error (ss.str());
        }
    };

    template<>
    struct PrimToSerialiser<int> {
        typedef serialisers::IntPropertySerialiserBase serialiser;

        [[maybe_unused]] static void put (const int * val_, pn_data_t * data_) {
            if (val_) {
                pn_data_put_int (data_, *val_);
            } else {
                pn_data_put_null (data_);
            }
        }

        [[maybe_unused]] static void get (int * rtn_, pn_data_t * data_) {
            proton::attest_is_int (data_, __FILE__, __LINE__);
            *rtn_ = pn_data_get_int (data_);
            DBG ("PrimToSerializer<int>::get - return " << *rtn_ << std::endl);
        }
    };

    template<>
    struct PrimToSerialiser<std::string> {
        typedef serialisers::StringPropertySerialiserBase serialiser;

        [[maybe_unused]] static void put(const std::string * val_, pn_data_t * data_) {
            if (val_) {
                pn_data_put_string (data_, pn_bytes (val_->size (), val_->data ()));
            } else {
                pn_data_put_null (data_);
            }
        }
    };

    template<>
    struct PrimToSerialiser<bool> {
        typedef serialisers::BoolPropertySerialiserBase serialiser;

        [[maybe_unused]] static void put (const bool * val_, pn_data_t * data_) {
            if (val_) {
                pn_data_put_bool (data_, *val_);
            } else {
                pn_data_put_null (data_);
            }
        }
    };

    template<>
    struct PrimToSerialiser<float> {
        typedef serialisers::FloatPropertySerialiserBase serialiser;

        [[maybe_unused]] static void put (const float * val_, pn_data_t * data_) {
            if (val_) {
                pn_data_put_float (data_, *val_);
            } else {
                pn_data_put_null (data_);
            }
        }
    };

    template<>
    struct PrimToSerialiser<double> {
        typedef serialisers::DoublePropertySerialiserBase serialiser;

        [[maybe_unused]] static void put (const double * val_, pn_data_t * data_) {
            if (val_) {
                pn_data_put_double (data_, *val_);
            } else {
                pn_data_put_null (data_);
            }
        }
    };

    template<>
    struct PrimToSerialiser<long> {
        typedef serialisers::LongPropertySerialiserBase serialiser;

        [[maybe_unused]] static void put (const long * val_, pn_data_t * data_) {
            if (val_) {
                pn_data_put_long (data_, *val_);
            } else {
                pn_data_put_null (data_);
            }
        }
    };
}

/******************************************************************************/
