#pragma once

/******************************************************************************/

#include <map>
#include <string>
#include <iostream>

/******************************************************************************/

#include "AMQPDescribed.h"
#include "amqp/AMQPDescriptor.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp {
namespace internal {

    class EnvelopeDescriptor : public AMQPDescriptor {
        public :
            EnvelopeDescriptor() : AMQPDescriptor() { }

            EnvelopeDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            virtual ~EnvelopeDescriptor() { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}
}


/******************************************************************************/

namespace amqp {
namespace internal {

    class SchemaDescriptor : public AMQPDescriptor {
        public :
            SchemaDescriptor() : AMQPDescriptor() { }

            SchemaDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            virtual ~SchemaDescriptor() { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}
}

/******************************************************************************/

namespace amqp {
namespace internal {

    class ObjectDescriptor : public AMQPDescriptor {
        public :
            ObjectDescriptor() : AMQPDescriptor() { }

            ObjectDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            virtual ~ObjectDescriptor() { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}
}

/******************************************************************************/

namespace amqp {
namespace internal {

    class FieldDescriptor : public AMQPDescriptor {
        public :
            FieldDescriptor() : AMQPDescriptor() { }

            FieldDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            virtual ~FieldDescriptor() { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}
}

/******************************************************************************/

namespace amqp {
namespace internal {

    class CompositeDescriptor : public AMQPDescriptor {
        public :
            CompositeDescriptor() : AMQPDescriptor() { }

            CompositeDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            virtual ~CompositeDescriptor() { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}
}

/******************************************************************************/

namespace amqp {
namespace internal {

    class RestrictedDescriptor : public AMQPDescriptor {
        public :
            RestrictedDescriptor() : AMQPDescriptor() { }

            RestrictedDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            virtual ~RestrictedDescriptor() { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}
}

/******************************************************************************/

namespace amqp {
namespace internal {

    class ChoiceDescriptor : public AMQPDescriptor {
        public :
            ChoiceDescriptor() : AMQPDescriptor() { }

            ChoiceDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            virtual ~ChoiceDescriptor() { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}
}

/******************************************************************************/

namespace amqp {
namespace internal {

    class ReferencedObjectDescriptor : public AMQPDescriptor {
        public :
            ReferencedObjectDescriptor() : AMQPDescriptor() { }

            ReferencedObjectDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            virtual ~ReferencedObjectDescriptor() { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}
}

/******************************************************************************/

namespace amqp {
namespace internal {

    class TransformSchemaDescriptor : public AMQPDescriptor {
        public :
            TransformSchemaDescriptor() : AMQPDescriptor() { }

            TransformSchemaDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            virtual ~TransformSchemaDescriptor() { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}
}

/******************************************************************************/

namespace amqp {
namespace internal {

    class TransformElementDescriptor : public AMQPDescriptor {
        public :
            TransformElementDescriptor() : AMQPDescriptor() { }

            TransformElementDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            virtual ~TransformElementDescriptor() { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}
}

/******************************************************************************/

namespace amqp {
namespace internal {

    class TransformElementKeyDescriptor : public AMQPDescriptor {
        public :
            TransformElementKeyDescriptor() : AMQPDescriptor() { }

            TransformElementKeyDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            virtual ~TransformElementKeyDescriptor() { }

            std::unique_ptr<AMQPDescribed> build (pn_data_t * data_) const override;
    };

}
}

/******************************************************************************/
