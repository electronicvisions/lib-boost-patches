#pragma once

#define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS
#include <boost/dynamic_bitset.hpp>
#undef BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS

#include <boost/serialization/utility.hpp>

namespace boost {
namespace serialization {
template<typename Archiver, typename Block, typename Allocator>
void serialize(Archiver & ar, boost::dynamic_bitset<Block, Allocator>& bitset, const unsigned int /*version*/)
{
	ar & BOOST_SERIALIZATION_NVP(bitset.m_bits)
	   & BOOST_SERIALIZATION_NVP(bitset.m_num_bits);
}
} // namespace serialization
} // namespace boost
