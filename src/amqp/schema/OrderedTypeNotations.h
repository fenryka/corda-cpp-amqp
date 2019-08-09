#pragma once

#include <list>

#include "types.h"
#include "AMQPTypeNotation.h"

namespace amqp::internal::schema {



    class OrderedTypeNotations {
        private:
            std::list<std::list<uPtr<schema::AMQPTypeNotation>>> m_schemas;

        public :
            void insert(uPtr<schema::AMQPTypeNotation> ptr);

            friend std::ostream & operator << (std::ostream & stream_, const OrderedTypeNotations &);
    };

}
