#include <zpch.h>
#include "ScriptLoader.h"
#include "../../scene/ScriptableEntity.h"

namespace Zewada
{
    ScriptLoader::ScriptLoader()
    {
        m_path = boost::filesystem::path((std::filesystem::current_path().string()).c_str());
        m_path = m_path.append("scripts");
    }

    std::shared_ptr<ScriptableEntity> ScriptLoader::LoadScript(std::string symbol)
    {
        symbol = "SCRIPT_" + symbol;
        if(!Utils::Contains(m_createFunctions, symbol))
        {
            std::function<std::shared_ptr<ScriptableEntity>()> createFunction;
            try
            {
                createFunction = boost::dll::import_alias<std::shared_ptr<ScriptableEntity>()>(m_path, symbol.c_str(), boost::dll::load_mode::append_decorations);
            }
            catch(const std::exception& e)
            {
                Z_ERROR("Could not find " + symbol);
                return std::make_shared<ScriptableEntity>();
            }

            m_createFunctions.insert({symbol, createFunction});
        }

        std::shared_ptr<ScriptableEntity> script = m_createFunctions[symbol]();

        return script;
    }

    void ScriptLoader::Clear()
    {
        m_createFunctions.clear();
    }
}