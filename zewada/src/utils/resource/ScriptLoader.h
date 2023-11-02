#pragma once 

#include <boost/config.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/make_shared.hpp>
#include <boost/dll.hpp>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>

#include <unordered_map>
#include <stdexcept>
#include <vector>
#include <string>

using namespace boost;

namespace Zewada
{
    class ScriptableEntity;

    class ScriptLoader
    {
    private:
        std::unordered_map<std::string,
        std::function<std::shared_ptr<ScriptableEntity>()>> m_createFunctions;
        boost::filesystem::path m_path;
    public:
        ScriptLoader();

        std::shared_ptr<ScriptableEntity> LoadScript(std::string symbol);
        void Clear();
    };
}