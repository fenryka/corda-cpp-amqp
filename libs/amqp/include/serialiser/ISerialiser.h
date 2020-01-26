#pragma once

/******************************************************************************/

#include <string>

#include "reader/IReader.h"

/******************************************************************************/

namespace amqp::serialiser {

    /**
     * In our public interface reader and writer are policies that define how we read and write
     * from a stream encapsulated by the serailser. This should let us plug various readers
     * and writers into the same generic mechanism
     */
    class ISerialiser : public reader::IReader {
        public :
            virtual const std::string & name() const = 0;
            virtual const std::string & type() const = 0;

            /*
             * Redeclare the IReader interface
             */
            std::any read (pn_data_t *) const override = 0;
            std::string readString (pn_data_t *) const override = 0;

            std::unique_ptr<amqp::serialiser::reader::IValue> dump(
                const std::string &,
                pn_data_t *,
                const schema::ISchema &) const override = 0;

            std::unique_ptr<amqp::serialiser::reader::IValue> dump(
                pn_data_t *,
                const schema::ISchema &) const override = 0;
    };

}

/******************************************************************************/
