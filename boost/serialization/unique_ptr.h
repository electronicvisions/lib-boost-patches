#pragma once

#include "boost/serialization/serialization.h"

#include <memory>

namespace boost {
namespace serialization {

template<typename Archive, typename T, typename Deleter>
void save(Archive& ar,
		  const std::unique_ptr<T, Deleter>& t,
		  const unsigned int)
{
	T* r = t.get();
	ar << boost::serialization::make_nvp("unique_ptr", r);
}

template<typename Archive, typename T, typename Deleter>
void load(Archive& ar,
		  std::unique_ptr<T, Deleter>& t,
		  const unsigned int)
{
	T* r;
	ar >> boost::serialization::make_nvp("unique_ptr", r);
	t.reset(r);
}

template<typename Archive, typename T, typename Deleter>
void serialize(Archive& ar,
			   std::unique_ptr<T, Deleter>& t,
			   const unsigned int version)
{
	boost::serialization::split_free(ar, t, version);
}

} // namespace serialization
} // namespace boost
