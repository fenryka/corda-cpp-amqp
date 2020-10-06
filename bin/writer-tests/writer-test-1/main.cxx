#include <iostream>

#include "SerialiseMe.h"

#include "amqp/include/CordaBytes.h"

#include "amqp/src/assembler/SerialiserFactoryInternal.h"

/******************************************************************************/

int
main () {
    SerialiseMe sme = SerialiseMe (100);
    amqp::internal::assembler::SerialiserFactoryInternal sf;

    auto blob = sme.serialise (sf);

    amqp::CordaBytes cb (*blob);
    cb.toFile ("./blob");

    return EXIT_SUCCESS;
}
/******************************************************************************/
