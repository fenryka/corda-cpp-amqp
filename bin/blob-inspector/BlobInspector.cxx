#include "BlobInspector.h"
#include "include/CordaBytes.h"

#include <iostream>
#include <sstream>

/******************************************************************************/

BlobInspector::BlobInspector (amqp::CordaBytes & cb_)
    : m_blob { cb_ }
{
}

/******************************************************************************/

std::string
BlobInspector::dump() {
    return m_blob.dumpContents();
}

/******************************************************************************/
