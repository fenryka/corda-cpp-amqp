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

            virtual std::unique_ptr<Pair> dump(
                const std::string &,
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &
            ) const override = 0;

            virtual const std::string & name() const override = 0;
    };


    class StringPropertyReader : public PropertyReader {
        private :
            static const std::string m_name;

        public :
            std::string readString (pn_data_t *) const override;

            std::any read (pn_data_t *) const override;

            std::unique_ptr<Pair> dump(
                const std::string &,
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &
            ) const override;

            const std::string & name() const override {
                return m_name;
            }
    };

    class IntPropertyReader : public PropertyReader {
        private :
            static const std::string m_name;

        public :
            std::string readString (pn_data_t *) const override;

            std::any read (pn_data_t *) const override;

            std::unique_ptr<Pair> dump(
                const std::string &,
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &
            ) const override;

            const std::string & name() const override {
                return m_name;
            }
    };

    class BoolPropertyReader : public PropertyReader {
        private :
            static const std::string m_name;

        public :
            std::string readString (pn_data_t *) const override;

            std::any read (pn_data_t *) const override;

            std::unique_ptr<Pair> dump(
                const std::string &,
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &
            ) const override;

            const std::string & name() const override {
                return m_name;
            }
    };

    class LongPropertyReader : public PropertyReader {
        private :
            static const std::string m_name;

        public :
            std::string readString (pn_data_t *) const override;

            std::any read (pn_data_t *) const override;

            std::unique_ptr<Pair> dump(
                const std::string &,
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &
            ) const override;

            const std::string & name() const override {
                return m_name;
            }
    };

    class DoublePropertyReader : public PropertyReader {
        private :
            static const std::string m_name;

        public :
            std::string readString (pn_data_t *) const override;

            std::any read (pn_data_t *) const override;

            std::unique_ptr<Pair> dump(
                const std::string &,
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &
            ) const override;

            const std::string & name() const override {
                return m_name;
            }
    };

}

/******************************************************************************/


