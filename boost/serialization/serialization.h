#pragma once

// This header provides the most important boost serialization includes
// Only Archivetypes included here can be used!!!

// Provides BOOST_SERIALIZATION_NVP(mPositions) and boost::make_nvp
#include <boost/serialization/nvp.hpp>
// Provides BOOST_CLASS_EXPORT_KEY(...) and BOOST_CLASS_EXPORT_IMPLEMENTATION(...)
#include <boost/serialization/export.hpp>

#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/split_free.hpp>


// Supportet archives, these are included to make BOOST_CLASS_EXPORT_IMPLEMENTATION
// work correctly
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#if defined(__ESTER_MPI__)
#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/packed_oarchive.hpp>
#endif

// Some Datatypes
#include <boost/serialization/set.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/weak_ptr.hpp>
