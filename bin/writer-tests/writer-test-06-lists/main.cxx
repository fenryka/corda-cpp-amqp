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

    std::vector<std::string> l = {
        "goodbye",
        "cruel",
        "world"
    };
    ContainsList cl (l);

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    auto blob = cl.serialise (sf);

    amqp::CordaBytes cb (*blob, std::make_unique<amqp::AMQPConfig>());
    cb.toFile (std::string (argv[1]));

    return EXIT_SUCCESS;
}

/******************************************************************************/
