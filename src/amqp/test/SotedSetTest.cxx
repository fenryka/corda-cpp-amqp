#include <gtest/gtest.h>


#include <memory>
#include "amqp/schema/Field.h"
#include "amqp/schema/Schema.h"
#include "amqp/schema/Composite.h"
#include "amqp/schema/restricted-types/Restricted.h"
#include "amqp/schema/Descriptor.h"
#include "amqp/schema/AMQPTypeNotation.h"

/******************************************************************************/

std::unique_ptr<amqp::internal::schema::Field>
makeIntField (const std::string & name_) {
    std::list<std::string> requires (0);
    return std::make_unique<amqp::internal::schema::Field>(
            name_,
            "int",
            requires,
            "default",
            "label",
            false,
            false);
}

/******************************************************************************/

std::unique_ptr<amqp::internal::schema::Field>
makeStringField (const std::string & name_) {
    std::list<std::string> requires (0);
    return std::make_unique<amqp::internal::schema::Field>(
            name_,
            "string",
            requires,
            "default",
            "label",
            false,
            false);
}

/******************************************************************************/

std::unique_ptr<amqp::internal::schema::Field>
makeCompositeField (
        const std::string & name_,
        const std::unique_ptr<amqp::internal::schema::AMQPTypeNotation> & type_)
{
    std::list<std::string> requires (0);
    return std::make_unique<amqp::internal::schema::Field>(
            name_,
            type_->name(),
            requires,
            "default",
            "label",
            false,
            false);

}

/******************************************************************************
 *
 *
 *
 ******************************************************************************/

std::unique_ptr<amqp::internal::schema::Descriptor>
makeDescriptor (const std::string & name_) {
    return std::make_unique<amqp::internal::schema::Descriptor> (name_);
}

/******************************************************************************
 *
 *
 *
 ******************************************************************************/

std::unique_ptr<amqp::internal::schema::AMQPTypeNotation>
makeComposite (
        const std::string & name_,
        std::vector<std::unique_ptr<amqp::internal::schema::Field>> & fields_)
{
    std::list<std::string> provides;
    std::string label { "label" };
    auto descriptor = makeDescriptor(name_);

    return std::make_unique<amqp::internal::schema::Composite>(
            name_,
            label,
            provides,
            descriptor,
            fields_);
}

/******************************************************************************/

std::unique_ptr<amqp::internal::schema::AMQPTypeNotation>
makeRestrictedList (
        const std::string & name_,
        const std::unique_ptr<amqp::internal::schema::AMQPTypeNotation> & type_)
{
    std::vector<std::string> provides;
    std::string label { "label" };
    auto descriptor = makeDescriptor(name_);

    std::stringstream ss;
    ss << "java.util.List<" + type_->name() + ">";

    return amqp::internal::schema::Restricted::make(
            descriptor,
            ss.str(),
            label,
            provides,
            "list");
}

/******************************************************************************
 *
 * Set Type for our test
 *
 ******************************************************************************/

typedef std::set<
    std::unique_ptr<amqp::internal::schema::AMQPTypeNotation>,
    amqp::internal::schema::SetSort> TestSet;

/******************************************************************************
 *
 * Tests
 *
 ******************************************************************************/

TEST (SotedSet, just_composites) {
    std::cout << std::endl;

    std::vector<std::unique_ptr<amqp::internal::schema::Field>> v1;
    v1.reserve(2);
    v1.emplace_back(makeIntField("a"));
    v1.emplace_back(makeStringField("b"));

    EXPECT_EQ(2, v1.size());

    auto c1 = makeComposite("comp1", v1);

    std::vector<std::unique_ptr<amqp::internal::schema::Field>> v2;
    v2.reserve(1);
    v2.emplace_back(makeCompositeField("c", c1));

    EXPECT_EQ(1, v2.size());

    auto c2 = makeComposite("comp2", v2);

    std::vector<std::unique_ptr<amqp::internal::schema::Field>> v3;
    v3.reserve(1);
    v3.emplace_back(makeCompositeField("c", c2));

    EXPECT_EQ(1, v3.size());

    auto c3 = makeComposite("comp3", v3);

    TestSet set (amqp::internal::schema::Schema::setSorter);
    set.insert (std::move (c3));
    set.insert (std::move (c2));
    set.insert (std::move (c1));

    auto it = set.begin();
    ASSERT_EQ ("comp1", (*it++)->name());
    ASSERT_EQ ("comp2", (*it++)->name());
    ASSERT_EQ ("comp3", (*it++)->name());
}

/******************************************************************************/

TEST (SortedSet, lists) {
    std::cout << std::endl;

    std::vector<std::unique_ptr<amqp::internal::schema::Field>> v;
    v.reserve(1);
    v.emplace_back(makeIntField("a"));

    auto c = makeComposite("c", v);
    auto l = makeRestrictedList("l", c);

    TestSet set (amqp::internal::schema::Schema::setSorter);
    set.insert (std::move(l));
    set.insert (std::move(c));

    for (auto & s : set){
        std::cout << *s << std::endl;
    }
}

/******************************************************************************/

