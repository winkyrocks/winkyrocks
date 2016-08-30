#include <iostream>
#include <limits>
#include "LruCache.h"

template<int N>
void LruCache<N>::Trace()
{
    for (auto key : _lru)
    {
        std::cout << "->" << key;
        auto iter = _map.find(key);
        std::cout << "(" << iter->second.first << ") ";
    }

    std::cout << std::endl;
}

template<int N>
void LruCache<N>::Set(std::string key, int value)
{
    auto iter = _map.find(key);
    if (iter == _map.end())
    {
        _lru.emplace_front(key);
        _map.emplace(key, std::make_pair(value, _lru.begin()));

        if ((int)_lru.size() > _capacity)
        {
            auto iterpop = _lru.end();
            std::string keyToEvict = *(--iterpop);
            _lru.erase(iterpop);
            _map.erase(keyToEvict);
        }
    }
    else
    {
        iter->second.first = value;
        auto iterlru = iter->second.second;
        _MoveUp(iterlru);
    }
}

template<int N>
int LruCache<N>::Get(std::string key)
{
    auto iter = _map.find(key);
    if (iter == _map.end())
    {
        return std::numeric_limits<int>::min();
    }

    auto iterlru = iter->second.second;
    _MoveUp(iterlru);

    return iter->second.first;
}

template<int N>
void LruCache<N>::_MoveUp(std::list<std::string>::iterator &iter)
{
    std::string key = *iter;
    _lru.erase(iter);
    _lru.emplace_front(key);
    iter = _lru.begin();
}
