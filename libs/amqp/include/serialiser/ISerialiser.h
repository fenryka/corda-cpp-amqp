#pragma once

/******************************************************************************/

#include <string>

#include "reader/IReader.h"
#include "writer/IWriter.h"

/******************************************************************************/

namespace amqp::serialiser {

    /**
     * In our public interface reader and writer are policies that define how we read and write
     * from a stream encapsulated by the serailser. This should let us plug various readers
     * and writers into the same generic mechanism
     */
    class ISerialiser : public reader::IReader, public writer::IWriter {
        private :
            static const std::vector<std::weak_ptr<amqp::serialiser::ISerialiser>> m_empty;

        public :
            [[nodiscard]] virtual const std::string & name() const = 0;
            [[nodiscard]] virtual const std::string & type() const = 0;

            /*
             * Non primitive serializers have sub elements, this should return a reference
             * to those
             */
            [[nodiscard]] virtual const std::vector<std::weak_ptr<amqp::serialiser::ISerialiser>> & serialisers() const {
                return m_empty;
            }

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

            /*
             * Redeclare the IWriter interface
             */
            void write (std::any, pn_data_t *) const override = 0;
    };

}

/******************************************************************************/
