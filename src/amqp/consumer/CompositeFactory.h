#pragma once

/******************************************************************************/

#include <map>

#include "Schema.h"
#include "CompositeReader.h"

/******************************************************************************/

class CompositeFactory {
    private :
        std::map<std::string, std::unique_ptr<amqp::CompositeReader>> m_readers;

    public :
        CompositeFactory() = default;

        void process (std::unique_ptr<amqp::internal::schema::Schema> & schema);

};

/******************************************************************************/

