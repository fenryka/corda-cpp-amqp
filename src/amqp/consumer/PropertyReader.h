#pragma once

/******************************************************************************/

#include "Reader.h"

#include "amqp/schema/Field.h"


/******************************************************************************/

namespace amqp {

    class PropertyReader : public Reader {
        private :
            using FieldPtr = std::unique_ptr<internal::schema::Field>;

        public :
            /**
             * Static Faactory method for creating apropriate derived types
             */
            static std::shared_ptr<PropertyReader> make (const FieldPtr &);

            virtual ~PropertyReader() = default;

            virtual std::string readString(pn_data_t *) const override = 0;
            virtual std::any read (pn_data_t *) const override = 0;
            virtual std::string dump(pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const override = 0;
    };


    class StringPropertyReader : public PropertyReader {
        public :
            std::string readString (pn_data_t *) const override;
            std::any read (pn_data_t *) const override;
            std::string dump(pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const override;
    };

    class IntPropertyReader : public PropertyReader {
        public :
            std::string readString (pn_data_t *) const override;
            std::any read (pn_data_t *) const override;
            std::string dump(pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const override;
    };

    class BoolPropertyReader : public PropertyReader {
        public :
            std::string readString (pn_data_t *) const override;
            std::any read (pn_data_t *) const override;
            std::string dump(pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const override;
    };

    class LongPropertyReader : public PropertyReader {
        public :
            std::string readString (pn_data_t *) const override;
            std::any read (pn_data_t *) const override;
            std::string dump(pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const override;
    };

    class DoublePropertyReader : public PropertyReader {
        public :
            std::string readString (pn_data_t *) const override;
            std::any read (pn_data_t *) const override;
            std::string dump(pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const override;
    };

}

/******************************************************************************/


