#pragma once

#include <array>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/array.hpp>

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
