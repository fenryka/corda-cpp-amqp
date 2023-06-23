#pragma once

#include "Field.h"

/******************************************************************************/

namespace amqp::internal::schema {

    class CustomField : public Field {
        public :
            CustomField (
                std::string, std::string, std::list<std::string>,
                std::string, std::string, bool, bool);

            [[nodiscard]] Type AMQPType() const override;
            [[nodiscard]] const std::string & resolvedType() const override;
    };

}

/******************************************************************************/
