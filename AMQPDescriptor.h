#pragma once

/******************************************************************************/

#include <map>
#include <string>
#include <iostream>

/******************************************************************************/

#include "AMQPDescribed.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp {

    class AMQPDescriptor {
        protected :
            std::string m_symbol;
            int m_val;

        public :
            AMQPDescriptor()
                : m_symbol ("ERROR")
                , m_val (-1)
            { }

            AMQPDescriptor(const std::string & symbol_, int val_)
                : m_symbol (symbol_)
                , m_val (val_)
            { }


            const std::string & symbol() const { return m_symbol; }

            void validateAndNext (pn_data_t * const ) const;

            std::unique_ptr<AMQPDescribed> dispatchDescribed(pn_data_t * data_) const;

            virtual std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const {
                return std::unique_ptr<AMQPDescribed>(nullptr);
            }
    };

}

/******************************************************************************/

namespace amqp {

    class EnvelopeDescriptor : public AMQPDescriptor {
        public :
            EnvelopeDescriptor() : AMQPDescriptor() { }

            EnvelopeDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}

/******************************************************************************/

namespace amqp {

    class SchemaDescriptor : public AMQPDescriptor {
        public :
            SchemaDescriptor() : AMQPDescriptor() { }

            SchemaDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}

/******************************************************************************/

namespace amqp {

    class ObjectDescriptor : public AMQPDescriptor {
        public :
            ObjectDescriptor() : AMQPDescriptor() { }

            ObjectDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}

/******************************************************************************/

namespace amqp {

    class FieldDescriptor : public AMQPDescriptor {
        public :
            FieldDescriptor() : AMQPDescriptor() { }

            FieldDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}

/******************************************************************************/

namespace amqp {

    class CompositeDescriptor : public AMQPDescriptor {
        public :
            CompositeDescriptor() : AMQPDescriptor() { }

            CompositeDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}

/******************************************************************************/

namespace amqp {

    class RestrictedDescriptor : public AMQPDescriptor {
        public :
            RestrictedDescriptor() : AMQPDescriptor() { }

            RestrictedDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}

/******************************************************************************/

namespace amqp {

    class ChoiceDescriptor : public AMQPDescriptor {
        public :
            ChoiceDescriptor() : AMQPDescriptor() { }

            ChoiceDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}

/******************************************************************************/

namespace amqp {

    class ReferencedObjectDescriptor : public AMQPDescriptor {
        public :
            ReferencedObjectDescriptor() : AMQPDescriptor() { }

            ReferencedObjectDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}

/******************************************************************************/

namespace amqp {

    class TransformSchemaDescriptor : public AMQPDescriptor {
        public :
            TransformSchemaDescriptor() : AMQPDescriptor() { }

            TransformSchemaDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}

/******************************************************************************/

namespace amqp {

    class TransformElementDescriptor : public AMQPDescriptor {
        public :
            TransformElementDescriptor() : AMQPDescriptor() { }

            TransformElementDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}

/******************************************************************************/

namespace amqp {

    class TransformElementKeyDescriptor : public AMQPDescriptor {
        public :
            TransformElementKeyDescriptor() : AMQPDescriptor() { }

            TransformElementKeyDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}

/******************************************************************************/
