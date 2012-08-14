#pragma once

#include <boost/multi_array.hpp>

#include <boost/serialization/array.hpp>

#include "boost/serialization/serialization.h"

namespace boost {
namespace serialization {

template<typename Archive, typename T, size_t N>
inline void save(Archive& ar, const boost::multi_array<T, N>& t, unsigned int const) {
	ar << make_nvp("dimensions", make_array(t.shape(), N));
	ar << make_nvp("data", make_array(t.data(), t.num_elements()));
}

template<typename Archive, typename T, size_t N>
inline void load(Archive& ar, boost::multi_array<T, N>& t, unsigned int const) {
	typedef typename boost::multi_array<T, N>::size_type size_type;

	boost::array<size_type, N> dimensions;
	ar >> make_nvp("dimensions", make_array(dimensions.c_array(), N));
	t.resize(dimensions);
	ar >> make_nvp("data", make_array(t.data(), t.num_elements()));
}

template<typename Archive, typename T, size_t N>
void serialize(Archive& ar, boost::multi_array<T, N>& t,
			   unsigned int const version) {
	split_free(ar, t, version);
}

} // namespace serialization
} // namespace boost
