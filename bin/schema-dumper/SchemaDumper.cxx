#include "SchemaDumper.h"

/******************************************************************************/

SchemaDumper::SchemaDumper (amqp::CordaBytes & cb_)
    : m_blob { cb_ }
{
}

/******************************************************************************/

std::string
SchemaDumper::dump (amqp::schema::DumpTarget target_) {
    return m_blob.dumpSchema (target_);
}

/******************************************************************************/
