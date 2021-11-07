
#include <gtest/gtest.h>

#include <list>
#include <vector>
#include "serializable/Serializable.h"
#include "serializable/SerializableVector.h"
#include "src/assembler/SerialiserFactoryInternal.h"

/******************************************************************************/

using namespace amqp;
using namespace amqp::serializable;
using namespace amqp::assembler;

/******************************************************************************/

namespace {

    template<typename T>
    class RTTSingle : public Serializable {
        friend class amqp::assembler::SerialiserFactory;
    private :
        T m_val;

        void serialiseImpl(
                const SerialiserFactory &sf_,
                ModifiableAMQPBlob &blob_
        ) const override {
            sf_.write<T>(m_val, "m_val", *this, blob_);
        }

    public :
        [[ maybe_unused ]] explicit RTTSingle(T val_)
                : Serializable(javaTypeName<decltype(this)>(), "fingerprint123"), m_val(val_) {}

        [[ maybe_unused ]] explicit RTTSingle(const std::vector<std::any> &l_)
                : Serializable(javaTypeName<decltype(this)>(), "fingerprint123"), m_val(std::any_cast<T>(l_[0])) {}

        [[ maybe_unused ]] static std::vector<std::any> deserialiseImpl(
                const SerialiserFactory &sf_,
                const AMQPBlob &blob_
        ) {
            std::vector<std::any> rtn;
            rtn.emplace_back(sf_.read<T>(blob_));

            return rtn;
        }

        [[nodiscard]] T val() const { return m_val; }
    };
}

/******************************************************************************/

namespace {

    template<typename T1, typename T2>
    class RTTDouble : public Serializable {
            friend class amqp::assembler::SerialiserFactory;
        private :
            T1 m_val1;
            T2 m_val2;

            void serialiseImpl(
                const SerialiserFactory &sf_,
                ModifiableAMQPBlob &blob_
            ) const override {
                sf_.write<T1>(m_val1, "m_val1", *this, blob_);
                sf_.write<T2>(m_val2, "m_val2", *this, blob_);
            }

        public :
            [[ maybe_unused ]] explicit RTTDouble(T1 val1_, T2 val2_)
                : Serializable(javaTypeName<decltype(this)>(), "fingerprint123")
                , m_val1(val1_)
                , m_val2 (val2_)
            { }

            [[ maybe_unused ]] explicit RTTDouble(const std::vector<std::any> &l_)
                : Serializable(javaTypeName<decltype(this)>(), "fingerprint123")
                , m_val1(std::any_cast<T1>(l_[0]))
                , m_val2(std::any_cast<T2>(l_[1])) {}

            [[ maybe_unused ]] static std::vector<std::any> deserialiseImpl(
                const SerialiserFactory &sf_,
                const AMQPBlob &blob_
            ) {
                std::vector<std::any> rtn;
                rtn.emplace_back (sf_.read<T1>(blob_));
                rtn.emplace_back (sf_.read<T2>(blob_));

                return rtn;
            }

            [[nodiscard]] T1 val1() const { return m_val1; }
            [[nodiscard]] T2 val2() const { return m_val2; }
    };
}

/******************************************************************************/

template<typename T>
void
singleTest(
    amqp::internal::assembler::SerialiserFactoryInternal & sfi_,
    T val_
) {
    typedef RTTSingle<T> Single;
    Single deSerialiseMe (val_);

    auto blob = deSerialiseMe.serialise (sfi_);
    auto b = sfi_.deserialise<Single> (*blob);

    ASSERT_EQ(deSerialiseMe.val (), b.val ());
}

/******************************************************************************/

TEST (RTT, singles) { // NOLINT
    amqp::internal::assembler::SerialiserFactoryInternal sf;

    singleTest<int> (sf, 69);
    singleTest<float> (sf, 69.6969);
    singleTest<double> (sf, 100);
    singleTest<long> (sf, 400);
    singleTest<std::string> (sf, "This is a test");
    singleTest<bool> (sf, true);
    singleTest<char> (sf, 'a');
}

/******************************************************************************/

template<typename T1, typename T2>
void
doubleTest(
    amqp::internal::assembler::SerialiserFactoryInternal & sfi_,
    T1 val1_,
    T2 val2_
) {
    typedef RTTDouble<T1, T2> Double;
    Double deSerialiseMe (val1_, val2_);

    auto blob = deSerialiseMe.serialise (sfi_);
    auto b = sfi_.deserialise<Double> (*blob);

    ASSERT_EQ(deSerialiseMe.val1 (), b.val1 ());
    ASSERT_EQ(deSerialiseMe.val2 (), b.val2 ());
}

/******************************************************************************/

TEST (RTT, Doubles) { // NOLINT
    amqp::internal::assembler::SerialiserFactoryInternal sf;

    doubleTest<int, int> (sf, 69, 1098);
    doubleTest<float, int> (sf, 69.6969, 102);
    doubleTest<double, int> (sf, 100, 103);
    doubleTest<long, int> (sf, 400, 30);
    doubleTest<std::string, int> (sf, "This is a test", 30);
    doubleTest<bool, int> (sf, true, 1);
    doubleTest<char, int> (sf, 'a', 909);
}

