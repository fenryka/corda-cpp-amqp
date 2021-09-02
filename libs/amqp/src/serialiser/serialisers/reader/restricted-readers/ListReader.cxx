#include "ListReader.h"

#include "amqp/src/serialiser/serialisers/restricted-serialisers/ListSerialiser.h"

#include "proton-wrapper/include/proton_wrapper.h"

/******************************************************************************
 *
 * class ListReader
 *
 ******************************************************************************/

[[maybe_unused]]
amqp::internal::schema::Restricted::RestrictedTypes
amqp::internal::serialiser::reader::
ListReader::restrictedType() {
    return internal::schema::Restricted::RestrictedTypes::list_t;
}

/******************************************************************************/

uPtr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
ListReader::dump (
    const std::string & name_,
    pn_data_t * data_,
    const amqp::schema::ISchema & schema_
) const {
    proton::auto_next an (data_);

    return std::make_unique<TypedPair<sList<uPtr<amqp::serialiser::reader::IValue>>>>(
         name_,
         dump_ (data_, schema_));
}

/******************************************************************************/

uPtr<amqp::serialiser::reader::IValue>
amqp::internal::serialiser::reader::
ListReader::dump(
    pn_data_t * data_,
    const amqp::schema::ISchema & schema_
) const {
    proton::auto_next an (data_);

    return std::make_unique<TypedSingle<sList<uPtr<amqp::serialiser::reader::IValue>>>>(
         dump_ (data_, schema_));
}

/******************************************************************************/

sList<uPtr<amqp::serialiser::reader::IValue>>
amqp::internal::serialiser::reader::
ListReader::dump_(
    pn_data_t * data_,
    const amqp::schema::ISchema & schema_
) const {
    proton::attest_is_described (data_, __FILE__, __LINE__);

    decltype (dump_(data_, schema_)) read;

    {
        proton::auto_enter ae (data_);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused"
        const auto & schema = schema_.fromDescriptor (proton::readAndNext<std::string>(data_, __FILE__, __LINE__));
#pragma clang diagnostic pop

        {
            proton::auto_list_enter ale (data_, true);

            auto reader = dynamic_cast<const amqp::serialiser::ISerialiser *>(this)->serialisers()[0].lock();

            for (size_t i { 0 } ; i < ale.elements() ; ++i) {
                // This feels a bit like a hack... but we do know this is what we actually are so it might be ok
                read.emplace_back (reader->dump (data_, schema_));
            }
        }
    }

    return read;
}

/******************************************************************************/
