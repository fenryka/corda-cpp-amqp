#include <sstream>
#include <cassert>

#include "AMQPBlob.h"

#include "amqp/src/schema/described-types/Envelope.h"
#include "amqp/src/schema/descriptors/Descriptors.h"
#include "amqp/src/schema/descriptors/AMQPDescriptorRegistory.h"
#include "amqp/src/assembler/CompositeFactory.h"

#include "proton-wrapper/include/proton_wrapper.h"

/******************************************************************************/

amqp::
AMQPBlob::AMQPBlob (amqp::CordaBytes & cb_)
    : m_data { pn_data (cb_.size()) }
{
    // returns how many bytes we processed which right now we don't care
    // about but I assume there is a case where it doesn't process the
    // entire file

    auto rtn = pn_data_decode(m_data, cb_.bytes(), cb_.size());
    assert (static_cast<size_t>(rtn) == cb_.size());
}

/******************************************************************************/

auto
amqp::
AMQPBlob::dumpSchema (schema::DumpTarget target_) const -> std::string {
    proton::is_described (m_data);

    std::stringstream ss;

    amqp::internal::AMQPDescriptorRegistory[PN_DESCRIBED]->read (
       m_data,
        ss,
       target_);

/**
 * I have zero idea why clan things *this* line is an infinite loop, but it
 * does and that's vexing so shut up the warning
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    return ss.str();
#pragma clang diagnostic pop
#pragma clang diagnostic pop
}

/******************************************************************************/

namespace {

using IValPtr = uPtr<amqp::serialiser::reader::IValue>;
using SingleString = amqp::internal::serialiser::reader::TypedSingle<std::string>;

    IValPtr
    dumpPrimitive (pn_data_t * data_) {

        switch (pn_data_type (data_)) {
            case PN_LONG :
                return std::make_unique<SingleString> (std::to_string (pn_data_get_long (data_)));
            case PN_ULONG :
                return std::make_unique<SingleString> (std::to_string (pn_data_get_ulong (data_)));
            case PN_STRING :
                return std::make_unique<SingleString> (proton::get_string (data_));
            case PN_INT :
                return std::make_unique<SingleString> (std::to_string (pn_data_get_int (data_)));
            case PN_UINT :
                return std::make_unique<SingleString> (std::to_string (pn_data_get_uint (data_)));
            case PN_FLOAT :
                return std::make_unique<SingleString> (std::to_string (pn_data_get_float (data_)));
            case PN_DOUBLE :
                return std::make_unique<SingleString> (std::to_string (pn_data_get_double (data_)));
            case PN_BOOL :
                return std::make_unique<SingleString> (pn_data_get_bool (data_) ? "true" : "false");
            case PN_SYMBOL :
                return std::make_unique<SingleString> ("<<SYMBOL>>");
            default :
                return std::make_unique<SingleString> ("<<UNKNOWN>>");

        }
    }

    IValPtr dumpComposite (pn_data_t *);
    IValPtr dumpMap (pn_data_t *);

    IValPtr
    dumpList (pn_data_t * data_) {
        std::cout << __FUNCTION__ << std::endl;
        proton::is_list (data_, __FILE__, __LINE__);
        proton::auto_list_enter ale (data_, true);

        sList<IValPtr> list;

        do {
            auto type = pn_data_type (data_);
            if ( type == PN_LIST) {
                list.emplace_back (dumpList (data_));
            } else if (type == PN_MAP) {
                list.emplace_back (dumpMap (data_));
            } else if (type == PN_DESCRIBED) {
                list.emplace_back (dumpComposite (data_));
            } else {
                list.emplace_back (dumpPrimitive (data_));
            }
        } while (pn_data_next (data_));

        return std::make_unique<amqp::internal::serialiser::reader::TypedSingle<sList<IValPtr>>>(std::move (list));
    }


    IValPtr
    dumpMap (pn_data_t * data_) {
        proton::is_map (data_, __FILE__, __LINE__);
        sList<IValPtr> list;
        {
            proton::auto_map_enter am (data_, true);

            for (int i {0} ; i < am.elements() ; i += 2) {
                IValPtr key, value;

                auto keyType = pn_data_type (data_);
                if ( keyType == PN_LIST) {
                    key = dumpList (data_);
                } else if (keyType == PN_MAP) {
                    key = dumpMap (data_);
                } else if (keyType == PN_DESCRIBED) {
                    key = dumpComposite (data_);
                } else {
                    key = dumpPrimitive (data_);
                }

                auto valueType = pn_data_type (data_);
                if ( valueType == PN_LIST) {
                    value = dumpList (data_);
                } else if (valueType == PN_MAP) {
                    value = dumpMap (data_);
                } else if (valueType == PN_DESCRIBED) {
                    value = dumpComposite (data_);
                } else {
                    value = dumpPrimitive (data_);
                }

                list.emplace_back (
                        std::make_unique<amqp::internal::serialiser::reader::ValuePair> (
                                std::move (key), std::move (value)
                        )
                );
            }
        }

        return std::make_unique<amqp::internal::serialiser::reader::TypedSingle<sList<IValPtr>>> (std::move (list));
    }

    IValPtr
    dumpComposite (pn_data_t * data_) {
        proton::assert_described (data_);

        {
            proton::auto_enter p2(data_);
            auto fingerprint = proton::readAndNext<std::string>(data_);

            std::cout << __FUNCTION__ << ": " << fingerprint << std::endl;

            proton::is_list (data_, __FILE__, __LINE__);
            proton::auto_list_enter ale (data_, true);

            sList<IValPtr> list;

            do {
                auto type = pn_data_type (data_);

                if ( type == PN_LIST) {
                    list.emplace_back (dumpList (data_));
                } else if (type == PN_MAP) {
                    list.emplace_back (dumpMap (data_));
                } else if (type == PN_DESCRIBED) {
                    list.emplace_back (dumpComposite (data_));
                } else {
                    list.emplace_back (dumpPrimitive (data_));
                }
            } while (pn_data_next (data_));

            return std::make_unique<amqp::internal::serialiser::reader::TypedPair<sList<IValPtr>>> (
                    fingerprint,
                    std::move (list));

        }
    }

}

/******************************************************************************/

/**
 * Take a aCorda serialized blob and walk the data section of it dumping
 * the contents. Less usful than the schema dumper but a useful debugging
 * tool none the less
 */
auto
amqp::
AMQPBlob::dumpData() const -> std::string {
    if (pn_data_is_described (m_data)) {
        // move to the actual blob entry in the tree - ideally we'd have
        // saved this on the Envelope but that's not easily doable as we
        // can't grab an actual copy of our data pointer
        proton::assert_described(m_data);
        {
            proton::auto_enter p (m_data);
            uint64_t key = proton::readAndNext<u_long>(m_data);
            assert (stripCorda (key) == amqp::internal::schema::descriptors::ENVELOPE);
        }

        proton::auto_enter p (m_data, true);
        proton::is_list (m_data, __FILE__, __LINE__);

        // first element in the list is the data (second the schema, third the transforms)
        proton::auto_list_enter ale (m_data, true);
        auto val = dumpComposite (m_data);

        std::cout << val->dump() << std::endl;
    }

    return "";
}

/******************************************************************************/

/*
 * Read the contents of the blob out as a string matching data in the
 * payload to elements from the schema
 */
std::string
amqp::
AMQPBlob::dumpContents() const {
    std::unique_ptr<internal::schema::Envelope> envelope;

    if (pn_data_is_described (m_data)) {
        proton::auto_enter p (m_data);

        auto a = pn_data_get_ulong(m_data);

        envelope.reset (
                dynamic_cast<amqp::internal::schema::Envelope *> (
                        internal::AMQPDescriptorRegistory[a]->build(m_data).release()));
    }

    auto cf = internal::assembler::CompositeFactory();

    cf.process (envelope->schema());

    auto reader = cf.byDescriptor (envelope->descriptor());
    assert (reader);

    {
        // move to the actual blob entry in the tree - ideally we'd have
        // saved this on the Envelope but that's not easily doable as we
        // can't grab an actual copy of our data pointer
        proton::auto_enter p (m_data, true);
        proton::is_list (m_data, __FILE__, __LINE__);
        assert (pn_data_get_list (m_data) == 3);

        {
            proton::auto_enter p2 (m_data);

            std::stringstream ss;

            // We wrap our output like this to make sure it's valid JSON to
            // facilitate easy pretty printing
            ss << reader->dump ("{ Parsed", m_data, envelope->schema())->dump()
               << " }";

            return ss.str();
        }
    }
}

/******************************************************************************/
