#pragma once

#include <bitset>
#include <string>

#include <boost/serialization/serialization.h>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/string.hpp>

#include "boost/serialization/dynamic_bitset.h"

namespace boost {
namespace serialization {

template<class Archive, size_t N>
void save(Archive& ar,
	std::bitset<N> const& t,
	const unsigned int /* version */)
{
	std::string const bits = t.to_string();
	ar << BOOST_SERIALIZATION_NVP(bits);
}

template<class Archive, size_t N>
void load(Archive& ar,
	std::bitset<N>& t,
	const unsigned int /* version */)
{
	std::string bits;
	ar >> BOOST_SERIALIZATION_NVP(bits);
	t = std::bitset<N>(bits);
}

template<typename Archive, size_t N>
void serialize(Archive& ar, std::bitset<N>& t, const unsigned int version)
{
	split_free(ar, t, version);
}

} // namespace serialization
} // namespace boost
