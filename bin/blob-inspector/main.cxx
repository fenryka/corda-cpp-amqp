#include <iostream>

#include <cassert>
#include <sys/stat.h>

#include "include/AMQPConfig.h"
#include "include/CordaBytes.h"
#include "BlobInspector.h"

/******************************************************************************/

int
main (int argc, char **argv) {
    struct stat results { };

    if (argc != 2)  {
        return EXIT_FAILURE;
    }

    if (stat(argv[1], &results) != 0) {
        return EXIT_FAILURE;
    }

    auto config = std::make_unique<amqp::AMQPConfig>();
    config->ignoreHeader = true;

    amqp::CordaBytes cb (argv[1], std::move (config));

    if (cb.encoding() == amqp::DATA_AND_STOP) {
        BlobInspector blobInspector (cb);
        auto val = blobInspector.dump();
        std::cout << val << std::endl;
    } else {
        std::cerr << "BAD ENCODING " << cb.encoding() << " != "
            << amqp::DATA_AND_STOP << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/******************************************************************************/
