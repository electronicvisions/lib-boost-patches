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
	mongo::BSONObjBuilder builder;
	mongo_oarchive mongo(builder);

	typename TestFixture::type a;
	mongo << boost::serialization::make_nvp("value", a);

	mongo::BSONObj obj = builder.obj();
	ASSERT_TRUE(!obj.toString().empty());
}

#include <array>
#include "boost/serialization/array.h"

struct A
{
	int a;
	int b;
	enum Name { x,y,z };
	Name n;
private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive& ar, unsigned int const)
	{
		ar & BOOST_SERIALIZATION_NVP(a)
		   & BOOST_SERIALIZATION_NVP(b)
		   & BOOST_SERIALIZATION_NVP(n);
	}
};

TEST(MongoOArchive, CustomType)
{
	mongo::BSONObjBuilder builder;
	mongo_oarchive mongo(builder);

	A a;
	mongo << BOOST_SERIALIZATION_NVP(a);

	// serialize named enums is broken
	ASSERT_TRUE(false);
	std::cout << builder.obj().toString() << std::endl;
}

TEST(MongoOArchive, AllMembersRegressionTest)
{
	const char name [] = { "myArray" };
	mongo::BSONObjBuilder builder;
	mongo_oarchive mongo(builder);

	std::array<int, 42> a;
	mongo << boost::serialization::make_nvp(name, a);

	mongo::BSONObj o = builder.obj();
	auto elem = o.getField(name).embeddedObject().getField("elems");
	ASSERT_EQ(43, elem.embeddedObject().nFields());
}
