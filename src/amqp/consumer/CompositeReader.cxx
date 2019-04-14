#include "CompositeReader.h"

#include <string>
#include <iostream>

#include <proton/codec.h>

#include "proton/proton_wrapper.h"

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

std::string
amqp::
CompositeReader::dump (
    pn_data_t * data_,
    const std::unique_ptr<internal::schema::Schema> & schema_) const
{
    proton::is_described (data_);
    {
        proton::auto_enter ae (data_);

        auto it = schema_->fromDescriptor(proton::get_symbol<std::string>(data_));
        auto & clazz = (*it).second;
        auto & fields = clazz->fields();

        pn_data_next (data_);

        proton::is_list (data_);
        {
            proton::auto_enter ae (data_);
            std::cout << fields[0]->name() << " : " << m_readers[0]->readString (data_) << std::endl;
        }

    }


    return "hello";
}

/******************************************************************************/

