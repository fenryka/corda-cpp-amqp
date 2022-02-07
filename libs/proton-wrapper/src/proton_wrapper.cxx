#include "../include/proton_wrapper.h"

#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <iostream>

#include <proton/types.h>
#include <proton/codec.h>
#include <map>
#include <utility>
#include <cstring>
#include "include/colours.h"

/******************************************************************************/

namespace {

    enum protonTypeTypes {
        COMPLEX,
        PRIMITIVE

    };

    std::map<pn_type_t, std::pair<std::string, protonTypeTypes>> protonToString { // NOLINT
            { PN_NULL, { "null", COMPLEX } },
            { PN_BOOL, { "bool", PRIMITIVE } },
            { PN_UBYTE, { "unsigned byte", PRIMITIVE } },
            { PN_BYTE, { "byte", PRIMITIVE } },
            { PN_USHORT, { "unsigned short", PRIMITIVE } },
            { PN_SHORT, { "short", PRIMITIVE } },
            { PN_UINT, { "unsigned int", PRIMITIVE } },
            { PN_INT, { "int", PRIMITIVE } },
            { PN_CHAR, { "char", PRIMITIVE } },
            { PN_ULONG, { "unsigned long", PRIMITIVE } },
            { PN_LONG, { "long", PRIMITIVE } },
            { PN_TIMESTAMP, { "timestamp", COMPLEX } },
            { PN_FLOAT, { "float", PRIMITIVE } },
            { PN_DOUBLE, { "double", PRIMITIVE } },
            { PN_DECIMAL32, { "decimal-32", PRIMITIVE } },
            { PN_DECIMAL64, { "decimal-64", PRIMITIVE } },
            { PN_DECIMAL128, { "decimal-128", PRIMITIVE } },
            { PN_UUID, { "uuid", PRIMITIVE } },
            { PN_BINARY, { "binary", PRIMITIVE } },
            { PN_STRING, { "string", PRIMITIVE } },
            { PN_SYMBOL, { "symbol", PRIMITIVE } },
            { PN_DESCRIBED, { "described",  COMPLEX } },
            { PN_ARRAY, { "array", COMPLEX } },
            { PN_LIST, { "list", COMPLEX } },
            { PN_MAP, { "map", COMPLEX } },
            { PN_INVALID, { "invalid", COMPLEX } }
    };

}

std::string
proton::typeToString (pn_data_t * data_) {
    return protonToString[pn_data_type (data_)].first;
}

/******************************************************************************/

std::ostream&
operator << (std::ostream& stream, pn_data_t * data_) {
    auto type = pn_data_type (data_);
    stream << std::setw (2) << type << " " <<  pn_type_name (type);

    switch (type) {
        case PN_ULONG :
            {
                stream << " " << pn_data_get_ulong (data_);
                break;
            }
        case PN_LIST :
            {
                stream << " #entries: " << pn_data_get_list (data_);
                break;
            }
        case PN_STRING :
            {
                auto str = pn_data_get_string (data_);

                stream << " " << std::string (str.start, str.size);
                break;
            }
        case PN_INT :
            {
                stream << " " << pn_data_get_int (data_);
                break;
            }
        case PN_BOOL :
            {
                stream << " " << (pn_data_get_bool (data_) ? "true" : "false");
                break;
            }
        case PN_SYMBOL :
            {
                stream << " " << pn_data_get_symbol (data_).size;
                stream << std::endl << "   -> ";
                auto v = pn_data_get_symbol (data_);
                for (size_t i (0) ; i < v.size ; ++i) {
                    stream << *(v.start + i) << " ";
                }
                break;
            }

        default : break;


    }
    return stream;
}

/******************************************************************************/

/**
 * pn_data_enter always places the current pointer before the first node. This
 * is a simple convienience function to avoid having to move to the first
 * element in addition to entering a child.
 */
bool
proton::pn_data_enter(pn_data_t * data_) {
    ::pn_data_enter (data_);
    return pn_data_next (data_);
}

/******************************************************************************/

bool
proton::is_described (pn_data_t * data_) {
    return pn_data_type (data_) == PN_DESCRIBED;
}

/******************************************************************************/

