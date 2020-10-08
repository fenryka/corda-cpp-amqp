#include <cxxabi.h>
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

    dynamic_cast<ModifiableAMQPBlobImpl &>(blob_).writePrimitive<int &> (
        propertyValue_, propertyName_, clazz_);
}

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::writeIntPtr(
    int * propertyValue_,
    const std::string & propertyName_,
    const amqp::serializable::Serializable & clazz_,
    ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << " - " << clazz_.name() << std::endl); // NOLINT

    dynamic_cast<ModifiableAMQPBlobImpl &>(blob_).writePrimitive<int *> (
        propertyValue_, propertyName_, clazz_);
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

    dynamic_cast<ModifiableAMQPBlobImpl &>(blob_).writePrimitive<std::string &> (
        const_cast<std::string &>(propertyValue_), propertyName_, clazz_);
}

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::writeStringPtr(
    std::string * propertyValue_,
    const std::string & propertyName_,
    const amqp::serializable::Serializable & clazz_,
    ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << " - " << clazz_.name() << std::endl); // NOLINT

    dynamic_cast<ModifiableAMQPBlobImpl &>(blob_).writePrimitive<std::string *> (
        propertyValue_, propertyName_, clazz_);
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
    const std::string & type_,
    const amqp::serializable::Serializable & clazz_,
    const std::string & propertyName_,
    const amqp::serializable::Serializable & parent_,
    ModifiableAMQPBlob & blob_
) const  {
    auto &blob = dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_);

    DBG (__FUNCTION__ << " - " << clazz_.name() << std::endl); // NOLINT

    blob.writeComposite (propertyName_, type_, parent_, clazz_);

    clazz_.serialise (*this, blob_);
}

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::writeCompositePtr (
    const std::string & type_,
    const amqp::serializable::Serializable * clazz_,
    const std::string & propertyName_,
    const amqp::serializable::Serializable & parent_,
    ModifiableAMQPBlob & blob_
) const  {
    DBG (__FUNCTION__ << "::" << type_ << std::endl); // NOLINT

    auto &blob = dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_);

    if (clazz_) {
        DBG (__FUNCTION__ << " - " << clazz_->name() << std::endl); // NOLINT

        blob.writeComposite (type_, propertyName_, parent_, *clazz_);

        clazz_->serialise (*this, blob_);
    } else {

        std::cout << "NULL!!!!!!!!!!!!!!!!" << std::endl;
        int status;
        std::cout << abi::__cxa_demangle (
            typeid(clazz_).name(),
            nullptr,
            nullptr, &status) << std::endl;
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
