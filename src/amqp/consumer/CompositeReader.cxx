#include "CompositeReader.h"

#include <string>
#include <iostream>
#include <assert.h>

#include <proton/codec.h>
#include <sstream>
#include "debug.h"
#include "proton/proton_wrapper.h"

/******************************************************************************/

const std::string amqp::CompositeReader::m_name { // NOLINT
    "Composite Reader"
};

/******************************************************************************
 *
 *
 ******************************************************************************/

const std::string &
amqp::
CompositeReader::name() const {
    return m_name;
}

/******************************************************************************/

const std::string &
amqp::
CompositeReader::type() const  {
    return m_type;
}

/******************************************************************************/

std::any
amqp::
CompositeReader::read (pn_data_t * data_) const {
    return std::any(1);
}

/******************************************************************************/

std::string
amqp::
CompositeReader::readString (pn_data_t * data_) const {
    pn_data_next (data_);
    proton::auto_enter ae (data_);

    return "Composite";
}

/******************************************************************************/


std::vector<std::unique_ptr<amqp::Value>>
amqp::
CompositeReader::_dump (
        pn_data_t * data_,
        const std::unique_ptr<amqp::internal::schema::Schema> & schema_
) const {
    DBG ("Read Composite: " << m_name << " : " << type() << std::endl);
    proton::is_described (data_);
    proton::auto_enter ae (data_);

    const auto & it = schema_->fromDescriptor(proton::get_symbol<std::string>(data_));
    auto & fields = dynamic_cast<amqp::internal::schema::Composite *>(it->get())->fields();

    assert (fields.size() == m_readers.size());

    pn_data_next (data_);

    std::vector<std::unique_ptr<amqp::Value>> read;
    read.reserve (fields.size());

    proton::is_list (data_);
    {
        proton::auto_enter ae (data_);

        for (int i (0) ; i < m_readers.size() ; ++i) {
            if (auto l =  m_readers[i].lock()) {
                DBG (fields[i]->name() << " " << (l ? "true" : "false") << std::endl);

                read.emplace_back(l->dump(fields[i]->name(), data_, schema_));
            } else {
                std::stringstream s;
                s << "null field reader: " << fields[i]->name();
                throw std::runtime_error(s.str());
            }
        }
    }

    return read;
}

/******************************************************************************/

std::unique_ptr<amqp::Value>
amqp::
CompositeReader::dump (
    const std::string & name_,
    pn_data_t * data_,
    const std::unique_ptr<internal::schema::Schema> & schema_) const
{

    return std::make_unique<amqp::TypedPair<std::vector<std::unique_ptr<amqp::Value>>>> (
        name_,
        _dump(data_, schema_));
}

/******************************************************************************/

/**
 *
 */
std::unique_ptr<amqp::Value>
amqp::
CompositeReader::dump (
    pn_data_t * data_,
    const std::unique_ptr<internal::schema::Schema> & schema_) const
{

    return std::make_unique<amqp::TypedSingle<std::vector<std::unique_ptr<amqp::Value>>>> (
        _dump (data_, schema_));
}

/******************************************************************************/

