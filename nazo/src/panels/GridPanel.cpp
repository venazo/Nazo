#include "GridPanel.h"
#include "../layers/ImGuiLayer.h"
#include "../NazoApplication.h"

namespace Nazo
{
    GridPanel::GridPanel(NazoApplication* application)
    {
        m_application = application;
    }

    void GridPanel::SetActiveGameObject(std::shared_ptr<GameObject> go)
    {
        if(m_go != nullptr)
        {
            m_go->Destroy();
            m_go = nullptr;
        }

        m_activeGameObject = go;
    }

    void GridPanel::ImGui()
    {
        ImGui::Begin("GridPanel");

        if(m_activeGameObject == nullptr)
        {
            ImGui::End();
            return;
        }

        if(!m_activeGameObject->HasComponent<Grid>())
        {
            ImGui::End();
            return;
        }

        for(auto& sprite : m_sprites)
        {
            if(ZImGui::ImageButtonWithName(std::filesystem::path(sprite->GetTexture()->GetPath()).filename().string(), (ImTextureID)sprite->GetTexture()->GetID()))
            {
                Entity entity = m_application->GetSceneManager()->GetActiveScene()->CreateEntity("GridObject");
                if(m_go != nullptr)
                    m_go->Destroy();
                m_go = std::make_shared<GameObject>(entity, m_application->GetSceneManager()->GetActiveScene());
                m_go->AddComponent<SpriteRenderer>();
                auto& spriteRenderer = m_go->GetComponent<SpriteRenderer>();
                spriteRenderer.sprite = sprite;
                spriteRenderer.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                m_go->AddComponent<GridObject>(); 
                m_activeGameObject->GetComponent<Transform>().children.push_back(m_go->GetComponent<Tag>().id);
                m_go->GetComponent<Transform>().parent = m_activeGameObject->GetComponent<Tag>().id;
            }

            if(ImGui::BeginPopupContextWindow(sprite->GetTexture()->GetPath().c_str()))
            {
                if(ImGui::MenuItem("Delete"))
                {
                    m_sprites.erase(std::remove(m_sprites.begin(), m_sprites.end(), sprite),  m_sprites.end());
                }
            }
        }

        ZImGui::ImageButtonWithName("Add Texture", (ImTextureID)m_application->GetAssetPool()->GetTexture("assets/nazo/textures/plusIcon.png")->GetID());

       	if(ImGui::BeginDragDropTarget())
	    {
            std::shared_ptr<Sprite> sprite = nullptr;
            const ImGuiPayload* payLoadObj = ImGui::AcceptDragDropPayload("Texture");
			const ImGuiPayload* payLoadSprite = ImGui::AcceptDragDropPayload("Sprite");
			if(payLoadObj != nullptr)
			{
				const wchar_t* path = (wchar_t*)payLoadObj->Data;
				std::filesystem::path scenePath(path);
				sprite = std::make_shared<Sprite>(m_application->GetAssetPool()->GetTexture(scenePath.string().c_str()));
			}
			else if(payLoadSprite != nullptr)
			{
				const wchar_t* charSprite = (wchar_t*)payLoadSprite->Data;
				std::wstring wsprite(charSprite);
				std::string spritePath(wsprite.begin(), wsprite.end());
				unsigned int size = spritePath.find("$.%.$");
				std::string path = spritePath.substr(0, size);
				int num = std::stoi(spritePath.substr(size + 5, spritePath.length()));
				sprite = std::make_shared<Sprite>(*(m_application->GetAssetPool()->GetSpriteSheet(path.c_str())->GetSprite(num)));
			}
            if(sprite != nullptr)
            {
                m_sprites.push_back(sprite);
            }
		}



        ImGui::End();
    }

    void GridPanel::OnUpdate(float dt)
    {
        if(m_activeGameObject == nullptr)
            return;

        if(!m_activeGameObject->HasComponent<Grid>())
            return;

        Grid& grid = m_activeGameObject->GetComponent<Grid>();
        glm::vec2 mousepos = m_application->GetInput()->GetWorldMousePosition();
        mousepos -= glm::vec2(m_activeGameObject->GetComponent<Transform>().pos);
        if(sgn(mousepos.x) == -1)
            mousepos.x += Zewada::sgn(mousepos.x);
        if(sgn(mousepos.y) == -1)
            mousepos.y += Zewada::sgn(mousepos.y);
        mousepos.x = (int)(mousepos.x / grid.size);
        mousepos.y = (int)(mousepos.y / grid.size);
        

        if(m_application->GetInput()->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT) && m_application->GetImGuiLayer()->GetEditorView()->IsHovering())
        {
            auto& children = m_activeGameObject->GetComponent<Transform>().children;            
            for(auto& child : children)
            {
                GameObject go(m_application->GetSceneManager()->GetActiveScene()->GetEntity(child), m_application->GetSceneManager()->GetActiveScene());
                if(go.GetComponent<GridObject>().gridPos == mousepos)
                {
                    if(m_go != nullptr)
                    {
                        if(go.GetEntity() != m_go->GetEntity())
                            go.Destroy();
                    }
                    else
                        go.Destroy();
                }
            }
        }

        if(m_go == nullptr)
            return;

        GridObject& gridO = m_go->GetComponent<GridObject>();
        gridO.gridPos = glm::vec2(mousepos.x, mousepos.y);
 
        if(m_application->GetInput()->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && m_application->GetImGuiLayer()->GetEditorView()->IsHovering())
        {
            auto& children = m_activeGameObject->GetComponent<Transform>().children;
            bool found = false;        
            for(auto& child : children)
            {
                GameObject go(m_application->GetSceneManager()->GetActiveScene()->GetEntity(child), m_application->GetSceneManager()->GetActiveScene());
                if(go.GetComponent<GridObject>().gridPos == mousepos)
                {
                    if(m_go != nullptr)
                        if(go.GetEntity() != m_go->GetEntity())
                            found = true;
                }
            }

            if(!found)
                m_go->Copy();
        }

        if(m_application->GetInput()->IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            if(m_go != nullptr)
            {
                m_go->Destroy();
                m_go = nullptr;
            }
        }
    }
}