#pragma once

/******************************************************************************/

#include "Reader.h"

#include "Field.h"

/******************************************************************************/

namespace amqp {

    class PropertyReader : public StringReader {
        private :
            using FieldPtr = std::unique_ptr<internal::schema::Field>;

        public :
            /**
             * Static Faactory method for creating apropriate derived types
             */
            static std::unique_ptr<PropertyReader> make (const FieldPtr &);

            virtual std::string read(pn_data_t *) const override = 0;

            virtual ~PropertyReader() = default;
    };


    class StringPropertyReader : public PropertyReader {
        public :
            std::string read(pn_data_t *) const override;
    };

    class IntPropertyReader : public PropertyReader {
        public :
            std::string read(pn_data_t *) const override;
    };
}

/******************************************************************************/


