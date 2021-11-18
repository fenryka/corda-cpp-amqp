
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

    template<typename T, bool = std::is_pointer_v<T>>
    struct Getter {
        static T get (const T &val_) {
            return val_;
        }
    };

    template<typename T>
    struct Getter<T, true> {
        static std::remove_pointer_t<T> get (const T &val_) {
            return *val_;
        }
    };

}

/******************************************************************************
 *
 * RTTSingle - Round Trip Test Single
 *
 ******************************************************************************/

template<typename T> class RTTSingle;

template<typename T>
class RTTSingle : public amqp::serializable::Serializable<RTTSingle<T>> {
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
                : amqp::serializable::Serializable<RTTSingle<T>>(javaTypeName<decltype(this)>())
                , m_val(std::move (val_)) {}

        [[ maybe_unused ]] explicit RTTSingle(const std::vector<std::any> &l_)
                : amqp::serializable::Serializable<RTTSingle<T>>(javaTypeName<decltype(this)>())
                , m_val(std::any_cast<T>(l_[0])) {}

        [[ maybe_unused ]] static std::vector<std::any> deserialiseImpl(
                const SerialiserFactory &sf_,
                const AMQPBlob &blob_
        ) {
            std::vector<std::any> rtn;
            rtn.emplace_back(sf_.read<T>(blob_));

            return rtn;
        }

        [[nodiscard]] std::remove_pointer_t<T> val() const { return Getter<T>::get(m_val); }
    };

/******************************************************************************/

template<> const std::string amqp::serializable::Fingerprint<RTTSingle<int>>::val = "SingleTestInt"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<RTTSingle<int *>>::val = "SingleTestIntPtr"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<RTTSingle<float>>::val = "SingleTestFloat"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<RTTSingle<float *>>::val = "SingleTestFloatPtr"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<RTTSingle<double>>::val = "SingleTestFloat"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<RTTSingle<double *>>::val = "SingleTestFloatPtr"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<RTTSingle<long>>::val = "SingleTestFloat"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<RTTSingle<long *>>::val = "SingleTestFloatPtr"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<RTTSingle<std::string>>::val = "SingleTestFloat"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<RTTSingle<std::string *>>::val = "SingleTestFloatPtr"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<RTTSingle<char>>::val = "SingleTestFloat"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<RTTSingle<char *>>::val = "SingleTestFloatPtr"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<RTTSingle<bool>>::val = "SingleTestFloat"; // NOLINT
template<> const std::string amqp::serializable::Fingerprint<RTTSingle<bool *>>::val = "SingleTestFloatPtr"; // NOLINT

/******************************************************************************/

namespace {

    template<typename, typename> class RTTDouble;

    template<typename T1, typename T2>
    class RTTDouble : public amqp::serializable::Serializable<RTTDouble<T1, T2>> {
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
                : amqp::serializable::Serializable<RTTDouble<T1, T2>>(javaTypeName<decltype(this)>())
                , m_val1 (std::move (val1_))
                , m_val2 (std::move (val2_))
            { }

            [[ maybe_unused ]] explicit RTTDouble(const std::vector<std::any> &l_)
                : amqp::serializable::Serializable<RTTDouble<T1, T2>>(javaTypeName<decltype(this)>())
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

            [[nodiscard]] std::remove_pointer_t<T1> val1() const { return Getter<T1>::get(m_val1); }
            [[nodiscard]] std::remove_pointer_t<T2> val2() const { return Getter<T2>::get(m_val2); }
    };
}

/******************************************************************************/

namespace {

    template<typename T, bool = std::is_pointer_v<T>>
    struct [[maybe_unused]] SingleTest {
        static void
        test (
            amqp::internal::assembler::SerialiserFactoryInternal &sfi_,
            std::remove_pointer_t<T> val_
        ) {
            typedef RTTSingle<T> Single;
            Single deSerialiseMe (val_);

            auto blob = deSerialiseMe.serialise (sfi_);
            auto b = sfi_.deserialise<Single> (*blob);

            ASSERT_EQ(deSerialiseMe.val(), b.val());
        }
    };

    template<typename T>
    struct [[maybe_unused]] SingleTest<T, true> {
        static void
        test (
            amqp::internal::assembler::SerialiserFactoryInternal &sfi_,
            std::remove_pointer_t<T> val_
        ) {
            std::remove_pointer_t<T> val {val_};

            typedef RTTSingle<T> Single;
            Single deSerialiseMe (&val);

            auto blob = deSerialiseMe.serialise (sfi_);
            auto b = sfi_.deserialise<Single> (*blob);

            ASSERT_EQ(deSerialiseMe.val(), b.val());
        }
    };
}

/******************************************************************************/

