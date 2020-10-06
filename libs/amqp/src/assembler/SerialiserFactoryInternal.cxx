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
SerialiserFactoryInternal::writeInt(
        int propertyValue_,
        const std::string & propertyName_,
        const amqp::serializable::Serializable & clazz_,
        ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << " - " << clazz_.name() << std::endl); // NOLINT

    dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).writePrimitive<int> (propertyValue_, propertyName_, clazz_);
}

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::writeString(
    const std::string & propertyValue_,
    const std::string & propertyName_,
    const amqp::serializable::Serializable & clazz_,
    ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << " - " << clazz_.name() << std::endl); // NOLINT

    dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).writePrimitive<std::string> (propertyValue_, propertyName_, clazz_);
}

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::writeLong(
    long propertyValue_,
    const std::string & propertyName_,
    const amqp::serializable::Serializable & clazz_,
    ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << " - " << clazz_.name() << std::endl); // NOLINT

//    blob_.writeLong (propertyValue_, propertyName_, clazz_);
}

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::writeBool (
    bool propertyValue_,
    const std::string & propertyName_,
    const amqp::serializable::Serializable & clazz_,
    ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << " - " << clazz_.name() << std::endl); // NOLINT

//    blob_.writeBool (propertyValue_, propertyName_, clazz_);
}

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::writeComposite (
    const amqp::serializable::Serializable & clazz_,
    ModifiableAMQPBlob & blob_
) const  {
    DBG (__FUNCTION__ << " - " << clazz_.name() << std::endl); // NOLINT

    dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).startComposite (clazz_);
    dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).writeComposite (clazz_);
    clazz_.serialise (*this, blob_);
}

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::startComposite (
    const amqp::serializable::Serializable & clazz_,
    ModifiableAMQPBlob & blob_
) const  {
    DBG (__FUNCTION__ << " - " << clazz_.name() << std::endl); // NOLINT

    dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).startComposite (clazz_);
}

/******************************************************************************/
