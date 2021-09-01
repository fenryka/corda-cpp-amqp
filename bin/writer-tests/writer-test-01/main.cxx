#include <iostream>

#include "DeSerialiseMe.h"

#include "amqp/include/CordaBytes.h"

#include "amqp/src/assembler/SerialiserFactoryInternal.h"

/******************************************************************************/

int
main (int argc, char ** argv) {
    if (argc != 2) {
        std::cerr << "ERROR: usage ./writer-test-1 <<filename>>" << std::endl;
        return EXIT_FAILURE;
    }

    DeSerialiseMe sme = DeSerialiseMe (100);
    amqp::internal::assembler::SerialiserFactoryInternal sf;

    auto blob = sme.serialise (sf);

    amqp::CordaBytes cb (*blob);
    cb.toFile (std::string (argv[1]));

    return EXIT_SUCCESS;
}
/******************************************************************************/