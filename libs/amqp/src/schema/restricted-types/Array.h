#pragma once

#include "Restricted.h"

/******************************************************************************/

namespace amqp::internal::schema {

    class Array : public Restricted {
        public :
            static std::string arrayType (const std::string &);
            static bool isArrayType (const std::string &);

        private :
            std::vector<std::string> m_arrayOf;
            std::string m_source;

            [[nodiscard]] int dependsOnMap (const Map &) const override;
            [[nodiscard]] int dependsOnList (const List &) const override;
            [[nodiscard]] int dependsOnEnum (const Enum &) const override;
            [[nodiscard]] int dependsOnArray (const Array &) const override;

        public :
            Array (
                uPtr<Descriptor> descriptor_,
                std::string,
                std::string,
                std::vector<std::string>,
                std::string);

            [[nodiscard]] std::vector<std::string>::const_iterator begin() const override;
            [[nodiscard]] std::vector<std::string>::const_iterator end() const override;

            [[nodiscard]] const std::string & arrayOf() const;

            [[nodiscard]] int dependsOnRHS (const Composite &) const override;
    };

}

/******************************************************************************/
