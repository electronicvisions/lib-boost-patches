#pragma once


#include <iostream>
#include <vector>
#include <cstddef>
#include <memory>

#include <mongo/client/dbclient.h>

#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/archive/detail/common_oarchive.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

using namespace std;

namespace boost {
namespace archive {

class mongo_oarchive :
    public detail::common_oarchive<mongo_oarchive>
{
private:
    friend class detail::interface_oarchive<mongo_oarchive>;
    friend class save_access;

	mongo::BSONObj& _obj;
	std::vector<std::unique_ptr<mongo::BSONObjBuilder>> _builder;
	char const* _name;


    // Anything not an attribute and not a name-value pair is an
    // error and should be trapped here.
    template<class T>
    void save_override(T& t, BOOST_PFTO int)
    {
        // If your program fails to compile here, its most likely due to
        // not specifying an nvp wrapper around the variable to
        // be serialized.
        static_assert(serialization::is_wrapper<T>::value, "missing NVP wrapper");
		throw std::runtime_error("this should never happen kind of exception");
    }

    // special treatment for name-value pairs.
    typedef detail::common_oarchive<mongo_oarchive> detail_common_oarchive;
    template<class T>
    void save_override(boost::serialization::nvp<T> const& t, int)
	{
		_name = t.name();
		_builder.emplace_back(new mongo::BSONObjBuilder);

		this->detail_common_oarchive::save_override(t.const_value(), 0);

		mongo::BSONObj obj = _builder.back()->obj();
		_builder.pop_back();

		if (!obj.isEmpty())
			_builder.back()->append(t.name(), obj);
    }

    // specific overrides for attributes - not name value pairs so we
    // want to trap them before the above "fall through"
	// TODO: do we want them in the DB, i'm afraid we should
	void save_override(object_id_type const& t, int);
	void save_override(object_reference_type const& t, int);
	void save_override(version_type const& t, int);
	void save_override(class_id_type const& t, int);
	void save_override(class_id_optional_type const& t, int);
	void save_override(class_id_reference_type const& t, int);
	void save_override(class_name_type const& t, int);
	void save_override(tracking_type const& t, int);


	// detail_common_oarchive::save_override calls save functions
	template<class T>
    void save(T const& t)
	{
		(*(_builder.end()-2))->append(_name, t);
    }
    void save(version_type const& t){ save(static_cast<const unsigned int>(t)); }
    void save(boost::serialization::item_version_type const& t){ save(static_cast<const unsigned int>(t)); }
    //void save(const char* t);
    //void save(const std::string &s);

public:
    mongo_oarchive(mongo::BSONObj& obj, unsigned int flags = 0) :
		_obj(obj), _builder(), _name()
	{
		_builder.emplace_back(new mongo::BSONObjBuilder);
		//if(0 == (flags & no_header))
			//;
		//no_header = 1,  // suppress archive header info
		//no_codecvt = 2,  // suppress alteration of codecvt facet
		//no_xml_tag_checking = 4,   // suppress checking of xml tags
		//no_tracking = 8,           // suppress ALL tracking
		//flags_last = 8
	}
    ~mongo_oarchive()
	{
		_obj = _builder.back()->obj();
	}

    void save_binary(void const* address, std::size_t count);
};


typedef mongo_oarchive naked_mongo_oarchive;

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::mongo_oarchive)

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas




namespace boost {
namespace archive {

void mongo_oarchive::save_override(
	object_id_type const& t, int)
{
}
void mongo_oarchive::save_override(
	object_reference_type const& t, int)
{
}
void mongo_oarchive::save_override(version_type const& t, int)
{
}
void mongo_oarchive::save_override(class_id_type const& t, int)
{
}
void mongo_oarchive::save_override(
	class_id_reference_type const& t, int)
{
}
void mongo_oarchive::save_override(
	class_id_optional_type const& t, int)
{
}
void mongo_oarchive::save_override(
	class_name_type const& t, int)
{
}
void mongo_oarchive::save_override(
	tracking_type const& t, int)
{
}

void mongo_oarchive::save_binary(
	void const* address, std::size_t count)
{
	throw std::runtime_error("not implemented");
}

} // namespace archive
} // namespace boost
