#include "SerialiserFactoryInternal.h"

#include "amqp/include/serializable/Serializable.h"
#include "amqp/include/ModifiableAMQPBlob.h"
#include "amqp/src/ModifiableAMQPBlobImpl.h"

/******************************************************************************/

uPtr<amqp::ModifiableAMQPBlob>
amqp::internal::assembler::
SerialiserFactoryInternal::blob() const  {
    return std::make_unique<amqp::internal::ModifiableAMQPBlobImpl>();
}

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::writeComposite_ (
    const std::string & type_,
    const amqp::serializable::Serializable * clazz_,
    const std::string & propertyName_,
    const amqp::serializable::Serializable & parent_,
    ModifiableAMQPBlob & blob_
) const  {
    DBG (__FUNCTION__ << "::" << type_ << std::endl); // NOLINT

    auto &blob = dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_);

    blob.writeComposite_ (propertyName_, type_, parent_);

    if (clazz_) {
        DBG (__FUNCTION__ << " - " << clazz_->name() << std::endl); // NOLINT

        clazz_->serialise (*this, blob_);
    } else {
        blob.writeNull (propertyName_, type_, parent_);
    }
}

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::startComposite (
    const amqp::serializable::Serializable & clazz_,
    ModifiableAMQPBlob & blob_
) const  {
    DBG (__FUNCTION__ << " - " << clazz_.name() << std::endl); // NOLINT

    auto & blob = dynamic_cast<ModifiableAMQPBlobImpl &>(blob_);

    blob.dump();

    blob.startComposite (clazz_);
}

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::startRestricted (
    const amqp::serializable::Serializable & clazz_,
    ModifiableAMQPBlob & blob_
) const  {
    DBG (__FUNCTION__ << " - " << clazz_.name() << std::endl); // NOLINT
    auto & blob = dynamic_cast<ModifiableAMQPBlobImpl &>(blob_);

    blob.dump();

    blob.startRestricted (clazz_);
}

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::writeRestricted_ (
    const std::string & type_,
    const amqp::serializable::Serializable * clazz_,
    const std::string & propertyName_,
    const amqp::serializable::Serializable & parent_,
    ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << "::" << type_ << std::endl);

    auto & blob = dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_);

    blob.writeRestricted_ (propertyName_, type_, parent_);

    clazz_->serialise (*this, blob_);
}

/******************************************************************************/

