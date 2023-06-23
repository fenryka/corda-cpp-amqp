#pragma once

#include "RestrictedField.h"

/******************************************************************************/

namespace amqp::internal::schema {

    class ArrayField final : public RestrictedField {
        private :
            static const std::string m_fieldType;

        public :
            ArrayField (
                std::string, std::string, std::list<std::string>,
                std::string, std::string, bool, bool);

        [[nodiscard]] Type AMQPType() const override;
        [[nodiscard]] const std::string & resolvedType() const override;
    };

}

/******************************************************************************/
