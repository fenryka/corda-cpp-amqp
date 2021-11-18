#include <iostream>

#include "DeSerialiseMe.h"

#include "amqp/include/CordaBytes.h"
#include "amqp/include/AMQPBlob.h"

#include "amqp/src/assembler/SerialiserFactoryInternal.h"

/******************************************************************************/

int
main (int argc, [[ maybe_unused ]] char ** argv) {
    if (argc != 1) {
        return EXIT_FAILURE;
    }

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    auto blob = DeSerialiseMe({1, 2, 3, 4}).serialise (sf);
    amqp::CordaBytes cb (*blob, std::make_unique<amqp::AMQPConfig>());
    cb.toFile ("serialized.bin");

    auto b = sf.deserialise<DeSerialiseMe>(*blob);

    return EXIT_SUCCESS;
}

/******************************************************************************/
