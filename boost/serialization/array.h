#pragma once

#include <array>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>

// serialization helper for std::array
namespace boost {
namespace serialization {

template<typename Archiver, typename T, size_t Size>
void serialize(Archiver & ar, std::array<T, Size> & s, unsigned int const)
{
	ar & BOOST_SERIALIZATION_NVP(s._M_instance);
}

} // namespace serialization
} // namespace boost
