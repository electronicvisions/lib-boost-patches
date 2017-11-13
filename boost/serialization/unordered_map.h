#pragma once

#include <unordered_map>
#include <unordered_set>

#include <boost/config.hpp>

#if BOOST_VERSION < 105600
// serialization helper for std::unordered_map for boost version < 1.56

#include <boost/serialization/utility.hpp>
#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost {
namespace serialization {

template<class Archive, class Type, class Key, class Hash, class Compare, class Allocator >
inline void save(
	Archive & ar,
	const std::unordered_map<Key, Type, Hash, Compare, Allocator> &t,
	const unsigned int /* file_version */)
{
	boost::serialization::stl::save_collection<
		Archive,
		std::unordered_map<Key, Type, Hash, Compare, Allocator>
	>(ar, t);
}

template<class Archive, class Type, class Key, class Hash, class Compare, class Allocator >
inline void load(
	Archive & ar,
	std::unordered_map<Key, Type, Hash, Compare, Allocator> &t,
	const unsigned int /* file_version */)
{
	boost::serialization::stl::load_collection<
		Archive,
		std::unordered_map<Key, Type, Hash, Compare, Allocator>,
		boost::serialization::stl::archive_input_map<
			Archive, std::unordered_map<Key, Type, Hash, Compare, Allocator> >,
		boost::serialization::stl::no_reserve_imp<std::unordered_map<
			Key, Type, Hash, Compare, Allocator > >
	>(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Type, class Key, class Hash, class Compare, class Allocator >
inline void serialize(
	Archive & ar,
	std::unordered_map<Key, Type, Hash, Compare, Allocator> &t,
	const unsigned int file_version)
{
	boost::serialization::split_free(ar, t, file_version);
}

// multimap
template<class Archive, class Type, class Key, class Hash, class Compare, class Allocator >
inline void save(
	Archive & ar,
	const std::unordered_multimap<Key, Type, Hash, Compare, Allocator> &t,
	const unsigned int /* file_version */)
{
	boost::serialization::stl::save_collection<
		Archive,
		std::unordered_multimap<Key, Type, Hash, Compare, Allocator>
	>(ar, t);
}

template<class Archive, class Type, class Key, class Hash, class Compare, class Allocator >
inline void load(
	Archive & ar,
	std::unordered_multimap<Key, Type, Hash, Compare, Allocator> &t,
	const unsigned int /* file_version */)
{
	boost::serialization::stl::load_collection<
		Archive,
		std::unordered_multimap<Key, Type, Hash, Compare, Allocator>,
		boost::serialization::stl::archive_input_map<
			Archive, std::unordered_multimap<Key, Type, Hash, Compare, Allocator>
		>,
		boost::serialization::stl::no_reserve_imp<
			std::unordered_multimap<Key, Type, Hash, Compare, Allocator>
		>
	>(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Type, class Key, class Hash, class Compare, class Allocator >
inline void serialize(
	Archive & ar,
	std::unordered_multimap<Key, Type, Hash, Compare, Allocator> &t,
	const unsigned int file_version)
{
	boost::serialization::split_free(ar, t, file_version);
}

} // serialization
} // namespace boost

#else

// boost::serialization 1.56 supports serialization of unordered_map
#include <boost/serialization/unordered_map.hpp>

#endif // BOOST_VERSION < 105600
