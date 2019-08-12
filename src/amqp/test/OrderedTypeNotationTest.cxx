#include <gtest/gtest.h>

#include "OrderedTypeNotations.h"

/******************************************************************************/

namespace {

    class OTN : public amqp::internal::schema::OrderedTypeNotation {
        private :
            std::string m_name;
            std::vector<std::string> m_dependsOn;
        public :
            OTN(std::string name_, const std::vector<std::string> & dependsOn_)
                : m_name (std::move (name_))
                , m_dependsOn (dependsOn_)
            { }


            bool dependsOn (const OrderedTypeNotation & otn_) const override {
                return std::find (
                        m_dependsOn.begin(),
                        m_dependsOn.end(),
                        dynamic_cast<const OTN &>(otn_).name()) != m_dependsOn.end();
            }

            const std::string & name() const { return m_name; }
    };

}

/******************************************************************************/

TEST (OTNTest, singleInsert) {
    amqp::internal::schema::OrderedTypeNotations<OTN> list;

    list.insert(std::make_unique<OTN>("A", std::vector<std::string>()));
    std::cout << list << std::endl;
}

/******************************************************************************/

TEST (OTNTest, twoInserts) {
    std::cout << std::endl;
    amqp::internal::schema::OrderedTypeNotations<OTN> list;

    list.insert(std::make_unique<OTN>("A", std::vector<std::string>()));
    list.insert(std::make_unique<OTN>("B", std::vector<std::string>()));
    std::cout << list << std::endl;
}

/******************************************************************************/

TEST (OTNTest, A_depends_on_B) {
    std::cout << std::endl;
    amqp::internal::schema::OrderedTypeNotations<OTN> list;

    std::vector<std::string> aDeps = { "B" };
    list.insert(std::make_unique<OTN>("A", aDeps));
    list.insert(std::make_unique<OTN>("B", std::vector<std::string>()));
    std::cout << list << std::endl;
}

/******************************************************************************/

TEST (OTNTest, B_depends_on_A) {
    std::cout << std::endl;
    amqp::internal::schema::OrderedTypeNotations<OTN> list;

    std::vector<std::string> aDeps = { };
    list.insert(std::make_unique<OTN>("A", aDeps));
    std::vector<std::string> bDeps = { "A" };
    list.insert(std::make_unique<OTN>("B", bDeps));
    std::cout << list << std::endl;
}

/******************************************************************************/

TEST (OTNTest, three_1) {
    std::cout << std::endl;
    amqp::internal::schema::OrderedTypeNotations<OTN> list;

    std::vector<std::string> aDeps = { };
    std::vector<std::string> bDeps = { "A" };
    std::vector<std::string> cDeps = { "A" };

    list.insert(std::make_unique<OTN>("A", aDeps));
    list.insert(std::make_unique<OTN>("B", bDeps));
    list.insert(std::make_unique<OTN>("C", cDeps));
    std::cout << list << std::endl;
}

/******************************************************************************/

TEST (OTNTest, three_2) {
    std::cout << std::endl;
    amqp::internal::schema::OrderedTypeNotations<OTN> list;

    std::vector<std::string> aDeps = { "B" };
    std::vector<std::string> bDeps = { "C" };
    std::vector<std::string> cDeps = {  };

    list.insert(std::make_unique<OTN>("A", aDeps));
    std::cout << list << std::endl;
    list.insert(std::make_unique<OTN>("B", bDeps));
    std::cout << list << std::endl;
    list.insert(std::make_unique<OTN>("C", cDeps));
    std::cout << list << std::endl;
}

/******************************************************************************/

TEST (OTNTest, three_3) {
    std::cout << std::endl;
    amqp::internal::schema::OrderedTypeNotations<OTN> list;

    std::vector<std::string> aDeps = { "B" };
    std::vector<std::string> bDeps = { "C" };
    std::vector<std::string> cDeps = {  };

    list.insert(std::make_unique<OTN>("C", cDeps));
    std::cout << list << std::endl;
    list.insert(std::make_unique<OTN>("A", aDeps));
    std::cout << list << std::endl;
    list.insert(std::make_unique<OTN>("B", bDeps));
    std::cout << list << std::endl;
}

/******************************************************************************/

TEST (OTNTest, three_4) {
    std::cout << std::endl;
    amqp::internal::schema::OrderedTypeNotations<OTN> list;

    std::vector<std::string> aDeps = { "B" };
    std::vector<std::string> bDeps = { "C" };
    std::vector<std::string> cDeps = {  };

    list.insert(std::make_unique<OTN>("C", cDeps));
    std::cout << list << std::endl;
    list.insert(std::make_unique<OTN>("B", bDeps));
    std::cout << list << std::endl;
    list.insert(std::make_unique<OTN>("A", aDeps));
    std::cout << list << std::endl;
}

/******************************************************************************/
