#include <zpch.h>
#include "SceneHierarchyPanel.h"
#include "../NazoApplication.h"

namespace Nazo {

    SceneHierarchyPanel::SceneHierarchyPanel(NazoApplication* application)
    {
        m_application = application;
    }

    void SceneHierarchyPanel::ImGui() 
    {
        ImGui::Begin("Scene Hierarchy");
        std::string path = m_application->GetSceneManager()->GetActiveScene()->GetPath();
        std::filesystem::path fsPath(path);
        ImGui::Text(fsPath.filename().string().c_str());
        auto coordinator = m_application->GetSceneManager()->GetActiveScene()->GetCoordinator();
        const std::vector<Entity>& entities = coordinator->GetAllEntities();
        std::shared_ptr<Scene> scene = m_application->GetSceneManager()->GetActiveScene();
        if(ImGui::BeginPopupContextWindow("GameObjectAdder"))
        {
            if(ImGui::MenuItem("Add GameObject"))
            {
                m_application->GetSceneManager()->GetActiveScene()->CreateEntity("new GameObject");
            }

		    ImGui::EndPopup();
        }
        ImRect();

        for(auto& entity : entities)
        {
            GameObject go = GameObject(entity, scene);
            if(go.GetComponent<Transform>().parent != -1)
            {
                continue;
            }
            bool treeNodeOpen = DoTreeNode(go);
            if(treeNodeOpen)
            {
                ImGui::TreePop();
            }
        }
        
        if(ImGui::BeginDragDropTarget())
        {
            const ImGuiPayload* payLoadObj = ImGui::AcceptDragDropPayload(payLoadDragDropType);
            if(payLoadObj != nullptr)
            {
                GameObject* payLoadGo = (GameObject*)payLoadObj->Data;
                if(payLoadGo->operator bool())
                {
                    Transform& transform = payLoadGo->GetComponent<Transform>();
                    if(transform.parent != -1)
                    {
                        GameObject parent = GameObject(scene->GetEntity(transform.parent), scene);
                        std::vector<ID>& children = parent.GetComponent<Transform>().children;
                        children.erase(remove(children.begin(), children.end(), payLoadGo->GetComponent<Tag>().id), children.end());
                        transform.pos += parent.GetComponent<Transform>().worldPos;
                    }
                }
            }
            ImGui::EndDragDropTarget();
        }
        static int index = 0; 
        if(SceneHierarchySpaces(&index))
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(payLoadDragDropType))
            {
                GameObject* go = (GameObject*)payload->Data;
                Transform& transform = go->GetComponent<Transform>();
                if(index == -1)
                {
                    if(transform.parent != -1)
                    {
                        GameObject parent = GameObject(scene->GetEntity(transform.parent), scene);
                        transform.parent = -1;
                        std::vector<ID>& children = parent.GetComponent<Transform>().children;
                        children.erase(remove(children.begin(), children.end(), go->GetComponent<Tag>().id), children.end());
                        transform.pos += parent.GetComponent<Transform>().worldPos;
                    }
                }
                else if(m_rects[index].index != -1 && m_rects[index].index != go->GetComponent<Tag>().id)
                {
                    
                    bool recursive = false;
                    GameObject parentOfParent = GameObject(scene->GetEntity(m_rects[index].index), scene);
                    while(parentOfParent.GetID() != -1)
                    {
                        if(parentOfParent.GetID() == go->GetID())
                        {
                            recursive = true;
                        }
                        parentOfParent = GameObject(scene->GetEntity(parentOfParent.GetComponent<Transform>().parent), scene);
                    }
                    if(!recursive)
                    {
                        if(transform.parent != -1)
                        {
                            GameObject parent = GameObject(scene->GetEntity(transform.parent), scene);
                            transform.parent = -1;
                            std::vector<ID>& children = parent.GetComponent<Transform>().children;
                            children.erase(remove(children.begin(), children.end(), go->GetComponent<Tag>().id), children.end());
                            transform.pos += parent.GetComponent<Transform>().worldPos;
                        }
                        if(index != -1)
                        {
                            transform.parent = m_rects[index].index;
                            GameObject temp = GameObject(scene->GetEntity(m_rects[index].index), scene);
                            ID parentid = temp.GetComponent<Transform>().parent;
                            transform.parent = parentid;
                            transform.pos -= temp.GetComponent<Transform>().worldPos;
                            
                            if(parentid != -1)
                            {
                                GameObject newParent = GameObject(scene->GetEntity(parentid), scene);
                                std::vector<ID>& children = newParent.GetComponent<Transform>().children;
                                int j = -1;
                                for(int i = 0; i < children.size(); i++)
                                {
                                    if(children[i] == m_rects[index].index)
                                    {
                                        j = i + 1;
                                        break;
                                    }
                                }
                                if(j != -1)
                                {
                                    children.push_back(-1);
                                    for(int i = children.size() - 1; i > j; i--)
                                    {
                                        children[i] = children[i - 1];
                                    }
                                    children[j] = go->GetComponent<Tag>().id;
                                }
                                else
                                {
                                    children.push_back(go->GetComponent<Tag>().id);
                                }
                            }
                        }
                    }
                }
            }
        }

        ImGui::End();
        m_rects.clear();
    }

    bool SceneHierarchyPanel::DoTreeNode(const GameObject& go)
    {
        std::shared_ptr<Scene> scene = m_application->GetSceneManager()->GetActiveScene();
        ImGui::PushID(go.GetID());
        bool treeNodeOpen = ImGui::TreeNodeEx(
                go.GetComponent<Tag>().name.c_str(), 
                ImGuiTreeNodeFlags_DefaultOpen |
                ImGuiTreeNodeFlags_FramePadding |
                ImGuiTreeNodeFlags_OpenOnArrow |
                ImGuiTreeNodeFlags_SpanAvailWidth,
                go.GetComponent<Tag>().name.c_str()
            );
        ImGui::PopID();

        if(ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload(payLoadDragDropType, &go, sizeof(go));
            ImGui::Text(go.GetComponent<Tag>().name.c_str());
            ImGui::EndDragDropSource();
        }

        if(ImGui::BeginDragDropTarget())
        {
            const ImGuiPayload* payLoadObj = ImGui::AcceptDragDropPayload(payLoadDragDropType);
            if(payLoadObj != nullptr)
            {
                GameObject* payLoadGo = (GameObject*)payLoadObj->Data;
                if(payLoadGo->operator bool())
                {
                    Transform& transform = payLoadGo->GetComponent<Transform>();
                    Tag& tag = payLoadGo->GetComponent<Tag>();
                    Entity parentID = scene->GetEntity(go.GetComponent<Transform>().parent);
                    bool recursive = false;
                    GameObject parentOfParent = GameObject(parentID, scene);
                    while(parentOfParent.GetID() != -1)
                    {
                        if(parentOfParent.GetID() == payLoadGo->GetID())
                        {
                            recursive = true;
                        }
                        parentOfParent = GameObject(scene->GetEntity(parentOfParent.GetComponent<Transform>().parent), scene);
                    }
                    if(!recursive)
                    {
                        if(transform.parent != -1)
                        {
                            GameObject parent = GameObject(scene->GetEntity(transform.parent),scene);
                            std::vector<ID>& children = parent.GetComponent<Transform>().children;
                            children.erase(remove(children.begin(), children.end(), payLoadGo->GetComponent<Tag>().id), children.end());
                            transform.pos += parent.GetComponent<Transform>().worldPos;
                        }
                        transform.parent = go.GetComponent<Tag>().id;
                        std::vector<ID>& children = go.GetComponent<Transform>().children;
                        children.push_back(-1);
                        for(int i = children.size() - 1; i > 0; i--)
                        {
                            children[i] = children[i - 1];
                        }
                        children[0] = payLoadGo->GetComponent<Tag>().id;
                        payLoadGo->GetComponent<Transform>().pos -= go.GetComponent<Transform>().worldPos;
                    }
                }
            }
            ImGui::EndDragDropTarget();
        }

        if(ImGui::IsItemClicked())
        {
            m_application->GetEditorLayer()->SetGameObject(go.GetID());
        }

        ImVec2 cursorPos = ImGui::GetCursorPos();
		ImVec2 elementSize = ImGui::GetItemRectSize();
		elementSize.x -= ImGui::GetStyle().FramePadding.x;
		elementSize.y = ImGui::GetStyle().FramePadding.y;
		ImVec2 windowPos = ImGui::GetCurrentWindow()->Pos;
        cursorPos.y -= ImGui::GetStyle().FramePadding.y;
        InBetweenRect rect;
        rect.index = go.GetComponent<Tag>().id;
        rect.rect = ImRect(windowPos.x + cursorPos.x, windowPos.y + cursorPos.y, windowPos.x + elementSize.x + cursorPos.x, windowPos.y + elementSize.y + cursorPos.y);
        m_rects.push_back(rect);

        if (ImGui::BeginPopupContextItem())
		{
            if(ImGui::MenuItem("Add GameObject"))
            {
                Entity entity = m_application->GetSceneManager()->GetActiveScene()->CreateEntity("new GameObject");
                GameObject newGo = GameObject(entity, scene);
                newGo.GetComponent<Transform>().parent = go.GetComponent<Tag>().id;
                std::vector<ID>& children = go.GetComponent<Transform>().children;
                children.push_back(-1);
                for(int i = children.size() - 1; i > 0; i--)
                {
                    children[i] = children[i - 1];
                }
                children[0] = newGo.GetComponent<Tag>().id;
            }
			if (ImGui::MenuItem("Delete Entity"))
            {
                if(m_application->GetEditorLayer()->GetActiveGameObject().get() != nullptr)
                {
                    if(m_application->GetEditorLayer()->GetActiveGameObject()->GetID() == go.GetID())
                        m_application->GetEditorLayer()->SetGameObject(-1);
                }

                m_application->GetSceneManager()->GetActiveScene()->DestroyEntity(go.GetID());
            }
            if (ImGui::MenuItem("Duplicate Entity", "CTR + D"))
            {
               go.Copy();
            }

			ImGui::EndPopup();
            return treeNodeOpen;
		}

        if(treeNodeOpen)
        {
            const std::vector<Entity>& children = go.GetComponent<Transform>().children;
            for(auto& child : children)
            {
                GameObject go = GameObject(scene->GetEntity(child), scene);
                bool childTreeNodeOpen = DoTreeNode(go);
                if(childTreeNodeOpen)
                {
                    ImGui::TreePop();
                }
            }
        }

        return treeNodeOpen;
    }

    bool SceneHierarchyPanel::SceneHierarchySpaces(int* index)
    {
        ImGuiContext& g = *GImGui;
		if (!g.DragDropActive)
        	return false;

		ImGuiWindow* window = g.CurrentWindow;
		if (window == NULL)
        	return false;

		ImRect windowRect = window->Rect();
		if (!ImGui::IsMouseHoveringRect(windowRect.Min, windowRect.Max))
			return false;
		if (window->SkipItems)
            return false;

        bool hoveringBetween = false;
		for (int i = 0; i < m_rects.size(); i++)
		{	
			if (ImGui::IsMouseHoveringRect(m_rects[i].rect.Min, m_rects[i].rect.Max))
			{
				*index = i;
				hoveringBetween = true;
				break;
			}
		}
        
		ImVec2 mousePos = ImGui::GetMousePos();
        if(m_rects.size() > 0)
        {
            if (mousePos.y > m_rects.back().rect.Max.y)
		    {
			    hoveringBetween = true;
			    *index = -1;
		    }
        }

		if (!hoveringBetween)
		{
			return false;
		}

		g.DragDropTargetRect = windowRect;
		g.DragDropTargetId = window->ID;
		g.DragDropWithinTarget = true;
		return true;
    }
}