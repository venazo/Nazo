#pragma once

namespace Zewada 
{
    enum BodyType {
        Static,
        Dynamic,
        Kinematic
    };

    extern std::unordered_map<BodyType, std::string> bodyType2Names;
    extern std::unordered_map<std::string, BodyType> names2BodyType;
}