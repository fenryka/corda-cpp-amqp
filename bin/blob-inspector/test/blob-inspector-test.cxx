#include <gtest/gtest.h>

#include "include/AMQPConfig.h"
#include "include/CordaBytes.h"

#include "../BlobInspector.h"

const std::string filepath ("../../test-files/"); // NOLINT

/******************************************************************************
 *
 * mapType Tests
 *
 ******************************************************************************/

void
test (const std::string & file_, const std::string & result_) {
    auto path { filepath + file_ } ;
    auto config = std::make_unique<amqp::AMQPConfig>();
    config->ignoreHeader = true;
    amqp::CordaBytes cb (path, std::move (config));
    auto val = BlobInspector (cb).dump();
    ASSERT_EQ(result_, val);
}

/******************************************************************************/

/**
 * int
 */
TEST (BlobInspector, _i_) { // NOLINT
    test ("_i_", "{ Parsed : { a : 69 } }");
}

/******************************************************************************/

/**
 * int, int
 */
TEST (BlobInspector, _ii_) { // NOLINT
    test ("_ii_", "{ Parsed : { a : 1, b : 2 } }");
}

/******************************************************************************/

/**
 * int, int, int
 *
 * NOTE: Currently, this test fails because we're not mapping the stored
 * property order onto the construction order. Essentially, the Corda
 * serialiser stores properties in the stream in a stable order based
 * on a sorting of the property names, whilst we're assuming they're
 * stored in declaration order
 */
#if 0
TEST (BlobInspector, _iii_) { // NOLINT
    test ("_iii_", "{ Parsed : { a : 10, b : 20, c : 30 } }");
}
#endif

/******************************************************************************/

TEST (BlobInspector, __i__i__) { // NOLINT
    test ("__i__i__", "{ Parsed : { a : { a : 1000 }, b : { a : 200 } } }");
}

/******************************************************************************/

/**
 * long
 */
TEST (BlobInspector, _l_) { // NOLINT
    test ("_l_", "{ Parsed : { x : 100000000000 } }");
}

/******************************************************************************/

/**
 * int
 */
TEST (BlobInspector, _Oi_) { // NOLINT
    test ("_Oi_", "{ Parsed : { a : 1 } }");
}

/******************************************************************************/

/**
 * array of int
 */
TEST (BlobInspector, _Ai_) { // NOLINT
    test ("_Ai_", "{ Parsed : { z : [ 1, 2, 3, 4, 5, 6 ] } }");
}

/******************************************************************************/

/**
 * List of ints
 */
TEST (BlobInspector, _Li_) { // NOLINT
    test ("_Li_", "{ Parsed : { a : [ 1, 2, 3, 4, 5, 6 ] } }");
}

/******************************************************************************/

/**
 * List of a class with a single int property
 */
TEST (BlobInspector, _L_i__) { // NOLINT
    test (
        "_L_i__",
        "{ Parsed : { listy : [ { a : 1 }, { a : 2 }, { a : 3 } ] } }");
}

/******************************************************************************/

TEST (BlobInspector, _Le_) { // NOLINT
    test ("_Le_", "{ Parsed : { listy : [ A, B, C ] } }");
}

/******************************************************************************/

TEST (BlobInspector,_Le_2) { // NOLINT
    EXPECT_THROW (
        {
            test ("_Le_2", "");
        },
        std::runtime_error);
}

/******************************************************************************/

/**
 * A map of ints to strings
 */
TEST (BlobInspector, _Mis_) { // NOLINT
    test ("_Mis_",
        R"({ Parsed : { a : { 1 : "two", 3 : "four", 5 : "six" } } })");
}

/******************************************************************************/

/**
 * A map of ints to lists of Strings
 */
TEST (BlobInspector, _MiLs_) { // NOLINT
    test ("_MiLs_",
        R"({ Parsed : { a : { 1 : [ "two", "three", "four" ], 5 : [ "six" ], 7 : [  ] } } })");
}

/******************************************************************************/

/**
 * a map of ints to a composite with a n int and string property
 */
TEST (BlobInspector, _Mi_is__) { // NOLINT
    test ("_Mi_is__",
        R"({ Parsed : { a : { 1 : { a : 2, b : "three" }, 4 : { a : 5, b : "six" }, 7 : { a : 8, b : "nine" } } } })");
}

/******************************************************************************/

TEST (BlobInspector,_Pls_) { // NOLINT
    test ("_Pls_",
            R"({ Parsed : { a : { first : 1, second : "two" } } })");
}

/******************************************************************************/

TEST (BlobInspector, _e_) { // NOLINT
    test ("_e_", "{ Parsed : { e : A } }");
}

/******************************************************************************/

TEST (BlobInspector, _i_is__) { // NOLINT
    test ("_i_is__",
            R"({ Parsed : { a : 1, b : { a : 2, b : "three" } } })");
}

/******************************************************************************/

// Array of unboxed integers
TEST (BlobInspector, _Ci_) { // NOLINT
    test ("_Ci_",
          R"({ Parsed : { z : [ 1, 2, 3 ] } })");
}

/******************************************************************************/

/**
 * Composite with
 *   * one int property
 *   * one long property
 *   * one list property that is a list of Maps of int to strings
 */
TEST (BlobInspector, __i_LMis_l__) { // NOLINT
    test ("__i_LMis_l__",
        R"({ Parsed : { x : [ { 1 : "two", 3 : "four", 5 : "six" }, { 7 : "eight", 9 : "ten" } ], y : { x : 1000000 }, z : { a : 666 } } })");
}

/******************************************************************************/

TEST (BlobInspector, _ALd_) { // NOLINT
    test ("_ALd_",
          R"({ Parsed : { a : [ [ 10.100000, 11.200000, 12.300000 ], [  ], [ 13.400000 ] ] } })");
}

/******************************************************************************/

TEST (BlobInspector, _p_i__null) { // NOLINT
    test ("_p_i__.null", "{ Parsed : { a : <<NULL>> } }");
}

/******************************************************************************/

TEST (BlobInspector, _p_i__notnull) { // NOLINT
    test ("_p_i__.notnull", "{ Parsed : { a : { a : 100 } } }");
}

/******************************************************************************/

TEST (BlobInspector, _Ls_) { // NOLINT
    test ("_Ls_", R"({ Parsed : { a : [ "Goodbye", "cruel", "world" ] } })");
}

/******************************************************************************/

TEST (BlobInspector, _i_dp) { // NOLINT
    test ("_i_.dp", "{ Parsed : { a : 69 } }");
}

/******************************************************************************/

TEST (BlobInspector, _isR_) { // NOLINT
    test ("_isR_",
          R"({ Parsed : { m_a : 5, m_b : "six", m_c : { m_a : 3, m_b : "four", m_c : { m_a : 1, m_b : "two", m_c : <<NULL>> } } } })");
}

/******************************************************************************/
