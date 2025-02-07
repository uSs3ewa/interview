#include <map>
#include <type_traits>
#include <utility>      
#include <iterator>     

template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	template<typename V_forward>
	interval_map(V_forward&& val)
	: m_valBegin(std::forward<V_forward>(val))
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	template<typename V_forward>
	void assign( K const& keyBegin, K const& keyEnd, V_forward&& val )
		requires (std::is_same<std::remove_cvref_t<V_forward>, V>::value)
	{
    // Part 1: Check for empty interval
    if (!(keyBegin < keyEnd)) {
        return; // Just exit
    }

    // Part 2: Save val locally to avoid extra copies
    V newVal = std::forward<V_forward>(val);

    // Find boundaries
    auto itLeft = m_map.lower_bound(keyBegin);
    auto itRight = m_map.lower_bound(keyEnd);

    // Determine values at keyBegin and keyEnd **without assuming default constructibility**
    std::optional<V> leftVal;
    if (itLeft != m_map.begin()) {
        leftVal = std::prev(itLeft)->second;
    }

    std::optional<V> rightVal;
    if (itRight != m_map.begin()) {
        rightVal = std::prev(itRight)->second;
    }

    // Part 3: Remove old values in [keyBegin, keyEnd)
    m_map.erase(itLeft, itRight);

    // Part 4: Insert new boundaries if necessary

    // Insert keyBegin if necessary
    if (!leftVal.has_value() || (*leftVal < newVal) || (newVal < *leftVal)) {
        m_map.insert({ keyBegin, newVal });
    }

    // Restore keyEnd if necessary
    if (!rightVal.has_value() || (*rightVal < newVal) || (newVal < *rightVal)) {
        auto itEnd = m_map.insert({ keyEnd, *rightVal }).first;
        // Ensure prevIt is valid and remove redundant boundary
        if (m_map.size() > 1 && itEnd != m_map.begin()) {
            auto prevIt = std::prev(itEnd);
            if (!(*prevIt->second < itEnd->second) && !(itEnd->second < *prevIt->second)) { 
                m_map.erase(itEnd);
            }
        }
    }
  }

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

