#include "SerialiserFactoryInternal.h"

#include "amqp/include/serializable/Serializable.h"

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::writeInt(
        int propertyValue_,
        const std::string & propertyName_,
        const amqp::serializable::Serializable & clazz_,
        ModifiableAMQPBlob & blob_
) const {
    DBG (__FUNCTION__ << " - " << clazz_.name() << std::endl);

    blob_.writeInt(propertyValue_, propertyName_, clazz_);
}

/******************************************************************************/

void
amqp::internal::assembler::
SerialiserFactoryInternal::writeComposite (
        const amqp::serializable::Serializable & clazz_,
        ModifiableAMQPBlob & blob_
) const  {
    DBG (__FUNCTION__ << " - " << clazz_.name() << std::endl);

    blob_.startComposite (clazz_);
}

/******************************************************************************/