void
proton::is_ulong (pn_data_t * data_) {
    auto t = pn_data_type(data_);
    if (t != PN_ULONG) {
        std::stringstream ss;
        ss << "Expected an unsigned long but received " << pn_type_name (t);
        throw std::runtime_error (ss.str());
    }
}

/******************************************************************************/

[[maybe_unused]]
bool
proton::is_bool (pn_data_t * data_) {
    return pn_data_type (data_) == PN_BOOL;
}

/******************************************************************************/

bool
proton::is_null (pn_data_t * data_) {
    return pn_data_type (data_) == PN_NULL;
}

/******************************************************************************/

void
proton::is_symbol (pn_data_t * data_) {
    if (pn_data_type(data_) != PN_SYMBOL) {
        throw std::runtime_error ("Expected an unsigned long");
    }
}

/******************************************************************************/

void
proton::
attest_is_described (pn_data_t * data_, const std::string & file_, int line_) {
    if (pn_data_type (data_) != PN_DESCRIBED) {
        std::stringstream ss;
        ss << "Expected a Described type, got " << protonToString[pn_data_type (data_)].first
           << ", " << file_ << "::" << line_ << std::endl;

        if (pn_data_type (data_) == PN_INT) {
            std::cerr << __FUNCTION__ << "::" << RED << "not desc is int " << RESET << pn_data_get_int (data_) << std::endl;
        }

        throw std::runtime_error (ss.str());
    }
}

/******************************************************************************/

void
proton::
attest_is_int (pn_data_t * data_, const std::string & file_, int line_) {
    if (pn_data_type (data_) != PN_INT) {
        std::stringstream ss;
        ss << "Expected an Integer type, got " << protonToString[pn_data_type (data_)].first
           << ", " << file_ << "::" << line_ << std::endl;

        throw std::runtime_error (ss.str());
    }
}

/******************************************************************************/

void
proton::
attest_is_binary (pn_data_t * data_, const std::string & file_, int line_) {
    if (pn_data_type (data_) != PN_BINARY) {
        std::stringstream ss;
        ss << "Expected a binary type, got " << protonToString[pn_data_type (data_)].first
           << ", " << file_ << "::" << line_ << std::endl;

        throw std::runtime_error (ss.str());
    }
}

/******************************************************************************/

void
proton::
attest_is_bool (pn_data_t * data_, const std::string & file_, int line_) {
    if (pn_data_type (data_) != PN_BOOL) {
        std::stringstream ss;
        ss << "Expected a boolean type, got " << protonToString[pn_data_type (data_)].first
           << ", " << file_ << "::" << line_ << std::endl;

        throw std::runtime_error (ss.str());
    }
}

/******************************************************************************/

void
proton::
attest_is_float (pn_data_t * data_, const std::string & file_, int line_) {
    if (pn_data_type (data_) != PN_FLOAT) {
        std::stringstream ss;
        ss << "Expected a float type, got " << protonToString[pn_data_type (data_)].first
           << ", " << file_ << "::" << line_ << std::endl;

        throw std::runtime_error (ss.str());
    }
}

/******************************************************************************/

void
proton::
attest_is_long (pn_data_t * data_, const std::string & file_, int line_) {
    if (pn_data_type (data_) != PN_LONG) {
        std::stringstream ss;
        ss << "Expected a long type, got " << protonToString[pn_data_type (data_)].first
           << ", " << file_ << "::" << line_ << std::endl;

        throw std::runtime_error (ss.str());
    }
}

/******************************************************************************/

void
proton::
attest_is_char (pn_data_t * data_, const std::string & file_, int line_) {
    if (pn_data_type (data_) != PN_CHAR) {
        std::stringstream ss;
        ss << "Expected a char type, got " << protonToString[pn_data_type (data_)].first
           << ", " << file_ << "::" << line_ << std::endl;

        throw std::runtime_error (ss.str());
    }
}

/******************************************************************************/

void
proton::
attest_is_double (pn_data_t * data_, const std::string & file_, int line_) {
    if (pn_data_type (data_) != PN_DOUBLE) {
        std::stringstream ss;
        ss << "Expected a double type, got " << protonToString[pn_data_type (data_)].first
           << ", " << file_ << "::" << line_ << std::endl;

        throw std::runtime_error (ss.str());
    }
}

