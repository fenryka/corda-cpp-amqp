#pragma once

#include "Field.h"

/******************************************************************************/

namespace amqp::internal::schema {

    class RestrictedField : public Field {
        private :
            sVec<std::string> m_subTypes;

        public :
            RestrictedField (
                std::string, std::string, std::list<std::string>,
                std::string, std::string, bool, bool);

            [[nodiscard]] Type AMQPType() const override;
            [[nodiscard]] const std::string & resolvedType() const override;
            [[nodiscard]] const sVec<std::string> & subTypes() const;
    };

}

/******************************************************************************/
