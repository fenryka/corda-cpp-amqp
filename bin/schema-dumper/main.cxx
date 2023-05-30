#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstddef>

#include <cassert>
#include <proton/types.h>
#include <proton/codec.h>
#include <sys/stat.h>

#include "amqp/include/AMQPConfig.h"
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
        //amqp::CordaBytes cb (std::string (argv[1]), std::make_unique<amqp::AMQPConfig>());
        auto config = std::make_unique<amqp::AMQPConfig>();
        config->ignoreHeader = true;
        amqp::CordaBytes cb (std::string (argv[1]), std::move(config));

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
