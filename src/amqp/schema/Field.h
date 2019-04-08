#pragma once

/******************************************************************************/

#include "amqp/AMQPDescribed.h"

#include <list>
#include <string>

/******************************************************************************/

namespace amqp {
namespace internal {
namespace schema {

    /**
     *
     * A Corda AMQP Scehma Field type has:
     *   - name      : String
     *   - type      : String
     *   - requires  : List<String>
     *   - default   : nullable String
     *   - label     : nullable String
     *   - mandatory : Boolean
     *   - multiple  : Boolean
     */
    class Field : public AMQPDescribed {
        private :
            std::string            m_name;
            std::string            m_type;
            std::list<std::string> m_requires;
            std::string            m_default;
            std::string            m_label;
            bool                   m_mandatory;
            bool                   m_mulitple;

        public :
            Field() = default;

            Field (
                const std::string & name_,
                const std::string & type_,
                const std::list<std::string> & requires_,
                const std::string & default_,
                const std::string & label_,
                bool mandatory_,
                bool multiple_
            ) : m_name (name_)
              , m_type (type_)
              , m_requires (requires_)
              , m_default (default_)
              , m_label (label_)
              , m_mandatory (mandatory_)
              , m_mulitple (multiple_)
            { }

            /*
            Field (const Field & field_)
              : m_name (field_->m_name)
              , m_type (field_->m_type)
              , m_requires (field_->m_requires)
              , m_default (field_->m_default)
              , m_label (field_->m_label)
              , m_mandatory (field_->m_mandatory)
              , m_mulitple (field_->m_multiple)
            { }
            */
    };

}
}
}

/******************************************************************************/

