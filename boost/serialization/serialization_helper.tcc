#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>


// Explicitly instantiate the templated serializers
#define EXPLICIT_INSTANTIATE_BOOST_SERIALIZE(CLASS_NAME) \
template void CLASS_NAME ::serialize(boost::archive::text_iarchive&,   const unsigned int); \
template void CLASS_NAME ::serialize(boost::archive::text_oarchive&,   const unsigned int); \
template void CLASS_NAME ::serialize(boost::archive::binary_oarchive&, const unsigned int); \
template void CLASS_NAME ::serialize(boost::archive::binary_iarchive&, const unsigned int); \
template void CLASS_NAME ::serialize(boost::archive::xml_oarchive&,    const unsigned int); \
template void CLASS_NAME ::serialize(boost::archive::xml_iarchive&,    const unsigned int);
// Add new default archivers here...
