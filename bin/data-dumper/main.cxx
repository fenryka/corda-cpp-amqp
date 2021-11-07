#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstddef>

#include <assert.h>
#include <string.h>
#include <proton/types.h>
#include <proton/codec.h>
#include <sys/stat.h>

#include "amqp/include/CordaBytes.h"
#include "DataDumper.h"

/******************************************************************************/

int
main (int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "ERROR! - usage" << std::endl << "\t./data-dumper file" << std::endl;
        return EXIT_FAILURE;
    }

    struct stat results { };

    if (stat (*(argv + 1), &results) != 0) {
        return EXIT_FAILURE;
    }

    try {
        amqp::CordaBytes cb(argv[1], std::make_unique<amqp::AMQPConfig>());

        if (cb.encoding() == amqp::DATA_AND_STOP) {
            DataDumper dataDumper (cb);
            std::cout << dataDumper.dump() << std::endl;
        } else {
            std::cerr << "BAD ENCODING " << cb.encoding() << " != "
                      << amqp::DATA_AND_STOP << std::endl;

            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    } catch (const std::runtime_error & e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

/******************************************************************************/
