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
#include "SchemaDumper.h"

/******************************************************************************/

int
main (int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "ERROR! - usage" << std::endl << "\t./schema-dumper file <mode>" << std::endl;
        return EXIT_FAILURE;
    }

    struct stat results { };

    if (stat (*(argv + 1), &results) != 0) {
        return EXIT_FAILURE;
    }

    amqp::schema::DumpTarget mode;
    auto modeFlag = std::string { *(argv + 2) };
    if (modeFlag == "avro") {
        mode = amqp::schema::DumpTarget::avro;
    } else if (modeFlag == "raw") {
        mode = amqp::schema::DumpTarget::raw;
    } else {
        std::cerr << "ERROR! - usage" << std::endl << "\t./schema-dumper file <mode>" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        amqp::CordaBytes cb(argv[1]);

        if (cb.encoding() == amqp::DATA_AND_STOP) {
            SchemaDumper schemaDumper (cb);
            std::cout << schemaDumper.dump (mode) << std::endl;
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