TEST (RTT, singles) { // NOLINT
    amqp::internal::assembler::SerialiserFactoryInternal sf;

    SingleTest<int>::test (sf, 69);
    SingleTest<float>::test (sf, 69.6969);
    SingleTest<double>::test (sf, 100);
    SingleTest<long>::test (sf, 400);
    SingleTest<std::string>::test (sf, "This is a test");
    SingleTest<bool>::test (sf, true);
    SingleTest<char>::test (sf, 'a');
}

/******************************************************************************/

TEST (RTT, singlePointers) { // NOLINT
    amqp::internal::assembler::SerialiserFactoryInternal sf;

    SingleTest<int *>::test (sf, 69);
    SingleTest<float *>::test (sf, 69.6969);
    SingleTest<double *>::test (sf, 100);
    SingleTest<long *>::test (sf, 400);
    SingleTest<std::string *>::test (sf, "This is a test");
    SingleTest<bool *>::test (sf, true);
    SingleTest<char *>::test (sf, 'a');
}

/******************************************************************************/

namespace {

    template<typename> struct defVal {};
    template<> struct defVal<int> { static const int val = 10; };
    template<> struct defVal<char> { static const char val = 'a'; };
    template<> struct defVal<double> { constexpr static double val = 100.1; };
    template<> struct defVal<float> { constexpr static float val = 69.69; };
    template<> struct defVal<long> { constexpr static long val = 100000; };
    template<> struct defVal<bool> { constexpr static bool val = true; };
    template<> struct defVal<std::string> { static const std::string val; };

    const std::string defVal<std::string>::val = "Hello World"; // NOLINT

}

/******************************************************************************/

namespace {

    template<typename T1, typename T2>
    void
    doubleTest (
        amqp::internal::assembler::SerialiserFactoryInternal &sfi_,
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

}

/******************************************************************************/

namespace {

    template<typename T, typename ...Args>
    struct doubleTester {

        template<typename OUTER, typename T2, typename ...Args2>
        struct with {

            static void
            test (amqp::internal::assembler::SerialiserFactoryInternal & sfi_) {
                doubleTest<OUTER, T2>(sfi_, defVal<OUTER>::val, defVal<T2>::val);

                if constexpr (sizeof...(Args2) > 0) {
                    with<OUTER, Args2...>::test (sfi_);
                }
            }
        };

        template<typename T2, typename ...Args2>
        static
        void
        test (amqp::internal::assembler::SerialiserFactoryInternal & sfi_) {
            with<T, T2, Args2...>::test (sfi_);

            // Recurse down our outer typelist
            if constexpr (sizeof...(Args) > 0) {
                doubleTester<Args...>::template test<T2, Args2...> (sfi_);
            }
        }
    };
}

/******************************************************************************/

#define FINGERPRINT(T1, T2) template<> const std::string amqp::serializable::Fingerprint<RTTDouble<T1, T2>>::val = "I-I" // NOLINT

FINGERPRINT(int, int);
FINGERPRINT(int, float);
FINGERPRINT(int, double);
FINGERPRINT(int, long);
FINGERPRINT(int, std::string);
FINGERPRINT(int, bool);
FINGERPRINT(int, char);

FINGERPRINT(float, int);
FINGERPRINT(float, float);
FINGERPRINT(float, double);
FINGERPRINT(float, long);
FINGERPRINT(float, std::string);
FINGERPRINT(float, bool);
FINGERPRINT(float, char);

FINGERPRINT(double, int);
FINGERPRINT(double, float);
FINGERPRINT(double, double);
FINGERPRINT(double, long);
FINGERPRINT(double, std::string);
FINGERPRINT(double, bool);
FINGERPRINT(double, char);

FINGERPRINT(long, int);
FINGERPRINT(long, float);
FINGERPRINT(long, double);
FINGERPRINT(long, long);
FINGERPRINT(long, std::string);
FINGERPRINT(long, bool);
FINGERPRINT(long, char);

FINGERPRINT(std::string, int);
FINGERPRINT(std::string, float);
FINGERPRINT(std::string, double);
FINGERPRINT(std::string, long);
FINGERPRINT(std::string, std::string);
FINGERPRINT(std::string, bool);
FINGERPRINT(std::string, char);

FINGERPRINT(bool, int);
FINGERPRINT(bool, float);
FINGERPRINT(bool, double);
FINGERPRINT(bool, long);
FINGERPRINT(bool, std::string);
FINGERPRINT(bool, bool);
FINGERPRINT(bool, char);

FINGERPRINT(char, int);
FINGERPRINT(char, float);
FINGERPRINT(char, double);
FINGERPRINT(char, long);
FINGERPRINT(char, std::string);
FINGERPRINT(char, bool);
FINGERPRINT(char, char);

/******************************************************************************/

TEST (RTT, things) { // NOLINT
    amqp::internal::assembler::SerialiserFactoryInternal sf;

    doubleTester<int, float, double, long, std::string, bool, char>
        ::test<int, float, double, long, std::string, bool, char>(sf);
}

/******************************************************************************/

class ManyTypes: public amqp::serializable::Serializable<ManyTypes> {
    friend class amqp::assembler::SerialiserFactory;

private :
    int m_val1;
    double m_val2;
    long m_val3;
    std::string m_val4;
    std::string *m_val5;

