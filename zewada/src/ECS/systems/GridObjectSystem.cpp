#include "GridObjectSystem.h"
#include "../../scene/GameObject.h"
#include "../../scene/Scene.h"

namespace Zewada {
    void GridObjectSystem::OnStart()
    {

    }

    void GridObjectSystem::OnUpdate(float dt)
    {
        for(auto& entity : m_entities)
        {
            GameObject go(entity, m_scene);
            auto& gridO = go.GetComponent<GridObject>();
            auto& transform = go.GetComponent<Transform>();
            if(transform.parent == -1)
                continue;
            if(!m_scene->Exist(m_scene->GetEntity(transform.parent)))
                continue;
            
            GameObject grid(m_scene->GetEntity(transform.parent), m_scene);
            
            auto& sprite = go.GetComponent<SpriteRenderer>();

            auto& gridTransform = grid.GetComponent<Transform>();
            auto& gridGrid = grid.GetComponent<Grid>();

            float x = gridO.gridPos.x * gridGrid.size + (0.5f * gridGrid.size);
            float y = gridO.gridPos.y * gridGrid.size + (0.5f * gridGrid.size);
            float z = 0.0f;

            go.SetPosition(glm::vec3(x, y, z));
            go.SetWorldScale(gridGrid.size, gridGrid.size);
        }
    }
}

