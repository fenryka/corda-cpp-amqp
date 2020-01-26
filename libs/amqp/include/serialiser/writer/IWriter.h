#pragma once

/******************************************************************************
 *
 * Forward declarations
 *
 ******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp::serialiser::writer {

    class IWriter {
        public :
            virtual ~IWriter() = default;

            virtual void write (std::any, pn_data_t *) const = 0;
    };

}

/******************************************************************************/
