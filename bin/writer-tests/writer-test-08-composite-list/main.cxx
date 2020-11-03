#include <iostream>

#include "SerialiseMe.h"

#include "amqp/include/CordaBytes.h"

#include "amqp/src/assembler/SerialiserFactoryInternal.h"

/******************************************************************************/

int
main (int argc, char ** argv) {
    if (argc != 2) {
        std::cerr << "ERROR: usage ./writer-test-06 <<filename>>" << std::endl;
        return EXIT_FAILURE;
    }

    Composite c1 ("1", 2.3);
    Composite c2 ("4", 5.6);
    Composite c3 ("7", 8.9);

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    CompositeList cl ({c1, c2, c3});

    auto blob = cl.serialise (sf);

    amqp::CordaBytes cb (*blob);
    cb.toFile (std::string (argv[1]));

    return EXIT_SUCCESS;
}

/******************************************************************************/
