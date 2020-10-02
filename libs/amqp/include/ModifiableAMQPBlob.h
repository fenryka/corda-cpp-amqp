#include "AMQPBlob.h"

namespace amqp {

    class ModifiableAMQPBlob : public AMQPBlob {
        private :
            pn_data_t * payload;
            pn_data_t * schema;
        public :
            ModifiableAMQPBlob();


    };

    ModifiableAMQPBlob::ModifiableAMQPBlob() {

    }

}