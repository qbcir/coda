#ifndef __CODA_CACHE_HPP__
#define __CODA_CACHE_HPP__

#include <time.h>
#include <map>
#include "string.hpp"

template <typename Key, typename Val>
class coda_cache
{
	struct elem_t;
	typedef std::map<Key, elem_t> data_t;

	struct elem_t
	{
		Val elem;

		typename data_t::iterator prev;
		typename data_t::iterator next;

		size_t size;
		size_t time; /* time when element was created */

		elem_t(typename data_t::iterator i_prev, typename data_t::iterator i_next)
			: prev(i_prev)
			, next(i_next)
			, size(0)
		{
			time = ::time(NULL);
		}
	};

	data_t data;
	size_t size_cur;
	size_t size_max;
	size_t time_max;

	typename data_t::iterator beg_it;
	typename data_t::iterator end_it;

	void drop_last_unused();

public:
	coda_cache(size_t i_size_max, size_t i_time_max)
		: size_cur(0)
		, size_max(i_size_max)
		, time_max(i_time_max)
	{
		beg_it = data.end();
		end_it = data.end();
	}

	void get_copy(const Key &key, Val &val);
	void set(const Key &key, const Val &val);

	bool drop(typename data_t::iterator it);
	bool drop(const Key &key);

	const Val *get(const Key &key) const;

	void update_time(const Key &key);

	void dbg(std::string &res, int dbg) const;

	size_t get_size() const
	{
		return size_cur;
	}
};

#include "cache.tcc"

#endif /* __CODA_CACHE_HPP__ */
