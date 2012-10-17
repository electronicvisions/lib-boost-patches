#pragma once

#include <tuple>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>

// serialization helper for std::array
namespace boost {
namespace serialization {

template<size_t N>
struct helper_tuple
{
	template<class Archive, typename... Args>
	static void serialize(
		Archive & ar, std::tuple<Args...>& t,
		unsigned int const version)
	{
		helper_tuple<N-1>::serialize(ar, t, version);
		ar & make_nvp("value", std::get<N-1>(t));
	}
};

template<>
struct helper_tuple<0>
{
	template<class Archive, typename... Args>
	static void serialize(
		Archive &, std::tuple<Args...>&,
		unsigned int const)
	{}
};

template<class Archive, typename... Args>
void serialize(
	Archive & ar, std::tuple<Args...> & t,
	unsigned int const version)
{
	helper_tuple<sizeof...(Args)>::serialize(ar, t, version);
}

} // namespace serialization
} // namespace boost
