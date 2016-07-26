#include <boost/optional.hpp>

namespace boost {

/** Provide specialization for hash_value.
 *
 * Until now, we used an implict conversion chain (optional to bool to int).
 */
template <typename T>
static size_t hash_value(boost::optional<T> const& t) {
	if (t) {
		return hash_value(*t);
	}
	return 0;
}

} // namespace boost
