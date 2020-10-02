#include <iostream>

#include "SerialiseMe.h"

#include "amqp/src/assembler/SerialiserFactoryInternal.h"

/******************************************************************************/

int
main () {
    SerialiseMe sme = SerialiseMe (100, "hello");
    amqp::internal::assembler::SerialiserFactoryInternal sf;

    auto blob = sme.serialise(sf);

    return EXIT_SUCCESS;
}
/******************************************************************************/