/******************************************************************************/

void
proton::
attest_is_list (pn_data_t * data_, const std::string & file_, int line_) {
    if (pn_data_type(data_) != PN_LIST) {
        std::stringstream ss;

        ss << "Expected a List, got " << protonToString[pn_data_type (data_)].first
            << ", " << file_ << "::" << line_ << std::endl;

        throw std::runtime_error (ss.str());
    } else {
        DBG ("YEP! it's a list" << std::endl);
    }
}

/******************************************************************************/

void
proton::
is_map (pn_data_t * data_, const std::string & file_, int line_) {
    if (pn_data_type(data_) != PN_MAP) {
        std::stringstream ss;

        ss << "Expected a Map, got " << protonToString[pn_data_type (data_)].first
           << ", " << file_ << "::" << line_ << std::endl;

        throw std::runtime_error (ss.str());
    }
}

/******************************************************************************/

[[maybe_unused]] bool
proton::
is_primitive (pn_data_t * data_) {
    return protonToString[pn_data_type(data_)].second == PRIMITIVE;
}

/******************************************************************************/

void
proton::
attest_is_string (pn_data_t * data_, const std::string & file_, int line_, bool allowNull) {
    if (pn_data_type(data_) != PN_STRING) {
        if (allowNull && pn_data_type(data_) != PN_NULL) {
            std::stringstream ss;

            ss << "Expected a String: " << __func__ << ", loc " << file_ << "::" << line_ << std::endl;

            throw std::runtime_error (ss.str());
        }
    }
}

/******************************************************************************/

std::string
proton::get_string (pn_data_t * data_, bool allowNull) {
    if (pn_data_type(data_) == PN_STRING) {
        auto str = pn_data_get_string (data_);
        return { str.start, str.size };
    } else  if (allowNull && pn_data_type (data_) == PN_NULL) {
        return "";
    }

    std::stringstream ss;
    ss << "Expected a String: " << __func__ << std::endl;
    throw std::runtime_error (ss.str());
}

/******************************************************************************/

template<>
std::string
proton::get_symbol<std::string> (pn_data_t * data_) {
    is_symbol (data_);
    auto symbol = pn_data_get_symbol(data_);
    return { symbol.start, symbol.size };
}

template<>
pn_bytes_t
proton::get_symbol (pn_data_t * data_) {
    is_symbol (data_);
    return pn_data_get_symbol (data_);
}

/******************************************************************************/

bool
proton::get_boolean (pn_data_t * data_) {
    if (pn_data_type(data_) == PN_BOOL) {
        return pn_data_get_bool (data_);
    }
    throw std::runtime_error ("Expected a boolean");
}

/******************************************************************************/

[[maybe_unused]]
int
proton::get_int (pn_data_t * data_) {
    if (pn_data_type(data_) == PN_INT) {
        return pn_data_get_int (data_);
    }
    throw std::runtime_error ("Expected an Integer");
}

/******************************************************************************
 *
 * proton::auto_enter
 *
 ******************************************************************************/

proton::
auto_enter::auto_enter (pn_data_t * data_, bool next_)
    : m_data (data_)
{
    proton::pn_data_enter (m_data);
    if (next_) pn_data_next (m_data);
}

/******************************************************************************/

proton::
auto_enter::~auto_enter() {
    pn_data_exit (m_data);
}

/******************************************************************************
 *
 * proton::auto_next
 *
 ******************************************************************************/

proton::
auto_next::auto_next (
    pn_data_t * data_
) : m_data (data_) {
    if (!m_data) {
        throw std::logic_error ("Cannot create Auto Next with null ptr");
    }
}

/******************************************************************************/

proton::
auto_next::~auto_next() {
    pn_data_next (m_data);
}

/******************************************************************************
 *
 * proton::auto_list_enter
 *
 ******************************************************************************/

proton::
auto_list_enter::auto_list_enter (pn_data_t * data_, bool next_)
    : m_elements (pn_data_get_list (data_))
    , m_data (data_)
{
   ::pn_data_enter (m_data);
   if (next_) {
       pn_data_next (m_data);
   }
}

