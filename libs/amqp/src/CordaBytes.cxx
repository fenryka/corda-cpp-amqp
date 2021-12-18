#include "CordaBytes.h"

#include <array>
#include <cstring>
#include <sys/stat.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <proton/codec.h>

#include "AMQPBlob.h"
#include "AMQPHeader.h"

#include "include/AMQPConfig.h"
#include "corda-utils/include/debug.h"

/******************************************************************************/

amqp::
CordaBytes::CordaBytes (const std::string & file_, uPtr<AMQPConfig> config_)
    : m_blob { nullptr }
    , m_config { std::move (config_) }
    , m_header { m_config->header }
{
    std::ifstream file { file_, std::ios::in | std::ios::binary };
    struct stat results { };

    if (::stat (file_.c_str(), &results) != 0) {
        throw std::runtime_error ("Not a file");
    }

    // Disregard the Corda header
    m_size = results.st_size - (amqp::AMQP_HEADERS[m_header].size() + 1);

    // Read the header, ignore encoding
    std::array<char, 7> header { };
    file.read (header.data(), 7);

#ifdef SRC_DEBUG
    for (int i { 0 } ; i < 7 ; ++i) {
        std::cout << header[i] << " " << static_cast<int>(header[i]) << std::endl;
    }
#endif

    if (std::find (amqp::AMQP_HEADERS.begin(), amqp::AMQP_HEADERS.end(), header) == amqp::AMQP_HEADERS.end()) {
        if (!m_config->ignoreHeader) {
            throw std::runtime_error ("Not a Corda stream");
        } else {
            std::cerr << "Bad Header: ";
            std::copy(header.begin(), header.end(),
                      std::ostream_iterator<int>(std::cerr, " "));
            std::cerr << std::endl;
        }
    }

    // grab the encoding flag. This could / should be done with the above
    // to avoid two writes but at the moment performance isn't an issue
    // and this makes the code a little cleaner
    char encoding;
    file.read (&encoding, 1);

    m_encoding = static_cast<amqp::amqp_section_id_t> (encoding);
    switch (m_encoding) {
        case amqp::amqp_section_id_t::ALT_DATA_AND_STOP :
        case amqp::amqp_section_id_t::DATA_AND_STOP :
        case amqp::amqp_section_id_t::ENCODING :
            break;
        default : {
            throw std::runtime_error ("Unknown encoding encountered");
        }
    }

    m_blob = new char[m_size];

    memset (m_blob, 0, m_size);
    file.read (m_blob, m_size);
}

/******************************************************************************/

amqp::
CordaBytes::CordaBytes (const AMQPBlob & bytes_, uPtr<AMQPConfig> config_)
    : m_encoding (DATA_AND_STOP)
    , m_config { std::move (config_) }
    , m_header { -1 }
{
    m_size = pn_data_encoded_size (bytes_.data());
    m_blob = new char[m_size];
    pn_data_encode (bytes_.data(), m_blob, m_size);
}

/******************************************************************************/

void
amqp::
CordaBytes::toFile (const std::string & fileName_) const {
    DBG (__FUNCTION__ << " - " << fileName_ << std::endl); // NOLINT

    std::ofstream file { fileName_, std::ios::out | std::ios::binary };
    file.write (amqp::AMQP_HEADERS[amqp::header::AMQP_DEFAULT].data(), 7);
    char encoding = 0;
    file.write(&encoding, sizeof (encoding));
    file.write (m_blob, static_cast<std::streamsize>(m_size));
}

/******************************************************************************/
