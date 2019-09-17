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

#define EXPLICIT_INSTANTIATE_BOOST_SERIALIZE_FREE(CLASS_NAME) \
template void boost::serialization::serialize(boost::archive::text_iarchive&,   CLASS_NAME&, const unsigned int); \
template void boost::serialization::serialize(boost::archive::text_oarchive&,   CLASS_NAME&, const unsigned int); \
template void boost::serialization::serialize(boost::archive::binary_oarchive&, CLASS_NAME&, const unsigned int); \
template void boost::serialization::serialize(boost::archive::binary_iarchive&, CLASS_NAME&, const unsigned int); \
template void boost::serialization::serialize(boost::archive::xml_oarchive&,    CLASS_NAME&, const unsigned int); \
template void boost::serialization::serialize(boost::archive::xml_iarchive&,    CLASS_NAME&, const unsigned int);
// Add new default archivers here...

#define EXPLICIT_INSTANTIATE_BOOST_SERIALIZE_CONSTRUCT_DATA(CLASS_NAME) \
template void boost::serialization::load_construct_data(boost::archive::text_iarchive&, CLASS_NAME * h, unsigned int const); \
template void boost::serialization::save_construct_data(boost::archive::text_oarchive&, CLASS_NAME const* h, unsigned int const); \
template void boost::serialization::load_construct_data(boost::archive::binary_iarchive&, CLASS_NAME * h, unsigned int const); \
template void boost::serialization::save_construct_data(boost::archive::binary_oarchive&, CLASS_NAME const* h, unsigned int const); \
template void boost::serialization::load_construct_data(boost::archive::xml_iarchive&, CLASS_NAME * h, unsigned int const); \
template void boost::serialization::save_construct_data(boost::archive::xml_oarchive&, CLASS_NAME const* h, unsigned int const);
// Add new default archivers here...
