#pragma once

#include "Restricted.h"

namespace amqp::internal::schema {

    class List : public Restricted {
        private :
            std::string m_listOf;

        public :
            List (
                uPtr<Descriptor> & descriptor_,
                const std::string &,
                const std::string &,
                const std::vector<std::string> &,
                const std::string &);

            std::vector<std::string>::const_iterator containedTypes() const override;

            const std::string & listOf() const;
    };

}
