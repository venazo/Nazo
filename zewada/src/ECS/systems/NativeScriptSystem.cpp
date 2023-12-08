#include "NativeScriptSystem.h"
#include "../../scene/ScriptableEntity.h"
#include "../../scene/scene.h"

namespace Zewada
{
    void NativeScriptSystem::OnStart()
    {
        m_scene->GetApplication()->GetScriptLoader()->Clear();

        for(auto entity : m_entities)
        {  
            GameObject go(entity, m_scene);
            auto& nativeScript = go.GetComponent<NativeScript>();
            if(nativeScript.className == "NONE")
                continue;

            std::shared_ptr<ScriptableEntity> script = m_scene->GetApplication()->GetScriptLoader()->LoadScript(nativeScript.className);
            nativeScript.script = script;
            nativeScript.script->SetGameObject(go);
            nativeScript.script->OnStart();
        }
    }

    void NativeScriptSystem::OnUpdate(float dt)
    {
        for(auto entity : m_entities)
        {
            GameObject go(entity, m_scene);
            auto& nativeScript = go.GetComponent<NativeScript>();
            if(nativeScript.className == "NONE")
                continue;

            nativeScript.script->OnUpdate(dt);
        }
    }
}