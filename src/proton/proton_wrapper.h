#pragma once

/******************************************************************************/

#include <iosfwd>

/******************************************************************************/

struct pn_data_t;
struct pn_bytes_t;

/******************************************************************************/

/**
 * Friendly ostream operator for a pn_data_t type
 */
std::ostream& operator << (std::ostream& stream, pn_data_t * data_);

/******************************************************************************/

namespace proton {

    /**
     * Wrap enter so we automatically move to the first child node rather
     * than starting on an invalid one
     */
    bool pn_data_enter(pn_data_t *);

    void is_described (pn_data_t *);
    void is_ulong (pn_data_t *);
    void is_symbol (pn_data_t *);
    void is_string (pn_data_t *, bool allowNull = false);

    pn_bytes_t get_symbol (pn_data_t *);
    bool get_boolean (pn_data_t *);
    std::string get_string (pn_data_t *, bool allowNull = false);

    class auto_enter {
        private :
            pn_data_t * m_data;

        public :
            auto_enter (pn_data_t *);
            ~auto_enter();
    };

    class auto_enter_and_next {
        private :
            pn_data_t * m_data;

        public :
            auto_enter_and_next (pn_data_t *);
            ~auto_enter_and_next();
    };

    class auto_list_enter {
        private :
            size_t m_elements;
            pn_data_t * m_data;

        public :
            auto_list_enter (pn_data_t *);
            ~auto_list_enter();

            size_t elements() const;
    };

}

/******************************************************************************/

