
#include "include/java/security/PublicKeySerialiser.h"

#include <string>
#include <proton/codec.h>

#include "proton-wrapper/include/proton_wrapper.h"
#include "amqp/include/serialiser/reader/IReader.h"
#include "amqp/src/serialiser/serialisers/reader/Reader.h"

/******************************************************************************/

const std::string
java::security::PublicKeySeraliser::m_name { /* NOLINT */
   "Public Key serialiser"
};

const std::string
java::security::PublicKeySeraliser::m_type { /* NOLINT */
    "java.security.PublicKey"
};

/******************************************************************************/

const std::string &
java::security::
PublicKeySeraliser::name() const {
    return m_name;
}

/******************************************************************************/

const std::string &
java::security::
PublicKeySeraliser::type() const  {
    return m_type;
}

/******************************************************************************/

std::any
java::security::
PublicKeySeraliser::read (pn_data_t *) const  {
    return { nullptr };
}

/******************************************************************************/

std::string
java::security::
PublicKeySeraliser::readString (pn_data_t *) const  {
    return "";
}

/******************************************************************************/

std::unique_ptr<amqp::serialiser::reader::IValue>
java::security::
PublicKeySeraliser::dump (
    const std::string & name_,
    pn_data_t * data_,
    const amqp::schema::ISchema &
) const  {
    DBG (__FUNCTION__ << std::endl); // NOLINT
    proton::auto_next an (data_);


    proton::attest_is_described (data_, __FILE__, __LINE__);
    {
        proton::auto_enter ae (data_);
        // skip the fingerprint / symbol
        pn_data_next (data_);

        proton::attest_is_binary (data_, __FILE__, __LINE__);
        [[maybe_unused]]
        auto val = proton::readAndNext<char *> (data_, __FILE__, __LINE__);

        return std::make_unique<amqp::internal::serialiser::reader::TypedPair<std::string>> (
            name_,
            "<<<Public Key>>>");
    }
}

/******************************************************************************/

std::unique_ptr<amqp::serialiser::reader::IValue>
java::security::
PublicKeySeraliser::dump (
    pn_data_t *,
    const amqp::schema::ISchema &
) const  {
    throw std::runtime_error ("NOT IMPLEMENTED");
}

/******************************************************************************/

/*
 * Redeclare the IWriter interface
 */
void
java::security::
PublicKeySeraliser::write (std::any, pn_data_t *) const  {
    throw std::runtime_error ("NOT IMPLEMENTED");
}

/******************************************************************************/
