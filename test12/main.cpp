#include <iostream>
#include <memory>
#include "LruCache.h"
#include "LruCache.cpp"

int main()
{
    std::unique_ptr<LruCache<3>> cache(new LruCache<3>());

    std::cout << "initializing:" << std::endl;
    cache->Set("apple", 1);
    cache->Set("banana", 2);
    cache->Set("pearl", 3);
    cache->Trace();

    std::cout << "getting orange: " << cache->Get("orange") << std::endl;
    cache->Trace();

    std::cout << "getting apple: " << cache->Get("apple") << std::endl;
    cache->Trace();

    std::cout << "adding grape:" << std::endl;
    cache->Set("grape", 4);
    cache->Trace();

    return 0;
}
