
#include <map>

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
    // Part 1 is to check for the empty interval: !(keyNegin < keyEnd)
    if (!(keyBegin < keyEnd)) {
      return; // just exit
    }


    // Part 2 - check values at the boundaries at the keyBegin and keyEnd
    
    // save val locally
    V newVal = std::forward<V_forward>(val);

    // The value in effect at keyBegin is either m_valBegin or the value from the previous boundary.
    auto leftVal = (*this)[keyBegin];
    auto rightVal = (*this)[keyEnd];
    // V leftVal = (itLow == m_map.begin() ? m_valBegin : std::prev(itLow)->second);
    // V rightVal = (itHigh == m_map.begin() ? m_valBegin : std::prev(itHigh)->second);

    // Find the first map entry not less than keyBegin.
    auto itLow = m_map.lower_bound(keyBegin);
    // Similarly, find the first map entry not less than keyEnd.
    auto itHigh = m_map.lower_bound(keyEnd);
    // Erase all map entries that fall in [keyBegin, keyEnd).
    m_map.erase(itLow, itHigh);
    
    // Part 3 - clean all previous boundaries that in our current interval
      
    // Part 4 - change new boundraies if they are not matched
    for (auto i=keyBegin; i<keyEnd; i++) {
      m_map[i] = val;
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

/*
*
  template<typename V_forward>
  void assign(K const& keyBegin, K const& keyEnd, V_forward&& val)
    requires(std::is_same_v<std::remove_cvref_t<V_forward>, V>)
  {
    if (!(keyBegin < keyEnd))
      return;
    
    const V value_left = (*this)[keyBegin];
    const V value_right = (*this)[keyEnd];

    auto it_low = m_map.lower_bound(keyBegin);
    auto it_high = m_map.lower_bound(keyEnd);
    m_map.erase(it_low, it_high);

    // Ensure first entry is not same as m_valBegin
    if (!m_map.empty() && m_map.begin()->second == m_valBegin) {
        m_map.erase(m_map.begin());
    }

    if (value_left != val) {
      auto it_begin = m_map.emplace_hint(m_map.end(), keyBegin, std::forward<V_forward>(val));

      // Check previous entry
      if (it_begin != m_map.begin()) {
        auto prev_it = std::prev(it_begin);
        if (prev_it->second == it_begin->second) {
          m_map.erase(it_begin);
          it_begin = prev_it;
          }
        } else {
          if (m_valBegin == it_begin->second) {
            m_map.erase(it_begin);
          }
        }

        // Check next entry
        auto next_it = std::next(it_begin);
        if (next_it != m_map.end() && next_it->second == it_begin->second) {
          m_map.erase(it_begin);
        }
      }

      if (value_right != val) {
        auto it_end = m_map.emplace_hint(m_map.end(), keyEnd, value_right);

      // Check previous entry
      if (it_end != m_map.begin()) {
        auto prev_it = std::prev(it_end);
        if (prev_it->second == it_end->second) {
          m_map.erase(it_end);
          it_end = prev_it;
        }
      }

      // Check next entry
      auto next_it = std::next(it_end);
      if (next_it != m_map.end() && next_it->second == it_end->second) {
        m_map.erase(it_end);
      }
    }

    // Re-check first entry after all operations
    if (!m_map.empty() && m_map.begin()->second == m_valBegin) {
      m_map.erase(m_map.begin());
    }
}
*
*/
