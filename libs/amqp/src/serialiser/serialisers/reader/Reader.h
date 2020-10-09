#pragma once

/******************************************************************************/

#include <any>
#include <list>
#include <string>
#include <vector>
#include <memory>

#include "amqp/src/schema/described-types/Schema.h"
#include "amqp/include/serialiser/reader/IReader.h"

/******************************************************************************/

namespace amqp::internal::serialiser::reader {

    class Value : public amqp::serialiser::reader::IValue {
        public :
            [[nodiscard]] std::string dump() const override = 0;

            ~Value() override = default;
    };

    /*
     * A Single represents some value read out of a proton tree that
     * exists without an association. The canonical example is an
     * element of a list. The list itself would be a pair,
     *
     * e.g. a : [ ]
     *
     * but the values of the list
     *
     * e.g. a : [ A, B, C ]
     *
     * are Singles
     */
    class Single : public Value {
        public :
            [[nodiscard]] std::string dump() const override = 0;

            ~Single() override = default;
    };

    class NullTypedSingle : public Single {
        public:
            explicit NullTypedSingle()
                : Single()
            { }

            [[nodiscard]] std::string dump() const override;
    };

    template<typename T>
    class TypedSingle : public Single {
        private:
            T m_value;

        public:
            explicit TypedSingle (const T & value_)
                : Single()
                , m_value (value_)
            { }

            explicit TypedSingle (T && value_)
                : Single()
                , m_value { std::move (value_) }
            { }

            TypedSingle (const TypedSingle && value_) noexcept
                : Single()
                , m_value { std::move (value_.m_value) }
            { }

            [[nodiscard]] const T & value() const {
                return m_value;
            }

            [[nodiscard]] std::string dump() const override;
    };

    /*
     * A Pair represents an association between a property and
     * the value of the property, i.e. a : b where property
     * a has value b
     */
    class Pair : public Value {
        protected :
            std::string m_property;

        public:
            explicit Pair (std::string property_)
                : Value()
                , m_property (std::move (property_))
            { }

            ~Pair() override = default;

            Pair (Pair && pair_) noexcept
                : m_property (std::move (pair_.m_property))
            { }

            [[nodiscard]] std::string dump() const override = 0;
    };

    class NullTypedPair : public Pair {
        public:
            explicit NullTypedPair (const std::string & property_)
                : Pair (property_)
            { }

            [[nodiscard]] std::string dump() const override;
    };

    template<typename T>
    class TypedPair : public Pair {
        private:
            T m_value;

        public:
            TypedPair (const std::string & property_, T & value_)
                : Pair (property_)
                , m_value (value_)
            { }

            TypedPair (const std::string & property_, T && value_)
                : Pair (property_)
                , m_value (std::move (value_))
            { }

            TypedPair (TypedPair && pair_) noexcept
                : Pair (std::move (pair_.m_property))
                , m_value (std::move (pair_.m_value))
            { }

            [[nodiscard]] const T & value() const {
                return m_value;
            }

            [[nodiscard]] std::string dump() const override;
    };

    /**
     * Similar to [Pair] where k : v relationships  are modelled. In this
     * case, however, rather than modelling a property : value relationship
     * we are modelling a key : value one. The primary difference is that
     * keys need not be simple strings.
     */
    class ValuePair : public Value {
        private :
            uPtr<amqp::serialiser::reader::IValue> m_key;
            uPtr<amqp::serialiser::reader::IValue> m_value;

        public :
            ValuePair (
                decltype (m_key) key_,
                decltype (m_value) value_
            ) : Value ()
              , m_key (std::move (key_))
              , m_value (std::move (value_))
        { }

        [[nodiscard]] std::string dump() const override;
    };

}

/******************************************************************************
 *
 * amqp::internal::serialiser::reader::TypedSingle
 *
 ******************************************************************************/

template<typename T>
inline std::string
amqp::internal::serialiser::reader::
TypedSingle<T>::dump() const {
    return std::to_string (m_value);
}

template<>
inline std::string
amqp::internal::serialiser::reader::
TypedSingle<std::string>::dump() const {
    return m_value;
}

template<>
std::string
amqp::internal::serialiser::reader::
TypedSingle<sVec<uPtr<amqp::serialiser::reader::IValue>>>::dump() const;

template<>
std::string
amqp::internal::serialiser::reader::
TypedSingle<sList<uPtr<amqp::serialiser::reader::IValue>>>::dump() const;

template<>
std::string
amqp::internal::serialiser::reader::
TypedSingle<sVec<uPtr<amqp::internal::serialiser::reader::Single>>>::dump() const;

template<>
std::string
amqp::internal::serialiser::reader::
TypedSingle<sList<uPtr<amqp::internal::serialiser::reader::Single>>>::dump() const;

/******************************************************************************
 *
 * amqp::internal::serialiser::reader::TypedPair
 *
 ******************************************************************************/

template<typename T>
inline std::string
amqp::internal::serialiser::reader::
TypedPair<T>::dump() const {
    return m_property + " : " + std::to_string (m_value);
}

template<>
inline std::string
amqp::internal::serialiser::reader::
TypedPair<std::string>::dump() const {
    return m_property + " : " + m_value;
}

template<>
std::string
amqp::internal::serialiser::reader::
TypedPair<sVec<uPtr<amqp::serialiser::reader::IValue>>>::dump() const;

template<>
std::string
amqp::internal::serialiser::reader::
TypedPair<sList<uPtr<amqp::serialiser::reader::IValue>>>::dump() const;

template<>
std::string
amqp::internal::serialiser::reader::
TypedPair<sVec<uPtr<amqp::internal::serialiser::reader::Pair>>>::dump() const;

template<>
std::string
amqp::internal::serialiser::reader::
TypedPair<sList<uPtr<amqp::internal::serialiser::reader::Pair>>>::dump() const;

/******************************************************************************
 *
 *
 *
 ******************************************************************************/

namespace amqp::internal::serialiser::reader  {

    /**
     * Interface that represents an object that has the ability to consume
     * the payload of a Corda serialized blob in a way defined by some
     * prior construction. This construction will usually come from
     * analysis of the schema, although in the JVM versions it will come
     * from reflection of the type definitions.
     *
     * In other words, when encountering a graph of nodes with values, an
     * instance of [Reader] will give a sub tree of that graph's contextual
     * meaning.
     */
    class Reader : public amqp::serialiser::reader::IReader {
        public :
            ~Reader() override = default;

            std::any read (struct pn_data_t *) const override = 0;
            std::string readString (struct pn_data_t *) const override = 0;

            uPtr<amqp::serialiser::reader::IValue> dump(
                const std::string &,
                pn_data_t *,
                const amqp::schema::ISchema &) const override = 0;

            uPtr<amqp::serialiser::reader::IValue> dump(
                pn_data_t *,
                const amqp::schema::ISchema &) const override = 0;
    };

}

/******************************************************************************/
