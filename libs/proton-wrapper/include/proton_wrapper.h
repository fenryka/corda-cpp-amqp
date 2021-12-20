#pragma once

/******************************************************************************/

#include <iosfwd>
#include <string>

#include <proton/types.h>
#include <proton/codec.h>

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

    void attest_is_double (pn_data_t *, const std::string &, int);
    void attest_is_char (pn_data_t *, const std::string &, int);
    void attest_is_long (pn_data_t *, const std::string &, int);
    void attest_is_float (pn_data_t *, const std::string &, int);
    void attest_is_bool (pn_data_t *, const std::string &, int);
    void attest_is_binary (pn_data_t *, const std::string &, int);
    void attest_is_int (pn_data_t *, const std::string &, int);
    void attest_is_list (pn_data_t *, const std::string &, int);
    void attest_is_string(pn_data_t *, const std::string &, int, bool = false);
    void attest_is_described(pn_data_t *, const std::string &, int);

    void is_map (pn_data_t *, const std::string &, int);

    [[maybe_unused]] [[maybe_unused]] bool is_primitive (pn_data_t *);

    void is_ulong(pn_data_t *);
    void is_symbol(pn_data_t *);

    bool is_described (pn_data_t *);
    [[maybe_unused]] bool is_bool (pn_data_t *);
    bool is_null (pn_data_t *);

    std::string typeToString (pn_data_t *);
}

/******************************************************************************/

namespace proton {

    /**
     * Specialised in the CXX file
     */
    template<typename T>
    T get_symbol (pn_data_t *) {
        return T {};
    }

    std::string get_symbol (pn_data_t *);

    [[maybe_unused]] [[maybe_unused]] int get_int (pn_data_t *);
    bool get_boolean (pn_data_t *);
    std::string get_string (pn_data_t *, bool allowNull = false);

    /**
     *
     */
    class auto_enter {
        private :
            pn_data_t * m_data;

        public :
            explicit auto_enter (pn_data_t *, bool next_ = false);
            ~auto_enter();
    };

    /**
     *
     */
    class auto_next {
        private :
            pn_data_t * m_data;

        public :
            explicit auto_next (pn_data_t *);
            auto_next (const auto_next &) = delete;

            explicit operator pn_data_t *() {
                return m_data;
            }

            ~auto_next();
    };

    /**
     *
     */
    class auto_list_enter {
        private :
            size_t      m_elements;
            pn_data_t * m_data;

        public :
            explicit auto_list_enter (pn_data_t *, bool next_ = false);
            ~auto_list_enter();

            [[nodiscard]] size_t elements() const;
    };

    /**
     *
     */
    class auto_map_enter {
        private :
            size_t      m_elements;
            pn_data_t * m_data;

        public :
            explicit auto_map_enter (pn_data_t *, bool next_ = false);
            ~auto_map_enter();

            [[nodiscard]] size_t elements() const;
    };

}

/******************************************************************************/

namespace proton {

    template<typename T>
    T
    readAndNext (
        pn_data_t *,
        const std::string &,
        int,
        [[maybe_unused]] bool tolerateDeviance_ = false
    ) {
        throw std::runtime_error ("This is very bad");
    }

}

namespace proton {

    template<>
    int32_t
    readAndNext(pn_data_t *, const std::string &, int, bool);

    template<>
    std::string
    readAndNext(pn_data_t *, const std::string &, int, bool);

    template<>
    char *
    readAndNext(pn_data_t *, const std::string &, int, bool);

    template<>
    std::pair<size_t, char *>
    readAndNext(pn_data_t *, const std::string &, int, bool);

    template<>
    long
    readAndNext(pn_data_t *, const std::string &, int, bool);

    template<>
    double
    readAndNext(pn_data_t *, const std::string &, int, bool);

    template<>
    bool
    readAndNext(pn_data_t *, const std::string &, int, bool);

}

/******************************************************************************/
