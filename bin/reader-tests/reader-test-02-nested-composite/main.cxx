#include <iostream>

#include "DeSerialiseMe.h"

#include "amqp/include/CordaBytes.h"
#include "amqp/include/AMQPBlob.h"

#include "amqp/src/assembler/SerialiserFactoryInternal.h"

/******************************************************************************/

int
main (int argc, char ** argv) {
    if (argc != 1) {
        return EXIT_FAILURE;
    }

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    auto blob = Outer(100).serialise (sf);
    amqp::CordaBytes cb (*blob, std::make_unique<amqp::AMQPConfig>());
    cb.toFile ("serialized.bin");

    DBG ("\n\nDESERIALISE\n\n");

    auto o2 = sf.deserialise<Outer> (*blob);

    std::cout << o2.name() << ":: " << o2.a().val() << std::endl;

    return EXIT_SUCCESS;
}

/******************************************************************************/
