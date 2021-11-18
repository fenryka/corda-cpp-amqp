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

    amqp::serializable::SerializableVector<int> l1 { 1, 2, 3};
    amqp::serializable::SerializableVector<int> l2 { 4, 5, 6};
    amqp::serializable::SerializableVector<int> l3 { 7, 8, 9};

    amqp::serializable::SerializableVector<
        amqp::serializable::SerializableVector<int>> l4 { l1, l2, l3 };

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    ListOfLists lol (l4);

    auto blob = lol.serialise (sf);

    amqp::CordaBytes cb (*blob, std::make_unique<amqp::AMQPConfig>());
    cb.toFile (std::string (argv[1]));

    return EXIT_SUCCESS;
}

/******************************************************************************/
