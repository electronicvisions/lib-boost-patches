#pragma once

// Copyright (c) 2012, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the GPLv2 or newer

#include <vector>
#include <cstddef>
#include <memory>
#include <cassert>
#include <string>

#include <mongo/client/dbclient.h>
// Uh, ugly, this header leaks macros...
#undef assert

#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/archive/detail/common_oarchive.hpp>


#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {
namespace detail {

template<typename T>
class cond_deleter
{
private:
	bool cond;
public:
	cond_deleter(bool del = true) : cond(del) {}

	void operator() (T* b)
	{
		if (cond)
			delete b;
	}
};

} // detail


class mongo_oarchive :
    public detail::common_oarchive<mongo_oarchive>
{
private:
	friend class detail::interface_oarchive<mongo_oarchive>;
	friend class save_access;

	typedef mongo::BSONObjBuilder type;
	typedef std::unique_ptr<type, detail::cond_deleter<type>> value_type;

	std::vector<value_type> _builder;
	char const* _name;

	type& penultimate()
	{
		assert(_builder.size()>1);
		return **(_builder.end()-2);
	}

    // Anything not an attribute and not a name-value pair is an
    // error and should be trapped here.
    template<class T>
    void save_override(T& t, BOOST_PFTO int x)
    {
        // If your program fails to compile here, its most likely due to
        // not specifying an nvp wrapper around the variable to
        // be serialized.
        BOOST_MPL_ASSERT((serialization::is_wrapper<T>));
        this->detail::common_oarchive<mongo_oarchive>::save_override(t, x);
    }

    // special treatment for name-value pairs.
    template<class T>
    void save_override(boost::serialization::nvp<T> const& t, int)
	{
		// if name == NULL then Enum ... seriously!!! WTF!1!!
		if (t.name() == nullptr) {
			save_enum(t.const_value());
			return;
		}

		_name = t.name();
		_builder.emplace_back(new type);

		detail::common_oarchive<mongo_oarchive>::save_override(t.const_value(), 0);

		mongo::BSONObj obj = _builder.back()->obj();
		_builder.pop_back();

		if (!obj.isEmpty())
			_builder.back()->append(t.name(), obj);
    }

    // specific overrides for attributes - not name value pairs so we
    // want to trap them before the above "fall through"
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
    void save(T const& t);

	// required overloads for boost serialization
    void save(version_type const& t);
    void save(boost::serialization::item_version_type const& t);
	void save(boost::serialization::collection_size_type const& t);

	// required overloads for incomplete BSONObjBuilder.append interface
	void save(long double const& t);
	void save(long int const& t);
	void save(long unsigned int const& t);
	void save(long long unsigned int const& t);

	// required for strings
	void save(std::string const& s);

	// requirest for enum types (null pointer for the win!)
	template<typename T>
	void save_enum(T const&) {}
	void save_enum(int const& e) { save(e);}

public:
	struct use_array_optimization
	{
		template<typename T>
		struct apply
		{
			typedef boost::mpl::true_ type;
		};
	};

    mongo_oarchive(type& obj, unsigned int flags = 0) :
		_builder(), _name()
	{
		static_cast<void>(flags);
		_builder.emplace_back(&obj, detail::cond_deleter<type>(false));
	}
    ~mongo_oarchive() {}

    void save_binary(void const* address, std::size_t count);

	template<typename T>
	void save_array(boost::serialization::array<T> const& a, unsigned int x)
	{
		using boost::serialization::make_nvp;
		for (size_t ii = 0; ii<a.count(); ++ii)
		{
			std::string s = std::to_string(ii);
			save_override(make_nvp(s.c_str(), *(a.address()+ii)), x);
		}
	}
};


namespace detail {

template<>
struct save_array_type<mongo_oarchive>
{
    template<class T>
    static void invoke(mongo_oarchive& ar, T const& t)
	{
        typedef typename std::remove_extent<T>::type value_type;

        // consider alignment
        std::size_t c = sizeof(t) / sizeof(value_type);

        boost::serialization::collection_size_type count(c);
        ar << BOOST_SERIALIZATION_NVP(count);
        ar << serialization::make_array(static_cast<value_type const*>(&t[0]), count);
    }

    static void invoke(mongo_oarchive& ar, char const* t)
	{
		ar.save_binary(t, std::strlen(t) + 1);
    }
};

} // detail




typedef mongo_oarchive naked_mongo_oarchive;

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::mongo_oarchive)

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::archive::mongo_oarchive)



namespace boost {
namespace archive {

inline
void mongo_oarchive::save_override(
	object_id_type const& t, int)
{
	_builder.back()->append("_object_id", t);
}
inline
void mongo_oarchive::save_override(
	object_reference_type const& t, int)
{
	_builder.back()->append("_object_reference", t);
}
inline
void mongo_oarchive::save_override(
	version_type const& t, int)
{
	_builder.back()->append("_version", t);
}
inline
void mongo_oarchive::save_override(
	class_id_type const& t, int)
{
	_builder.back()->append("_class_id", t);
}
inline
void mongo_oarchive::save_override(
	class_id_reference_type const& t, int)
{
	_builder.back()->append("_class_id_reference", t);
}
inline
void mongo_oarchive::save_override(
	class_id_optional_type const& t, int)
{
	_builder.back()->append("_class_id_optional", t);
}
inline
void mongo_oarchive::save_override(
	class_name_type const& t, int)
{
	_builder.back()->append("_class_name", t);
}
inline
void mongo_oarchive::save_override(
	tracking_type const& t, int)
{
	_builder.back()->append("_tracking", t);
}


template<class T>
inline
void mongo_oarchive::save(T const& t)
{
	penultimate().append(_name, t);
}
inline
void mongo_oarchive::save(long double const& t)
{
	penultimate().append(_name, static_cast<double const&>(t));
}
inline
void mongo_oarchive::save(long int const& t)
{
	penultimate().appendNumber(_name, static_cast<long long const&>(t));
}
inline
void mongo_oarchive::save(long unsigned int const& t)
{
	penultimate().appendNumber(_name, static_cast<size_t const&>(t));
}
inline
void mongo_oarchive::save(long long unsigned int const& t)
{
	penultimate().appendNumber(_name, static_cast<size_t const&>(t));
}

inline
void mongo_oarchive::save(version_type const& t)
{
	save(static_cast<const unsigned int>(t));
}
inline
void mongo_oarchive::save(boost::serialization::item_version_type const& t)
{
	save(static_cast<const unsigned int>(t));
}
inline
void mongo_oarchive::save(boost::serialization::collection_size_type const& t)
{
	penultimate().appendNumber(_name, static_cast<size_t>(t));
}
inline
void mongo_oarchive::save(std::string const& s)
{
	save_binary(s.c_str(), s.size()+1);
}

inline
void mongo_oarchive::save_binary(
	void const* address, std::size_t count)
{
	penultimate().append(_name, static_cast<char const*>(address), count);
}

} // namespace archive
} // namespace boost
