#include <iostream>

#include "SerialiseMe.h"

/******************************************************************************/

int
main () {
    SerialiseMe sme = SerialiseMe (100);
    amqp::assembler::SerialiserFactory sf;

    auto blob = sme.serialize(sf);

    return EXIT_SUCCESS;
}
/******************************************************************************/
