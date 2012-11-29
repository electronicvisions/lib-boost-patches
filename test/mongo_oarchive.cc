#include <gtest/gtest.h>

#include "boost/archive/mongo_oarchive.hpp"

using namespace boost::archive;

typedef ::testing::Types<
	bool,
	char,
	signed char,
	unsigned char,
	wchar_t,
	//char16_t,
	//char32_t,
	short,
	unsigned short,
	int,
	unsigned int,
	long,
	unsigned long,
	long long,
	unsigned long long,
	float,
	double,
	long double> types;

template<typename T>
struct MongoBuiltin :
	public ::testing::Test
{
	typedef T type;
};

TYPED_TEST_CASE(MongoBuiltin, types);

TYPED_TEST(MongoBuiltin, Serialization)
{
	mongo::BSONObjBuilder b;
	mongo_oarchive mongo(b);

	typename TestFixture::type a;
	mongo << boost::serialization::make_nvp("value", a);

	mongo::BSONObj obj = b.obj();
	ASSERT_TRUE(!obj.toString().empty());
}
