#pragma once

#include "Restricted.h"

/******************************************************************************/

namespace amqp::internal::schema {

    class Map : public Restricted {
        private :
            std::vector<std::string> m_mapOf;
            std::string m_source;

            [[nodiscard]] int dependsOnMap (const Map &) const override;
            [[nodiscard]] int dependsOnList (const List &) const override;
            [[nodiscard]] int dependsOnEnum (const Enum &) const override;
            [[nodiscard]] int dependsOnArray (const Array &) const override;

        public :
            Map (
                uPtr<Descriptor> descriptor_,
                std::string,
                std::string,
                std::vector<std::string>,
                std::string);

            [[nodiscard]] std::vector<std::string>::const_iterator begin() const override;
            [[nodiscard]] std::vector<std::string>::const_iterator end() const override;

            [[nodiscard]] std::pair<
                std::reference_wrapper<const std::string>,
                std::reference_wrapper<const std::string>> mapOf() const;

            [[nodiscard]] int dependsOnRHS (const Composite &) const override;
    };

}

/******************************************************************************/
