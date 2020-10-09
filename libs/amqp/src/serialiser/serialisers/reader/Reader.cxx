#include "Reader.h"

#include <memory>
#include <sstream>

/******************************************************************************/

namespace {

    struct AutoMap {
        std::stringstream & m_stream;

        AutoMap (
                const std::string & s,
                std::stringstream & stream_
        ) : m_stream (stream_) {
            m_stream << s << " : { ";
        }

        explicit AutoMap (std::stringstream & stream_)
            : m_stream (stream_)
        {
            m_stream << "{ ";
        }

        ~AutoMap() {
            m_stream << " }";
        }
    };

    struct AutoList {
        std::stringstream & m_stream;

        AutoList (
                const std::string & s,
                std::stringstream & stream_
        ) : m_stream (stream_) {
            m_stream << s << " : [ ";
        }

        explicit AutoList (std::stringstream & stream_)
            : m_stream (stream_)
        {
            m_stream << "[ ";
        }

        ~AutoList() {
            m_stream << " ]";
        }
    };

    template<class Auto, class T>
    std::string
    dumpPair (const std::string & name_, const T & begin_, const T & end_) {
        std::stringstream rtn;
        {
            Auto am (name_, rtn);

            if (begin_ != end_) {
                rtn << (*(begin_))->dump();
                for (auto it(std::next(begin_)); it != end_; ++it) {
                    rtn << ", " << (*it)->dump();
                }
            }
        }

        return rtn.str();
    }

    template<class Auto, class T>
    std::string
    dumpSingle (const T & begin_, const T & end_) {
        std::stringstream rtn;
        {
            Auto am (rtn);

            if (begin_ != end_) {
                rtn << (*(begin_))->dump();
                for (auto it(std::next(begin_)); it != end_; ++it) {
                    rtn << ", " << (*it)->dump();
                }
            }
        }

        return rtn.str();
    }

}

/******************************************************************************
 *
 * amqp::internal::serialiser::reader::TypedValuePair
 *
 ******************************************************************************/

std::string
amqp::internal::serialiser::reader::
ValuePair::dump() const {
    std::stringstream ss;

    ss << m_key->dump() << " : " << m_value->dump();

    return ss.str();
}

/******************************************************************************
 *
 * amqp::internal::serialiser::reader::TypedPair
 *
 ******************************************************************************/

template<>
std::string
amqp::internal::serialiser::reader::
TypedPair<sVec<uPtr<amqp::internal::serialiser::reader::Pair>>>::dump() const {
    return ::dumpPair<AutoMap> (m_property, m_value.begin(), m_value.end());
}

template<>
std::string
amqp::internal::serialiser::reader::
TypedPair<sList<uPtr<amqp::internal::serialiser::reader::Pair>>>::dump() const {
    return ::dumpPair<AutoMap> (m_property, m_value.begin(), m_value.end());
}

template<>
std::string
amqp::internal::serialiser::reader::
TypedPair<sVec<uPtr<amqp::serialiser::reader::IValue>>>::dump() const {
    return ::dumpPair<AutoMap> (m_property, m_value.begin(), m_value.end());
}

template<>
std::string
amqp::internal::serialiser::reader::
TypedPair<sList<uPtr<amqp::serialiser::reader::IValue>>>::dump() const {
    return ::dumpPair<AutoList> (m_property, m_value.begin(), m_value.end());
}

/******************************************************************************
 *
 * amqp::internal::serialiser::reader::NullValuePair
 *
 ******************************************************************************/

std::string
amqp::internal::serialiser::reader::
NullTypedPair::dump() const {
    return m_property + " : <<NULL>>";
}

/******************************************************************************
 *
 * amqp::internal::serialiser::reader::NullValueSingle
 *
 ******************************************************************************/

std::string
amqp::internal::serialiser::reader::
NullTypedSingle::dump() const {
    return "<<NULL>>";
}

/******************************************************************************
 *
 * amqp::internal::serialiser::reader::TypedSingle specialisations
 *
 ******************************************************************************/

template<>
std::string
amqp::internal::serialiser::reader::
TypedSingle<sList<uPtr<amqp::serialiser::reader::IValue>>>::dump() const {
    return ::dumpSingle<AutoList> (m_value.begin(), m_value.end());
}

template<>
std::string
amqp::internal::serialiser::reader::
TypedSingle<sVec<uPtr<amqp::serialiser::reader::IValue>>>::dump() const {
    return ::dumpSingle<AutoMap> (m_value.begin(), m_value.end());
}

template<>
std::string
amqp::internal::serialiser::reader::
TypedSingle<sList<uPtr<amqp::internal::serialiser::reader::Single>>>::dump() const {
    return ::dumpSingle<AutoList> (m_value.begin(), m_value.end());
}

template<>
std::string
amqp::internal::serialiser::reader::
TypedSingle<sVec<uPtr<amqp::internal::serialiser::reader::Single>>>::dump() const {
    return ::dumpSingle<AutoMap> (m_value.begin(), m_value.end());
}

/******************************************************************************/
