#pragma once

/******************************************************************************/

#include <vector>

#include "RestrictedSerialiser.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template<class Reader>
    class EnumSerialiser : public RestrictedSerialiser<Reader> {
        private :
            std::vector <std::string> m_choices;

        public :
            EnumSerialiser(
                std::string type_, sVec <std::string> choices_
            ) : RestrictedSerialiser<Reader> (std::move(type_))
              , m_choices { std::move(choices_) }
            { }
    };

}

/******************************************************************************/
