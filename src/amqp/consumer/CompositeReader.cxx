#include "CompositeReader.h"

#include <string>
#include <iostream>

#include <proton/codec.h>

#include "proton/proton_wrapper.h"

/******************************************************************************/

const std::string amqp::CompositeReader::m_name = "Composite Reader";

/******************************************************************************/

std::any
amqp::
CompositeReader::read (pn_data_t * data_) const {
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

std::unique_ptr<amqp::Pair>
amqp::
CompositeReader::dump (
    const std::string & name_,
    pn_data_t * data_,
    const std::unique_ptr<internal::schema::Schema> & schema_) const
{
    std::cout << "dump" << std::endl;

    proton::is_described (data_);
    proton::auto_enter ae (data_);

    auto it = schema_->fromDescriptor(proton::get_symbol<std::string>(data_));

    std::cout << "Schema first - " << (*it).first << std::endl;

    auto & clazz = (*it).second;
    auto & fields = clazz->fields();

    assert (fields.size() == m_readers.size());

    std::cout << "Fields size: " << fields.size() << " Reader size: "
        << m_readers.size() << std::endl;

    pn_data_next (data_);

    std::vector<std::unique_ptr<amqp::Pair>> read;
    read.reserve(fields.size());

    proton::is_list (data_);
    {
        proton::auto_enter ae (data_);

        std::cout << data_ << std::endl;

        for (int i (0) ; i < m_readers.size() ; ++i) {
            std::cout << m_readers[i]->name() << " : "
                << fields[i]->name() << std::endl;

            read.emplace_back (
                    m_readers[i]->dump (
                        fields[i]->name(),
                        data_,
                        schema_));
        }
    }

    /*
    return std::make_unique<amqp::TypedPair<std::vector<std::unique_ptr<amqp::Pair>>>>> (
            name_,
            std::move (read));
            */

    return std::make_unique<amqp::TypedPair<int>> (
            name_,
            100);

}

/******************************************************************************/

