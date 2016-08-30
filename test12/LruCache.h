#ifndef TEST1_LRUCACHE_H
#define TEST1_LRUCACHE_H

#include <list>
#include <unordered_map>
#include <string>

template<int N>
class LruCache {

public:
    void Set(std::string key, int value);
    int Get(std::string key);

    void Trace();

private:
    void _MoveUp(std::list<std::string>::iterator &iter);

private:
    std::unordered_map<std::string, std::pair<int, std::list<std::string>::iterator>> _map;
    std::list<std::string> _lru;
    int _capacity = N;
};

#endif //TEST1_LRUCACHE_H

