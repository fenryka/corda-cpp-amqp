#pragma once

#ifndef __FIELD_H__
#define __FIELD_H__

/******************************************************************************/

#include "amqp/src/schema/described-types/Descriptor.h"

#include "corda-utils/include/types.h"

#include <set>
#include <list>
#include <string>
#include <iosfwd>

/******************************************************************************/

namespace amqp::internal::schema {

    /**
     *
     * A Corda AMQP Schema Field type has:
     *   - name      : String
     *   - type      : String
     *   - requires  : List<String>
     *   - default   : nullable String
     *   - label     : nullable String
     *   - mandatory : Boolean
     *   - multiple  : Boolean
     *
     *   NOTE
     *  ------
     *  type - types with a  dollar symbol, for example net.corda.v5.crypto.DigitalSignature$WithKeyID,
     *         are referring to a nested class, where WithKeyID is a nested class (or interface)
     */
    class Field : public amqp::schema::ISchemaElement {
        public :
            friend std::ostream & operator << (std::ostream &, const Field &);

            static bool typeIsPrimitive (const std::string &);

            static uPtr<Field> make (
                std::string, std::string, std::list<std::string>,
                std::string, std::string, bool, bool);

            enum Type { composite_t, restricted_t, array_t, primitive_t, custom_t };

    private :
            std::string            m_name;
            std::string            m_type;
            std::list<std::string> m_requires;
            std::string            m_default;
            std::string            m_label;


            [[maybe_unused]] bool  m_mandatory;
            [[maybe_unused]] bool  m_multiple;

        protected :
            Field (std::string, std::string, std::list<std::string>,
               std::string, std::string, bool, bool);

        public :
            [[nodiscard]] const std::string & name() const;
            [[nodiscard]] const std::string & type() const;

            [[maybe_unused]] [[nodiscard]] const std::string & label() const;
            [[nodiscard]] const std::list<std::string> & requires() const;

            /**
             * Is the field composite, restricted etc
             * @return
             */
            [[nodiscard]] virtual Type AMQPType() const = 0;

            /**
             * Resole from the header what type the field is. If named in the schema
             * then its trivial, its the named type. If it's a wildcard though
             * we have to work out what it might be based on the interfaces it requires
             *
             * @return
             */
            [[nodiscard]] virtual const std::string & resolvedType() const = 0;
    };

}

/******************************************************************************/

std::ostream &
operator << (std::ostream& os, const amqp::internal::schema::Field::Type & obj);

/******************************************************************************/

#endif