/******************************************************************************/

proton::
auto_list_enter::~auto_list_enter() {
    pn_data_exit (m_data);
}

/******************************************************************************/

size_t
proton::
auto_list_enter::elements() const {
    return m_elements;
}

/******************************************************************************
 *
 * proton::auto_map_enter
 *
 ******************************************************************************/

proton::
auto_map_enter::auto_map_enter (pn_data_t * data_, bool next_)
        : m_elements (pn_data_get_map (data_))
        , m_data (data_)
{
    ::pn_data_enter(m_data);
    if (next_) {
        pn_data_next (m_data);
    }
}

/******************************************************************************/

proton::
auto_map_enter::~auto_map_enter() {
    pn_data_exit (m_data);
}

/******************************************************************************/

size_t
proton::
auto_map_enter::elements() const {
    return m_elements;
}

/******************************************************************************
 *
 *
 *
 ******************************************************************************/

template<>
int32_t
proton::
readAndNext<int32_t> (
    pn_data_t * data_,
    const std::string & file_,
    int,
    bool
) {
    auto_next an (data_);
    return pn_data_get_int (data_);
}

/******************************************************************************/

template<>
int64_t
proton::
readAndNext<int64_t> (
        pn_data_t * data_,
        const std::string & file_,
        int,
        bool
) {
    auto_next an (data_);
    return pn_data_get_long(data_);
}

/******************************************************************************/

template<>
uint32_t
proton::
readAndNext<uint32_t> (
        pn_data_t * data_,
        const std::string & file_,
        int,
        bool
) {
    auto_next an (data_);
    return pn_data_get_uint(data_);
}

/******************************************************************************/

template<>
uint64_t
proton::
readAndNext<uint64_t> (
        pn_data_t * data_,
        const std::string & file_,
        int,
        bool
) {
    auto_next an (data_);
    return pn_data_get_ulong(data_);
}

/******************************************************************************/
template<>
std::string
proton::
readAndNext<std::string> (
    pn_data_t * data_,
    const std::string & file_,
    int line_,
    bool tolerateDeviance_
) {
    std::cout << "STRING" << std::endl;
    auto_next an (data_);

    if (pn_data_type (data_) == PN_STRING) {
        auto str = pn_data_get_string (data_);
        return std::string { str.start, str.size };
    } else if (pn_data_type (data_) == PN_SYMBOL) {
        auto symbol = pn_data_get_symbol (data_);
        return std::string { symbol.start, symbol.size };
    } else  if (tolerateDeviance_ && pn_data_type(data_) == PN_NULL) {
        return "";
    }

    std::stringstream ss;
    ss << "Expected a String but found [" << data_ << "] :: " << file_ << "::" << line_;
    throw std::runtime_error (ss.str());
}

/******************************************************************************/

template<>
bool
proton::
readAndNext<bool> (
    pn_data_t * data_,
    const std::string & file_,
    int,
    bool
) {
    auto_next an (data_);
    return pn_data_get_bool (data_);
}

/******************************************************************************/

template<>
double
proton::
readAndNext<double> (
    pn_data_t * data_,
    const std::string & file_,
    int,
    bool
) {
    auto_next an (data_);
    return pn_data_get_double (data_);
}

/******************************************************************************/

template<>
char *
proton::
readAndNext<char *> (
    pn_data_t * data_,
    const std::string & file_,
    int,
    bool
) {
    auto_next an (data_);

    auto binary = pn_data_get_binary (data_);

    auto rtn = new char[binary.size];
    std::memcpy (rtn, binary.start, binary.size);

    return rtn;
}

/******************************************************************************/

template<>
std::pair<size_t, char *>
proton::
readAndNext<std::pair<size_t, char *>> (
    pn_data_t * data_,
    const std::string & file_,
    int,
    bool
) {
    auto_next an (data_);

    auto binary = pn_data_get_binary (data_);

    auto rtn = new char[binary.size];
    std::memcpy(rtn, binary.start, binary.size);

    return std::make_pair(binary.size, rtn);
}

/******************************************************************************/
