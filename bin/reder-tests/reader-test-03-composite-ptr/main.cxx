#include <iostream>

#include "DeSerialiseMe.h"

#include "amqp/include/CordaBytes.h"
#include "amqp/include/AMQPBlob.h"

#include "amqp/src/assembler/SerialiserFactoryInternal.h"

/******************************************************************************/

int
main (
    int argc,
    [[maybe_unused]] char ** argv
) {
    if (argc != 1) {
        return EXIT_FAILURE;
    }

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    auto blob = Outer().serialise (sf);
    amqp::CordaBytes cb (*blob);
    cb.toFile ("serialized.bin");

    DBG ("\n\nDESERIALISE\n\n");

    auto o2 = sf.deserialise<Outer> (*blob);

    return EXIT_SUCCESS;
}

/******************************************************************************/
