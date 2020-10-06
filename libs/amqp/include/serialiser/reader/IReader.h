#pragma once

/******************************************************************************/

#include <any>

#include "amqp/include/schema/ISchema.h"

/******************************************************************************
 *
 * Forward declarations
 *
 ******************************************************************************/

struct pn_data_t;

/******************************************************************************
 *
 * class amqp::reader::IValue
 *
 ******************************************************************************/

/**
 * Used by the dump method on all instantiated instances of amqp readers
 * it represents the ability to pull out a value from the blob as determined
 * by the reader type and convert it to a string formatted nicely as JSON
 */
namespace amqp::serialiser::reader {

    class IValue {
        public :
            [[nodiscard]] virtual std::string dump() const = 0;

            virtual ~IValue() = default;
    };

}

/******************************************************************************
 *
 * class ampq::reader::IReader
 *
 ******************************************************************************/

namespace amqp::serialiser::reader {

    class IReader {
        public :
            virtual ~IReader() = default;

            virtual std::any read (pn_data_t *) const = 0;
            virtual std::string readString (pn_data_t *) const = 0;

            virtual std::unique_ptr<IValue> dump(
                    const std::string &,
                    pn_data_t *,
                    const schema::ISchema &) const = 0;

            virtual std::unique_ptr<IValue> dump(
                    pn_data_t *,
                    const schema::ISchema &) const = 0;
    };

}

/******************************************************************************/
