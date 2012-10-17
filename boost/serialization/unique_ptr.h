#pragma once

#include "boost/serialization/serialization.h"

#include <memory>

namespace boost {
namespace serialization {

template<class Archive, class T>
void save( Archive & ar,
           const std::unique_ptr< T, std::default_delete<T> > & t,
           const unsigned int /* version */
           ){
	T* r = t.get();
	ar << boost::serialization::make_nvp("unique_ptr", r);
}

template<class Archive, class T>
void load( Archive & ar,
           std::unique_ptr< T, std::default_delete<T> > & t,
           const unsigned int /* version */
           ){
	T* r;
	ar >> boost::serialization::make_nvp("unique_ptr", r);
	t.reset(r);
}
template<class Archive, class T>
void serialize( Archive& ar,
                std::unique_ptr< T, std::default_delete<T> > & t,
                const unsigned int version
                ){
	boost::serialization::split_free(ar, t, version);
}

} // namespace serialization
} // namespace boost