    void serialiseImpl(
            const SerialiserFactory &sf_,
            ModifiableAMQPBlob &blob_
    ) const override {
        sf_.write<int>(m_val1, "m_val1", *this, blob_);
        sf_.write<double>(m_val2, "m_val2", *this, blob_);
        sf_.write<long>(m_val3, "m_val3", *this, blob_);
        sf_.write<std::string>(m_val4, "m_val4", *this, blob_);
        sf_.write<std::string *>(m_val5, "m_val5", *this, blob_);
    }

public :
    explicit ManyTypes(int val1_, double val2_, long val3_, std::string val4_, const std::string &val5_)
            : amqp::serializable::Serializable<ManyTypes>(javaTypeName<decltype(this)>()), m_val1(val1_),
              m_val2(val2_), m_val3(val3_), m_val4{std::move(val4_)}, m_val5{new std::string(val5_)} {}

    explicit ManyTypes(const std::vector<std::any> &l_)
            : amqp::serializable::Serializable<ManyTypes>(javaTypeName<decltype(this)>()),
              m_val1{std::any_cast<int>(l_[0])}, m_val2{std::any_cast<double>(l_[1])},
              m_val3{std::any_cast<long>(l_[2])}, m_val4{std::any_cast<std::string>(l_[3])},
              m_val5{std::any_cast<std::string *>(l_[4])} {}

    [[maybe_unused]] static std::vector<std::any> deserialiseImpl(
            const SerialiserFactory &sf_,
            const AMQPBlob &blob_
    ) {
        std::vector<std::any> rtn;
        rtn.emplace_back(sf_.read<int>(blob_));
        rtn.emplace_back(sf_.read<double>(blob_));
        rtn.emplace_back(sf_.read<long>(blob_));
        rtn.emplace_back(sf_.read<std::string>(blob_));
        rtn.emplace_back(sf_.read<std::string *>(blob_));

        return rtn;
    }

    [[nodiscard]] const decltype(m_val1) &val1() const { return m_val1; }

    [[nodiscard]] const decltype(m_val2) &val2() const { return m_val2; }

    [[nodiscard]] const decltype(m_val3) &val3() const { return m_val3; }

    [[nodiscard]] const decltype(m_val4) &val4() const { return m_val4; }

    [[nodiscard]] const std::string &val5() const { return *m_val5; }
};

template<> const std::string amqp::serializable::Fingerprint<ManyTypes>::val = "DSM"; // NOLINT

TEST (RTT, many_types) { // NOLINT

    amqp::internal::assembler::SerialiserFactoryInternal sf;

    ManyTypes deSerialiseMe(1000, 24, 1, "hello", "world");

    auto blob = deSerialiseMe.serialise(sf);
    auto b = sf.deserialise<ManyTypes>(*blob);

    ASSERT_EQ(deSerialiseMe.val1(), b.val1());
    ASSERT_EQ(deSerialiseMe.val2(), b.val2());
    ASSERT_EQ(deSerialiseMe.val3(), b.val3());
    ASSERT_EQ(deSerialiseMe.val4(), b.val4());
    ASSERT_EQ(deSerialiseMe.val5(), b.val5());
}

/******************************************************************************/

class INTList : public amqp::serializable::Serializable<INTList> {
    private :
        serializable::SerializableVector<int> m_val;

        void serialiseImpl(
            const SerialiserFactory & sf_,
            ModifiableAMQPBlob & blob_
        ) const override {
            sf_.write (m_val, "m_val", *this, blob_);
        }

    public :
        explicit INTList (std::vector<int> v_)
            : Serializable<INTList>(javaTypeName<decltype(this)>())
            , m_val (std::move (v_) )
        { }

        explicit INTList (const std::vector<std::any> & l_)
            : Serializable<INTList> (javaTypeName<decltype(this)>())
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

/**
 * Declare fingerprints for the above types
 */
template<>
const std::string amqp::serializable::Fingerprint<INTList>::val = "INTListC"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<std::vector<int>>::val = "int-vector"; // NOLINT

template<>
const std::string amqp::serializable::Fingerprint<SerializableVector<int>>::val = "int-vector-alt"; // NOLINT

TEST (RTT, int_list) { // NOLINT


    amqp::internal::assembler::SerialiserFactoryInternal sf;

    INTList deSerialiseMe(std::vector<int> {1, 2, 3, 4, 5});

    auto blob = deSerialiseMe.serialise (sf);
    auto b = sf.deserialise<INTList>(*blob);

    ASSERT_EQ(deSerialiseMe.val(), b.val());
}

/******************************************************************************/

