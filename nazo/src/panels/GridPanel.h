#pragma once 

#include "../utils/ZImGui.h"
#include <Zewada.h>
#include <imgui_internal.h>

using namespace Zewada;

namespace Nazo
{
    class NazoApplication;

    class GridPanel
    {
        private:
            std::shared_ptr<GameObject> m_activeGameObject;

            std::shared_ptr<GameObject> m_go;
            std::map<std::string, std::vector<std::shared_ptr<Sprite>>>* m_groups;
            std::vector<std::shared_ptr<Sprite>>* m_sprites;
            std::string m_activeSprites;
            std::string m_activeWriting;
            NazoApplication* m_application;
        public:
            GridPanel(NazoApplication* application);
            void SetActiveGameObject(std::shared_ptr<GameObject> go);
            void OnUpdate(float dt);
           
            void ImGui();

            bool IsDrawing() {return m_go != nullptr;}

    };
}