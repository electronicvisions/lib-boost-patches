#pragma once

#include <boost/serialization/array.hpp>

namespace std {
template<typename _Tp, std::size_t _Nm>
struct array;
}

// serialization helper for std::array
namespace boost {
namespace serialization {

template<typename Archiver, typename T, size_t Size>
void serialize(Archiver & ar, std::array<T, Size> & s, unsigned int const version)
{
	serialize(ar, reinterpret_cast<boost::array<T, Size>&>(s), version);
}

} // namespace serialization
} // namespace boost
