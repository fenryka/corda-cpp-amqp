#include <iostream>

#include "DeSerialiseMe.h"

#include "amqp/include/CordaBytes.h"
#include "amqp/include/AMQPBlob.h"

#include "amqp/src/assembler/SerialiserFactoryInternal.h"

/******************************************************************************/

int
main (
    int argc,
    [[ maybe_unused ]] char ** argv
) {
    if (argc != 1) {
        return EXIT_FAILURE;
    }

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    auto blob = Outer(100, 200, 300, 400, 500, 600).serialise (sf);
    amqp::CordaBytes cb (*blob, std::make_unique<amqp::AMQPConfig>());
    cb.toFile ("serialized.bin");

    DBG ("\n\nDESERIALISE\n\n"); // NOLINT

    auto o2 = sf.deserialise<Outer> (*blob);

    std::cout << o2.name() << ":: " << std::endl
        << "  " << o2.a().m_val1 << std::endl
        << "  " << o2.a().m_val2 << std::endl
        << "  " << o2.a().m_val3 << std::endl
        << "  " << o2.a().m_val4 << std::endl
        << "  " << o2.a().m_val5 << std::endl
        << "  " << o2.a().m_val6 << std::endl;


    return EXIT_SUCCESS;
}

/******************************************************************************/
