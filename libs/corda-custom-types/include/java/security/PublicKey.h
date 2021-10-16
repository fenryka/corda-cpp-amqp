#pragma once

namespace java::security {

    class PublicKey {
        private :
            [[ maybe_unused ]] char * m_bytes;

        public :
            PublicKey();
    };

}