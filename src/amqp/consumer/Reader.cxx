#include "Reader.h"

template<>
std::string
amqp::TypedPair<std::vector<std::unique_ptr<amqp::Pair>>>::dump() const {
    std::strstream rtn;
    rtn << m_property + " : { ";

    rtn << m_value[0]->dump();
    for (auto it (std::next (m_value.begin())) ; it != m_value.end() ; ++it) {
       rtn << ", " << (*it)->dump();
    }
    rtn << " }";

    return rtn.str();
}
