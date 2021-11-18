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

    template<typename> class RTTSingleList;

    template<typename T>
    class RTTSingleList : public amqp::serializable::Serializable<RTTSingleList<T>> {
    private :
        amqp::serializable::SerializableVector<T> m_val;

        void serialiseImpl(
                const SerialiserFactory &sf_,
                ModifiableAMQPBlob &blob_
        ) const override {
            m_val.serialise (sf_, blob_);
        }

    public :
        [[ maybe_unused ]]
        RTTSingleList(std::initializer_list<T> val_)
                : amqp::serializable::Serializable<RTTSingleList<T>>(javaTypeName<decltype(this)>())
                , m_val(val_) {}

        [[ maybe_unused ]]
        explicit RTTSingleList(const std::vector<std::any> &l_)
                : amqp::serializable::Serializable<RTTSingleList<T>>(javaTypeName<decltype(this)>())
        {

        }

        [[ maybe_unused ]] static std::vector<std::any> deserialiseImpl(
                const SerialiserFactory &sf_,
                const AMQPBlob &blob_
        ) {
            std::vector<std::any> rtn;
            rtn.emplace_back(sf_.read<T>(blob_));

            return rtn;
        }

//            [[nodiscard]] std::remove_pointer_t<T> val() const { return Getter<T>::get(m_val); }
    };
}

/******************************************************************************/

namespace {

    template<typename T, bool = std::is_pointer_v<T>>
    struct SingleListTest {
        static void
        test (
                amqp::internal::assembler::SerialiserFactoryInternal &sfi_,
                std::initializer_list<T> vals_
        ) {
            typedef RTTSingleList<T> Single;
            Single deSerialiseMe (vals_);

            auto blob = deSerialiseMe.serialise (sfi_);
            auto b = sfi_.deserialise<Single> (*blob);

//            ASSERT_EQ(deSerialiseMe.val(), b.val());
        }
    };

    template<typename T>
    struct SingleListTest<T, true> {
        static void
        test (
                amqp::internal::assembler::SerialiserFactoryInternal &sfi_,
                std::remove_pointer_t<T> val_
        ) {
            std::remove_pointer_t<T> val {val_};

            typedef RTTSingleList<T> Single;
            Single deSerialiseMe (&val);

            auto blob = deSerialiseMe.serialise (sfi_);
            auto b = sfi_.deserialise<Single> (*blob);

//            ASSERT_EQ(deSerialiseMe.val(), b.val());
        }
    };
}

/******************************************************************************/

TEST (RTT, SingleLists) { // NOLINT
    amqp::internal::assembler::SerialiserFactoryInternal sf;

    SingleListTest<int>::test (sf, { 1, 2, 3});
}

/******************************************************************************/

