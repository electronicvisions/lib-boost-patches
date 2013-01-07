#pragma once
#include <boost/preprocessor/config/config.hpp>

#ifdef BOOST_PP_VARIADICS
#include <boost/preprocessor/variadic/to_seq.hpp>
#else
#include <boost/preprocessor/tuple/to_seq.hpp>
#define BOOST_PP_VARIADIC_TO_SEQ(...) BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__))
#endif
