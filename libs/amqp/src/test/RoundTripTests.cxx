
#include <gtest/gtest.h>

#include <list>
#include "serializable/Serializable.h"
#include "src/assembler/SerialiserFactoryInternal.h"

using namespace amqp;
using namespace amqp::serializable;
using namespace amqp::assembler;

/******************************************************************************/

TEST (RTT, single_int) { // NOLINT
    class DeSerialiseMe : public Serializable {
        private :
            int   m_val;

            void serialiseImpl(
                const SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const override {
                sf_.write<int> (m_val, "m_val", *this, blob_);
            }

        public :
            explicit DeSerialiseMe (int val_)
                : Serializable (javaTypeName<decltype(this)>(), "fingerprint123")
                , m_val (val_)
            { }

            explicit DeSerialiseMe (const std::vector<std::any> & l_)
                : Serializable (javaTypeName<decltype(this)>(), "fingerprint123")
                , m_val (std::any_cast<int>(l_[0]))
            { }

            [[maybe_unused]] static std::vector<std::any> deserialiseImpl(
                const SerialiserFactory & sf_,
                const AMQPBlob & blob_
            ) {
                std::vector<std::any> rtn;
                rtn.emplace_back (sf_.read<int> (blob_));
                rtn.emplace_back (sf_.read<int *> (blob_));

                return rtn;
            }

            [[nodiscard]] int val() const { return m_val; }
    };

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    DeSerialiseMe deSerialiseMe(69);

    auto blob = deSerialiseMe.serialise (sf);
    auto b = sf.deserialise<DeSerialiseMe>(*blob);

    ASSERT_EQ(deSerialiseMe.val(), b.val());
}

/******************************************************************************/

TEST (RTT, two_int) { // NOLINT
    class DeSerialiseMe : public Serializable {
            friend class amqp::assembler::SerialiserFactory;
        private :
            int m_val1;
            int m_val2;

            void serialiseImpl(
                const SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const override {
                sf_.write<int> (m_val1, "m_val1", *this, blob_);
                sf_.write<int> (m_val2, "m_val2", *this, blob_);
            }

            explicit DeSerialiseMe (const std::vector<std::any> & l_)
                : Serializable (javaTypeName<decltype(this)>(), "fingerprint123")
                , m_val1 (std::any_cast<int>(l_[0]))
                , m_val2 (std::any_cast<int>(l_[1]))
            { }

            [[maybe_unused]] static std::vector<std::any> deserialiseImpl(
                const SerialiserFactory & sf_,
                const AMQPBlob & blob_
            ) {
                std::vector<std::any> rtn;
                rtn.emplace_back (sf_.read<int> (blob_));
                rtn.emplace_back (sf_.read<int> (blob_));

                return rtn;
            }
        public :
            explicit DeSerialiseMe (int val1_, int val2_)
                : Serializable (javaTypeName<decltype(this)>(), "fingerprint123")
                , m_val1 (val1_)
                , m_val2 (val2_)
            { }

            [[nodiscard]] int val1() const { return m_val1; }
            [[nodiscard]] int val2() const { return m_val2; }
    };

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    DeSerialiseMe deSerialiseMe(1000, 24);

    auto blob = deSerialiseMe.serialise (sf);
    auto b = sf.deserialise<DeSerialiseMe>(*blob);

    ASSERT_EQ(deSerialiseMe.val1(), b.val1());
    ASSERT_EQ(deSerialiseMe.val2(), b.val2());
}

/******************************************************************************/

TEST (RTT, one_int_one_int_ptr) { // NOLINT
    class DeSerialiseMe : public Serializable {
            friend class amqp::assembler::SerialiserFactory;
        private :
            int   m_val1;
            int * m_val2;

            void serialiseImpl(
                const SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const override {
                sf_.write<int> (m_val1, "m_val1", *this, blob_);
                sf_.write<int *> (m_val2, "m_val2", *this, blob_);
            }

            explicit DeSerialiseMe (const std::vector<std::any> & l_)
                : Serializable (javaTypeName<decltype(this)>(), "fingerprint123")
                , m_val1 (std::any_cast<int>(l_[0]))
                , m_val2 { std::any_cast<int *>(l_[1]) }
            { }

            [[maybe_unused]] static std::vector<std::any> deserialiseImpl(
                const SerialiserFactory & sf_,
                const AMQPBlob & blob_
            ) {
                std::vector<std::any> rtn;
                rtn.emplace_back (sf_.read<int> (blob_));
                rtn.emplace_back (sf_.read<int *> (blob_));

                return rtn;
            }
        public :
            explicit DeSerialiseMe (int val1_, int val2_)
                : Serializable (javaTypeName<decltype(this)>(), "fingerprint123")
                , m_val1 (val1_)
                , m_val2 { new int { val2_ } }
            { }

            [[nodiscard]] int val1() const { return m_val1; }
            [[nodiscard]] int val2() const { return *m_val2; }
    };

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    DeSerialiseMe deSerialiseMe(1000, 24);

    auto blob = deSerialiseMe.serialise (sf);
    auto b = sf.deserialise<DeSerialiseMe>(*blob);

    ASSERT_EQ(deSerialiseMe.val1(), b.val1());
    ASSERT_EQ(deSerialiseMe.val2(), b.val2());
}

/******************************************************************************/
