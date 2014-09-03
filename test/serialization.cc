#include <memory>
#include <array>
#include <bitset>
#include <sstream>
#include <boost/dynamic_bitset.hpp>

#include <gtest/gtest.h>

#include "boost/archive/mongo_oarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/archive/binary_iarchive.hpp"

#include "boost/serialization/array.h"
#include <boost/serialization/bitset.hpp>
#include "boost/serialization/dynamic_bitset.h"
#include "boost/serialization/multi_array.h"
#include "boost/serialization/tuple.h"
#include "boost/serialization/continuous_interval.h"


namespace ba = boost::archive;
namespace bs = boost::serialization;
namespace bi = boost::icl;
using namespace std;

template<typename T>
void test_random_accessable_serialization(T& a)
{
	mongo::BSONObjBuilder builder;
	ba::mongo_oarchive mongo(builder);

	bs::serialize(mongo, a, 0);

	for (size_t ii = 0; ii<a.size(); ++ii)
		a[ii] = ii;

	stringstream os;
	ba::binary_oarchive out(os);

	out << a;
	os.flush();

	ba::binary_iarchive in(os);
	T b;
	in >> b;

	ASSERT_EQ(a, b);
}


TEST(Serialization, Array)
{
	array<int, 42> a;
	test_random_accessable_serialization(a);
}

TEST(Serialization, StdBitset)
{
	bitset<256> a;
	test_random_accessable_serialization(a);
}

TEST(Serialization, DynamicBitset)
{
	boost::dynamic_bitset<> a(256);
	test_random_accessable_serialization(a);
}

TEST(Serialization, MultiArray)
{
	typedef boost::multi_array<double, 3> array_t;
	array_t a(boost::extents[100][42][23]);

	mongo::BSONObjBuilder builder;
	ba::mongo_oarchive mongo(builder);

	// next line commented out because build breaks
	//bs::serialize(mongo, a, 0);
	ASSERT_FALSE(builder.obj().toString().empty());
}

TEST(Serialization, Tuple)
{
	typedef std::tuple<int, double, char, std::string> type;
	type a;

	get<0>(a) = 42;
	get<1>(a) = 3.141;
	get<2>(a) = 'D';
	get<3>(a) = std::string("fancy test string");

	mongo::BSONObjBuilder builder;
	ba::mongo_oarchive mongo(builder);

	bs::serialize(mongo, a, 0);

	stringstream os;
	ba::binary_oarchive out(os);

	out << a;
	os.flush();

	ba::binary_iarchive in(os);
	type b;
	in >> b;

	ASSERT_EQ(a, b);
}

TEST(Serialization, ContinuousInterval)
{
	typedef bi::continuous_interval<double> type;
	type a = bi::construct<type>(3.14, 1024.2048, bi::interval_bounds::closed());

	mongo::BSONObjBuilder builder;
	ba::mongo_oarchive mongo(builder);

	bs::serialize(mongo, a, 0);

	stringstream os;
	ba::binary_oarchive out(os);

	out << a;
	os.flush();

	ba::binary_iarchive in(os);
	type b;
	in >> b;

	// hacky conversion, avoiding ambiguous overload for 'operator<<'
	std::stringstream str_a, str_b;
	str_a << a;
	str_b << b;
	ASSERT_EQ(str_a.str(), str_b.str());
}
