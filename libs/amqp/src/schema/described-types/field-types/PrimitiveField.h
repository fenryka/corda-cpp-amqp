#pragma once

#include "Field.h"

/******************************************************************************/

namespace amqp::internal::schema {

    class PrimitiveField final : public Field {
        private :
            static const std::string m_fieldType;

        public :
            PrimitiveField (
                std::string, std::string, std::string,
                std::string, bool, bool);

            [[nodiscard]] Type AMQPType() const override;
            [[nodiscard]] const std::string & resolvedType() const override;
    };

}

/******************************************************************************/
