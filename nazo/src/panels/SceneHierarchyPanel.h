#pragma once

#include "../utils/ZImGui.h"

using namespace Zewada;

namespace Nazo {

    class NazoApplication;

    struct InBetweenRect 
    {
        int index;
        ImRect rect;
    };

    class SceneHierarchyPanel
    {
    private:
        NazoApplication* m_application;

        std::vector<InBetweenRect> m_rects;
        const char* payLoadDragDropType = "SceneHierarchy";

        bool DoTreeNode(const GameObject& go);
        bool SceneHierarchySpaces(int* index);
    public:
        SceneHierarchyPanel(NazoApplication* application);

        void ImGui(); 
    };
}