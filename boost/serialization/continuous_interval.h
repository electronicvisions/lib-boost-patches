#pragma once

#include <boost/serialization/split_free.hpp>
#include <boost/icl/continuous_interval.hpp>
#include <boost/serialization/utility.hpp>

namespace boost {
namespace serialization {

    template <typename Archive, typename V>
        void save(Archive& ar, boost::icl::continuous_interval<V> const& di, unsigned) {
            boost::icl::bound_type bb = di.bounds().bits();
            V l  = di.lower();
            V u  = di.upper();

            ar << BOOST_SERIALIZATION_NVP(bb)
			   << BOOST_SERIALIZATION_NVP(l)
			   << BOOST_SERIALIZATION_NVP(u);
        }

    template <typename Archive, typename V>
        void load(Archive& ar, boost::icl::continuous_interval<V>& di, unsigned) {
            boost::icl::bound_type bb = di.bounds().bits();
            V    l, u;

            ar >> BOOST_SERIALIZATION_NVP(bb)
			   >> BOOST_SERIALIZATION_NVP(l)
			   >> BOOST_SERIALIZATION_NVP(u);

			di = boost::icl::continuous_interval<V>(l, u, boost::icl::interval_bounds(bb));
        }

    template <typename Archive, typename V>
        void serialize(Archive& ar, boost::icl::continuous_interval<V>& di, unsigned v) {
            split_free(ar, di, v);
        }

} // serialization
} //boost