/******************************************************************************/

TEST (RTT, many_types) { // NOLINT
    class DeSerialiseMe : public Serializable {
        friend class amqp::assembler::SerialiserFactory;
    private :
        int           m_val1;
        double        m_val2;
        long          m_val3;
        std::string   m_val4;
        std::string * m_val5;

        void serialiseImpl(
                const SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
        ) const override {
            sf_.write<int> (m_val1, "m_val1", *this, blob_);
            sf_.write<double> (m_val2, "m_val2", *this, blob_);
            sf_.write<long> (m_val3, "m_val3", *this, blob_);
            sf_.write<std::string> (m_val4, "m_val4", *this, blob_);
            sf_.write<std::string *> (m_val5, "m_val5", *this, blob_);
        }


        public :
            explicit DeSerialiseMe (int val1_, double val2_, long val3_, std::string val4_, const std::string & val5_)
                : Serializable (javaTypeName<decltype(this)>(), "fingerprint123")
                , m_val1 (val1_)
                , m_val2 (val2_)
                , m_val3 (val3_)
                , m_val4 { std::move (val4_) }
                , m_val5 { new std::string (val5_) }
            { }

            explicit DeSerialiseMe (const std::vector<std::any> & l_)
                : Serializable (javaTypeName<decltype(this)>(), "fingerprint123")
                , m_val1 { std::any_cast<int>(l_[0]) }
                , m_val2 { std::any_cast<double>(l_[1]) }
                , m_val3 { std::any_cast<long>(l_[2]) }
                , m_val4 { std::any_cast<std::string>(l_[3]) }
                , m_val5 { std::any_cast<std::string *>(l_[4]) }
            { }


            [[maybe_unused]] static std::vector<std::any> deserialiseImpl(
                const SerialiserFactory & sf_,
                const AMQPBlob & blob_
            ) {
                std::vector<std::any> rtn;
                rtn.emplace_back (sf_.read<int> (blob_));
                rtn.emplace_back (sf_.read<double> (blob_));
                rtn.emplace_back (sf_.read<long> (blob_));
                rtn.emplace_back (sf_.read<std::string> (blob_));
                rtn.emplace_back (sf_.read<std::string *> (blob_));

                return rtn;
            }

            [[nodiscard]] const decltype (m_val1) & val1() const { return m_val1; }
            [[nodiscard]] const decltype (m_val2) & val2() const { return m_val2; }
            [[nodiscard]] const decltype (m_val3) & val3() const { return m_val3; }
            [[nodiscard]] const decltype (m_val4) & val4() const { return m_val4; }
            [[nodiscard]] const std::string & val5() const { return *m_val5; }
    };

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    DeSerialiseMe deSerialiseMe(1000, 24, 1, "hello", "world");

    auto blob = deSerialiseMe.serialise (sf);
    auto b = sf.deserialise<DeSerialiseMe>(*blob);

    ASSERT_EQ(deSerialiseMe.val1(), b.val1());
    ASSERT_EQ(deSerialiseMe.val2(), b.val2());
    ASSERT_EQ(deSerialiseMe.val3(), b.val3());
    ASSERT_EQ(deSerialiseMe.val4(), b.val4());
    ASSERT_EQ(deSerialiseMe.val5(), b.val5());
}

/******************************************************************************/

TEST (RTT, int_list) { // NOLINT
    class DeSerialiseMe : public Serializable {
        private :
            serializable::SerializableVector<int> m_val;

            void serialiseImpl(
                const SerialiserFactory & sf_,
                ModifiableAMQPBlob & blob_
            ) const override {
                sf_.write (m_val, "m_val", *this, blob_);
            }

        public :
            explicit DeSerialiseMe (std::vector<int> v_)
                : Serializable (javaTypeName<decltype(this)>(), "fingerprint123")
                , m_val ( "fingerprint456", std::move (v_) )
            { }

            explicit DeSerialiseMe (const std::vector<std::any> & l_)
                : Serializable (javaTypeName<decltype(this)>(), "fingerprint123")
                , m_val (std::any_cast<serializable::SerializableVector<int>>(l_[0]))
            { }

            [[maybe_unused]]
            static std::vector<std::any> deserialiseImpl(
                const SerialiserFactory & sf_,
                const AMQPBlob & blob_
            ) {
                std::vector<std::any> rtn;
                rtn.emplace_back (sf_.read<serializable::SerializableVector<int>> (blob_));
                return rtn;
            }

            [[nodiscard]] const decltype(m_val) & val() const { return m_val; }
    };

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    DeSerialiseMe deSerialiseMe(std::vector<int> {1, 2, 3, 4, 5});

    auto blob = deSerialiseMe.serialise (sf);
    auto b = sf.deserialise<DeSerialiseMe>(*blob);

    ASSERT_EQ(deSerialiseMe.val(), b.val());
}

/******************************************************************************/
