#pragma once

#include <tbb/concurrent_unordered_map.h>

#include <boost/config.hpp>

#include <boost/serialization/utility.hpp>
#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost {
namespace serialization {

template<class Archive, class Type, class Key, class Hash, class Compare, class Allocator>
inline void save(
	Archive & ar,
	const tbb::concurrent_unordered_map<Key, Type, Hash, Compare, Allocator> &t,
	const unsigned int /* file_version */)
{
	boost::serialization::stl::save_collection<
		Archive,
		tbb::concurrent_unordered_map<Key, Type, Hash, Compare, Allocator>
	>(ar, t);
}

template<class Archive, class Type, class Key, class Hash, class Compare, class Allocator >
inline void load(
	Archive & ar,
	tbb::concurrent_unordered_map<Key, Type, Hash, Compare, Allocator> &t,
	const unsigned int /* file_version */)
{
#if BOOST_VERSION <= 105800
	boost::serialization::stl::load_collection<
		Archive,
		tbb::concurrent_unordered_map<Key, Type, Hash, Compare, Allocator>,
		boost::serialization::stl::archive_input_map<
			Archive, tbb::concurrent_unordered_map<Key, Type, Hash, Compare, Allocator> >,
		boost::serialization::stl::no_reserve_imp<tbb::concurrent_unordered_map<
			Key, Type, Hash, Compare, Allocator > >
	>(ar, t);
#elif BOOST_VERSION >= 105900
	// API changed (code adapted according to upstream std::deque/vector code)
	boost::archive::library_version_type const library_version(
		ar.get_library_version()
	);
	// retrieve number of elements
	item_version_type item_version(0);
	collection_size_type count;
	ar >> BOOST_SERIALIZATION_NVP(count);
	if (boost::archive::library_version_type(3) < library_version) {
		ar >> BOOST_SERIALIZATION_NVP(item_version);
	}
	stl::collection_load_impl(ar, t, count, item_version);
#else
#error please implement
#endif
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Type, class Key, class Hash, class Compare, class Allocator >
inline void serialize(
	Archive & ar,
	tbb::concurrent_unordered_map<Key, Type, Hash, Compare, Allocator> &t,
	const unsigned int file_version)
{
	boost::serialization::split_free(ar, t, file_version);
}

} // serialization
} // namespace boost
