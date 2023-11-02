#pragma once

#include <unordered_map>
#include <map>

namespace Zewada
{
    struct Utils
    {
        template<class T, class U>
        static bool Contains(std::unordered_map<T, U>& map, T& value)
        {
            bool result = false;

            for (auto& pair : map)
            {
                if (pair.first == value)
                    result = true;
            }

            return result;
        }

        template<class T, class U>
        static bool Contains(std::map<T, U>& map, T& value)
        {
            bool result = false;

            for (auto& pair : map)
            {
                if (pair.first == value)
                    result = true;
            }

            return result;
        }
    };
}