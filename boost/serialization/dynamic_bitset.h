#pragma once

#include <boost/dynamic_bitset.hpp>
#include "boost/serialization/serialization.h"
#include <boost/serialization/utility.hpp>
#include <boost/serialization/string.hpp>

namespace boost {
namespace serialization {

template<typename Archive, typename Block, typename Allocator>
void save(Archive& ar, boost::dynamic_bitset<Block, Allocator> const& bitset,
	const unsigned int)
{
	std::string bits;
	to_string(bitset, bits);
	ar << BOOST_SERIALIZATION_NVP(bits);
}

template<typename Archive, typename Block, typename Allocator>
void load(Archive& ar, boost::dynamic_bitset<Block, Allocator>& bitset,
	const unsigned int)
{
	std::string bits;
	ar >> BOOST_SERIALIZATION_NVP(bits);
	bitset = boost::dynamic_bitset<Block, Allocator>(bits);
}

template<typename Archive, typename Block, typename Allocator>
void serialize(Archive& ar, boost::dynamic_bitset<Block, Allocator>& bitset,
	const unsigned int version)
{
	split_free(ar, bitset, version);
}

} // serialization
} // booost
