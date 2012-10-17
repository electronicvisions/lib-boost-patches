#pragma once

#include "boost/serialization/serialization.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/storage.hpp>

namespace ublas = boost::numeric::ublas;

namespace boost {
namespace serialization {

template<typename Archive>
inline void save(Archive& ar, ublas::range const& t, unsigned int const) {

	typedef typename ublas::range::size_type size_type;
	size_type start = t.start(), size = t.size();

	ar << make_nvp("start", start);
	ar << make_nvp("size",  size);
}

template<typename Archive>
inline void load(Archive& ar, ublas::range& t, unsigned int const) {

	typedef typename ublas::range::size_type size_type;
	size_type start, size;

	ar >> make_nvp("start", start);
	ar >> make_nvp("size",  size);

	t = ublas::range(start, size);
}

template<typename Archive>
void serialize(Archive& ar, ublas::range& t,
			   unsigned int const version) {
	split_free(ar, t, version);
}

// Fix broken matrix & vector serialisation

template<typename Archive, class T>
inline void save(Archive& ar, ublas::vector<T, ublas::unbounded_array<T> > const& t, unsigned int const)
{
	typedef typename ublas::vector<T, ublas::unbounded_array<T> >::size_type size_type;
	size_type size = t.size();
	size_t data_size = size * sizeof(T);
	void * data = const_cast<T*>(t.data().begin());

	ar << BOOST_SERIALIZATION_NVP(size);
	ar << make_nvp("data", make_binary_object(data, data_size));
}

template<typename Archive, class T>
inline void load(Archive& ar, ublas::vector<T,ublas::unbounded_array<T> > & t, unsigned int const)
{
	typedef typename ublas::vector<T, ublas::unbounded_array<T> >::size_type size_type;
	size_type size;

	ar >> BOOST_SERIALIZATION_NVP(size);

	t.resize(size);
	size_t data_size = size * sizeof(T);
	void * data = const_cast<T*>(t.data().begin());

	ar >> make_nvp("data", make_binary_object(data, data_size));
}

template<typename Archive, class T>
inline void serialize(Archive& ar,
                      ublas::vector<T, ublas::unbounded_array<T> > & t,
                      unsigned int const version)
{
	split_free(ar, t, version);
}


template<typename Archive, class T, class L>
inline void save(Archive& ar, ublas::matrix<T, L, ublas::unbounded_array<T> > const& t, unsigned int const)
{
	typedef typename ublas::matrix<T, L, ublas::unbounded_array<T> >::size_type size_type;
	size_type size1 = t.size1(), size2 = t.size2();
	size_t data_size = size1 * size2 * sizeof(T);
	void * data = const_cast<T*>(t.data().begin());

	ar << BOOST_SERIALIZATION_NVP(size1)
	   << BOOST_SERIALIZATION_NVP(size2);
	ar << make_nvp("data", make_binary_object(data, data_size));
}

template<typename Archive, class T, class L>
inline void load(Archive& ar, ublas::matrix<T, L, ublas::unbounded_array<T> > & t, unsigned int const)
{
	typedef typename ublas::matrix<T, L, ublas::unbounded_array<T> >::size_type size_type;
	size_type size1, size2;

	ar >> BOOST_SERIALIZATION_NVP(size1)
	   >> BOOST_SERIALIZATION_NVP(size2);

	t.resize(size1, size2);
	size_t data_size = size1 * size2 * sizeof(T);
	void * data = const_cast<T*>(t.data().begin());

	ar >> make_nvp("data", make_binary_object(data, data_size));
}

template<typename Archive, class T, class L>
inline void serialize(Archive& ar,
                      ublas::matrix<T, L, ublas::unbounded_array<T> > & t,
                      unsigned int const version)
{
	split_free(ar, t, version);
}

} // namespace serialization
} // namespace boost
