#pragma once

#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/binary_object.hpp>

#include <boost/numeric/ublas/storage.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

namespace boost {
namespace serialization {

template<typename Archive, typename Z, typename D>
void load(Archive& ar,
		  boost::numeric::ublas::basic_range<Z, D>& t,
		  unsigned int const)
{
	Z start;
	D size;
	ar >> make_nvp("start", start)
	   >> make_nvp("size", size);
	t = boost::numeric::ublas::basic_range<Z, D>(start, size);
}

template<typename Archive, typename Z, typename D>
void save(Archive& ar,
		  boost::numeric::ublas::basic_range<Z, D> const& t,
		  unsigned int const)
{
	Z const start = t.start();
	D const size = t.size();
	ar << make_nvp("start", start)
	   << make_nvp("size", size);
}

template<typename Archive, typename Z, typename D>
void serialize(Archive& ar,
			   boost::numeric::ublas::basic_range<Z, D>& t,
			   unsigned int const v)
{
	split_free(ar, t, v);
}


// Add NVP serializers for vector & matrix

template<typename Archive, class T>
inline void save(Archive& ar,
				 boost::numeric::ublas::vector<T, boost::numeric::ublas::unbounded_array<T> > const& t,
				 unsigned int const)
{
	typedef typename boost::numeric::ublas::vector<T,
			boost::numeric::ublas::unbounded_array<T> >::size_type size_type;
	size_type size = t.size();
	size_t data_size = size * sizeof(T);
	void * data = const_cast<T*>(t.data().begin());

	ar << BOOST_SERIALIZATION_NVP(size);
	ar << make_nvp("data", make_binary_object(data, data_size));
}

template<typename Archive, class T>
inline void load(Archive& ar,
				 boost::numeric::ublas::vector<T, boost::numeric::ublas::unbounded_array<T> > & t,
				 unsigned int const)
{
	typedef typename boost::numeric::ublas::vector<T,
			boost::numeric::ublas::unbounded_array<T> >::size_type size_type;
	size_type size;

	ar >> BOOST_SERIALIZATION_NVP(size);

	t.resize(size);
	size_t data_size = size * sizeof(T);
	void * data = const_cast<T*>(t.data().begin());

	ar >> make_nvp("data", make_binary_object(data, data_size));
}

template<typename Archive, class T>
inline void serialize(Archive& ar,
                      boost::numeric::ublas::vector<T, boost::numeric::ublas::unbounded_array<T> > & t,
                      unsigned int const version)
{
	split_free(ar, t, version);
}


template<typename Archive, class T, class L>
inline void save(Archive& ar,
				 boost::numeric::ublas::matrix<T, L, boost::numeric::ublas::unbounded_array<T> > const& t,
				 unsigned int const)
{
	typedef typename boost::numeric::ublas::matrix<T, L,
			boost::numeric::ublas::unbounded_array<T> >::size_type size_type;
	size_type size1 = t.size1(), size2 = t.size2();
	size_t data_size = size1 * size2 * sizeof(T);
	void * data = const_cast<T*>(t.data().begin());

	ar << BOOST_SERIALIZATION_NVP(size1)
	   << BOOST_SERIALIZATION_NVP(size2);
	ar << make_nvp("data", make_binary_object(data, data_size));
}

template<typename Archive, class T, class L>
inline void load(Archive& ar,
				 boost::numeric::ublas::matrix<T, L, boost::numeric::ublas::unbounded_array<T> > & t,
				 unsigned int const)
{
	typedef typename boost::numeric::ublas::matrix<T, L, boost::numeric::ublas::unbounded_array<T> >::size_type size_type;
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
                      boost::numeric::ublas::matrix<T, L, boost::numeric::ublas::unbounded_array<T> > & t,
                      unsigned int const version)
{
	split_free(ar, t, version);
}

} // namespace serialization
} // namespace boost
