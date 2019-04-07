#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstddef>

#include <proton/types.h>
#include <proton/codec.h>
#include <sys/stat.h>

#include "proton_wrapper.h"

#include "amqp_header.h"
#include "amqp_section_id.h"
#include "AMQPDescriptorRegistory.h"

/******************************************************************************/

void
data_and_stop(std::ifstream & f_, size_t sz) {
    char * blob = new char[sz];
    memset (blob, 0, sz);
    f_.read(blob, sz);

    pn_data_t * d = pn_data(sz);

    auto rtn = pn_data_decode (d, blob, sz);

    std::cout << "rtn - " << rtn << std::endl;
    std::cout << d << std::endl;

    if (pn_data_is_described(d)) {
        proton::auto_enter p (d);

        auto a = pn_data_get_ulong(d);

        amqp::AMQPDescriptorRegistory[a]->build(d);


    }

}

/******************************************************************************/

int
main (int argc, char **argv) {
    std::cout << "File = " << argv[1] << std::endl;
    struct stat results;

    if (stat(argv[1], &results) == 0) {
        std::cout << "size = " << results.st_size << std::endl;
        // The size of the file in bytes is in
        // results.st_size
    } else {
        return EXIT_FAILURE;
    }

    std::ifstream f (argv[1], std::ios::in | std::ios::binary);
    f.seekg(0);
    std::array<char, 7> header;
    f.read(header.data(), 7);

    if (header == AMQP_HEADER) {
        std::cout << "YES" << std::endl;
    }

    amqp_section_id_t encoding;
    f.read((char *)&encoding, 1);
    std::cout << "encoding = " << encoding << std::endl;

    if (encoding == DATA_AND_STOP) {
        data_and_stop(f, results.st_size - 8);
    }



    /*
    f.read((char *)&z, sizeof (z));
    //z = __builtin_bswap64(z);
    std::cout << "z = " << (int)z << " " << std::hex << (int)z << std::dec << std::endl;

    f.read((char *)&z, sizeof (z));
    //z = __builtin_bswap64(z);
    std::cout << "z = " << (int)z << " " << std::hex << (int)z << std::dec << std::endl;

    unsigned long l = 0;
    f.read(reinterpret_cast<char *>(&l), sizeof (l));
    std::cout << "L = " << l << " " << std::hex << l << std::dec << " " << std::endl;;

    std::cout << "swap L = " << __builtin_bswap64(l) << std::endl;
    */



    //proton::message m;
    //


    /*


    for (int i(0) ; i < 50 ; ++i) {
        int x;
        f.read((char *)&x, sizeof (int));
        std::cout << std::setfill(' ') << std::setw(12) << x << "  #  ";
        std::cout << "'" << *(char *)&x << "' ";
        std::cout << "'" << *((char *)&x + 1) << "' ";
        std::cout << "'" << *((char *)&x + 2) << "' ";
        std::cout << "'" << *((char *)&x + 3) << "'" << "  #  ";
        std::cout << (int)*(char *)&x << " ";
        std::cout << (int)*((char *)&x + 1) << " ";
        std::cout << (int)*((char *)&x + 2) << " ";
        std::cout << (int)*((char *)&x + 3) << " " << std::endl;
    }
    */
}

/******************************************************************************/

