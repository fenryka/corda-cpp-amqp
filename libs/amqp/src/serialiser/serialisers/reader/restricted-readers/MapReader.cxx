#include "MapReader.h"

#include <cassert>

#include "serialisers/reader/Reader.h"
#include "serialiser/reader/IReader.h"
#include "proton-wrapper/include/proton_wrapper.h"

#include "amqp/src/serialiser/serialisers/restricted-serialisers/MapSerialiser.h"

/******************************************************************************/

amqp::internal::schema::Restricted::RestrictedTypes
amqp::internal::serialiser::reader::
MapReader::restrictedType() {
    return schema::Restricted::Restricted::map_t;
}

/******************************************************************************/

sVec<uPtr<amqp::serialiser::reader::IValue>>
amqp::internal::serialiser::reader::
MapReader::dump_(
    pn_data_t * data_,
    const amqp::schema::ISchema & schema_
) const {
    proton::attest_is_described (data_, __FILE__, __LINE__);
    proton::auto_enter ae (data_);

    // gloss over fetching the descriptor from the schema since
    // we don't need it, we know the types this is a reader for
    // and don't need context from the schema as there isn't
    // any. Maps have a Key and a Value, they aren't named
    // parameters, unlike composite types.
    schema_.fromDescriptor (proton::readAndNext<std::string>(data_, __FILE__, __LINE__));

    {
        proton::auto_map_enter am (data_, true);

        decltype (dump_(data_, schema_)) rtn;
        rtn.reserve (am.elements() / 2);

        auto serialisers = (dynamic_cast<const amqp::serialiser::ISerialiser *>(this))->serialisers();

        assert (serialisers.size() == 2);

        auto keyReader = serialisers[0].lock();
        auto valueReader = serialisers[1].lock();

        for (int i {0} ; i < am.elements() ; i += 2) {
            rtn.emplace_back (
                std::make_unique<ValuePair> (
                    keyReader->dump (data_, schema_),
                    valueReader->dump (data_, schema_)
                )
            );
        }

        return rtn;
    }
}

/******************************************************************************/

uPtr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
MapReader::dump(
        const std::string & name_,
        pn_data_t * data_,
        const amqp::schema::ISchema & schema_
) const {
    DBG ("MapReader::dump " << name_ << std::endl);
    proton::auto_next an (data_);

    return std::make_unique<TypedPair<sVec<uPtr<amqp::serialiser::reader::IValue>>>>(
            name_,
            dump_ (data_, schema_));
}

/******************************************************************************/

std::unique_ptr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
MapReader::dump(
        pn_data_t * data_,
        const amqp::schema::ISchema & schema_
) const  {
    DBG ("MapReader::dump no-name" << std::endl);

    proton::auto_next an (data_);

    return std::make_unique<TypedSingle<sVec<uPtr<amqp::serialiser::reader::IValue>>>>(
            dump_ (data_, schema_));
}

/******************************************************************************/
