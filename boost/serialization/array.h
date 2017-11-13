#pragma once

#include <boost/serialization/array.hpp>
#include <boost/version.hpp>

#ifdef PYPLUSPLUS
namespace std {
template<typename _Tp, std::size_t _Nm>
struct array;
}
#else
#include <array>
#endif

#if BOOST_VERSION < 105600
// serialization helper for std::array for boost version < 1.56
namespace boost {
namespace serialization {

template<typename Archiver, typename T, size_t Size>
void serialize(Archiver & ar, std::array<T, Size> & s, unsigned int const version)
{
	serialize(ar, reinterpret_cast<boost::array<T, Size>&>(s), version);
}

} // namespace serialization
} // namespace boost
#endif
