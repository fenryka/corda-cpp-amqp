#include <iostream>

#include "DeSerialiseMe.h"

#include "amqp/include/CordaBytes.h"
#include "amqp/include/AMQPBlob.h"

#include "amqp/src/assembler/SerialiserFactoryInternal.h"

/******************************************************************************/

int
main (int argc, [[ maybe_unused ]] char ** argv) {
    if (argc != 2) {
        std::cerr << "ERROR: usage ./reader-test-1 <<filename>>" << std::endl;
        return EXIT_FAILURE;
    }

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    amqp::CordaBytes cb (argv[1], std::make_unique<amqp::AMQPConfig>());
    amqp::AMQPBlob blob (cb);

    auto b = sf.deserialise<DeSerialiseMe>(blob);

    std::cout << b.val() << ", " << b.val2() << std::endl;

    return EXIT_SUCCESS;
}

/******************************************************************************/
