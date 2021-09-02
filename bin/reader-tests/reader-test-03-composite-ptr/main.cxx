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

    std::cout << o2.a().v1() << " " << o2.a().v2() << " " << o2.b()->v1() << " " << o2.b()->v2() << std::endl;

    return EXIT_SUCCESS;
}

/******************************************************************************/
