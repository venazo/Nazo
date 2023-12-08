#include <zpch.h>
#include "EditorLayer.h"
#include "../NazoApplication.h"

namespace Nazo {

#define BIND_EVENT_FN(x) std::bind(&Nazo::EditorLayer::x, this, std::placeholders::_1)

	EditorLayer::EditorLayer(NazoApplication* application)
	:Layer("EditorLayer")
	{
		m_activeGameObject = nullptr;
		m_application = application;
		m_ctr = false;
		m_shift =false;
		m_loading = false;
		m_scenePlaying =false;
	}

	void EditorLayer::OnAttach()
	{
		ZImGui::SetAssetPool(m_application->GetAssetPool());
		m_cameraController = std::make_unique<CameraController>(m_application);
		m_gizmoSystem = std::make_unique<GizmoSystem>(m_application, m_cameraController->GetCamera());
		m_defaultShader = m_application->GetAssetPool()->GetShader("assets/shaders/Default_Editor.glsl");
	}

	void EditorLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnResize));
		dispatcher.Dispatch<GameStartEvent>(BIND_EVENT_FN(OnGameStart));
		dispatcher.Dispatch<GameEndEvent>(BIND_EVENT_FN(OnGameEnd));
		dispatcher.Dispatch<ChangedSceneEvent>(BIND_EVENT_FN(OnChangedScene));
		dispatcher.Dispatch<LoadSceneEvent>(BIND_EVENT_FN(OnLoadScene));
		dispatcher.Dispatch<SaveSceneEvent>(BIND_EVENT_FN(OnSaveScene));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(OnKeyReleased));

		if(m_application->GetImGuiLayer()->GetEditorView()->IsHovering())
		{
			dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseButtonPressed));
			m_cameraController->OnEvent(event);
		}
	}

	//all shortcuts
	bool EditorLayer::OnKeyPressed(KeyPressedEvent& event)
	{
		if(event.IsRepeat())
			return false;
		
		if(event.GetKeyCode() == GLFW_KEY_LEFT_CONTROL || event.GetKeyCode() == GLFW_KEY_RIGHT_CONTROL)
		{
			unsigned int key = event.GetKeyCode();
			m_ctr = true;
			return false;	
		}

		if(event.GetKeyCode() == GLFW_KEY_LEFT_SHIFT || event.GetKeyCode() == GLFW_KEY_RIGHT_SHIFT)
		{
			m_shift = true;
			return false;	
		}

		if(event.GetKeyCode() == GLFW_KEY_E)
		{
			m_gizmoSystem->SetActiveGizmo(0);
			return true;
		}

		if(event.GetKeyCode() == GLFW_KEY_R)
		{
			m_gizmoSystem->SetActiveGizmo(1);
			return true;
		}
		
		if(event.GetKeyCode() == GLFW_KEY_F5)
		{
			if(!m_scenePlaying)
			{
				GameStartEvent event;
                m_callback(event);
				return true;
			}
		}

		if(event.GetKeyCode() == GLFW_KEY_F4)
		{
			if(m_scenePlaying)
			{
				GameEndEvent event;
                m_callback(event);
				return true;
			}
		}

		if(event.GetKeyCode() == GLFW_KEY_S && m_ctr)
		{
			if(!m_scenePlaying)
			{
				SaveSceneEvent event;
                m_callback(event);
				return true;
			}
		}

		//TO DO
		if(event.GetKeyCode() == GLFW_KEY_S && m_ctr && m_shift)
		{
			if(!m_scenePlaying)
			{
				return true;
			}
		}

		//TO DO
		if(event.GetKeyCode() == GLFW_KEY_O && m_ctr)
		{
			if(!m_scenePlaying)
			{
				return true;
			}
		}

		//common used like delete ctr + c, ctr + v, ctr + d, ctr + x
		if(event.GetKeyCode() == GLFW_KEY_D && m_ctr)
		{
			if(m_activeGameObject != nullptr)
			{
				m_activeGameObject->Copy();
			}
			return true;
		}

		if(event.GetKeyCode() == GLFW_KEY_DELETE)
		{
			if (m_activeGameObject != nullptr)
			{
				if(m_activeGameObject->operator bool())
					m_activeGameObject->Destroy();
			}
			return true;
		}
		return false;
	}

    bool EditorLayer::OnKeyReleased(KeyReleasedEvent& event)
    {
		if(event.GetKeyCode() == GLFW_KEY_LEFT_CONTROL || event.GetKeyCode() == GLFW_KEY_RIGHT_CONTROL)
		{
			m_ctr = false;
			return false;	
		}

		if(event.GetKeyCode() == GLFW_KEY_LEFT_SHIFT || event.GetKeyCode() == GLFW_KEY_RIGHT_SHIFT)
		{
			m_shift = false;
			return false;	
		}

        return false;
    }

    bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent &event)
    {
		
        return false;
    }

    bool EditorLayer::OnResize(WindowResizeEvent& event)
	{
		//because of gameviewportview
		glm::vec2 size = glm::vec2(m_application->GetImGuiLayer()->GetEditorView()->GetWindowWidth(), m_application->GetImGuiLayer()->GetEditorView()->GetWindowHeight());
		m_cameraController->OnResize(size.x, size.y);
		if(m_application->GetSceneManager()->HasActiveScene())
			m_application->GetSceneManager()->GetActiveScene()->OnResize(event);
		return false;
	}

	void EditorLayer::OnUpdate(float dt)
	{
		//startframe
		m_application->GetRenderer2D()->Clear();
		m_application->GetRenderer2D()->BindShader(m_defaultShader);

		//startFrame Game
		m_application->GetImGuiLayer()->GetGameView()->Bind();
		if(m_application->GetSceneManager()->HasActiveScene())
		{
			GameObject maincamera = GameObject(m_application->GetSceneManager()->GetActiveScene()->GetCameraSystem()->GetMaincameraObject(), m_application->GetSceneManager()->GetActiveScene());
			if(maincamera.operator bool())
			{
				m_application->GetInput()->CalcWorldMousePosition(maincamera.GetComponent<Transform>(), 
					maincamera.GetComponent<Camera>());
			}
			else
			{
				m_application->GetInput()->CalcWorldMousePosition(Transform(), Camera());
			}
		}


		//Update Game
		if(!m_scenePlaying)
		{
			m_application->GetSceneManager()->OnUpdate(dt);
		}
		else
		{
			m_application->GetSceneManager()->OnRuntimeUpdate(dt);
		}

		//Render Game
		m_application->GetSceneManager()->OnRender();

		//endFrame Game
		m_application->GetImGuiLayer()->GetGameView()->UnBind();
		
		//startFrame Editor
		m_application->GetImGuiLayer()->GetEditorView()->Bind();
		m_application->GetInput()->CalcWorldMousePosition(m_cameraController->GetTransform(), 
			m_cameraController->GetCamera());

		//update Editor
		m_cameraController->OnUpdate(dt);
		m_gizmoSystem->OnUpdate(dt);			

		//render Editor
		m_application->GetRenderer2D()->Render(m_cameraController->GetCamera());
		EditorDrawing();
		m_application->GetDebugDraw()->Draw(m_cameraController->GetCamera());

		CheckActiveGameObject();

		//Endframe Editor
		m_application->GetDebugDraw()->EndFrame(dt);
		m_application->GetImGuiLayer()->GetEditorView()->UnBind();

		if (m_passed > 1.0f)
		{
			Z_INFO() << m_frames;
			//PrintMemory();
			m_passed = 0.0f;
			m_frames = 0;
		}
		else
		{
			m_passed += dt;
			m_frames++;
		}
	}

	bool EditorLayer::CheckActiveGameObject()
	{
		if (m_application->GetInput()->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && !m_application->GetInput()->IsDraging() && m_application->GetImGuiLayer()->GetEditorView()->IsHovering() && m_application->GetSceneManager()->HasActiveScene())
		{
			//just bind because we want no clear and no translation
			glm::vec2 pos = m_application->GetInput()->GetMousePosition();
			int id = m_application->GetImGuiLayer()->GetEditorView()->GetFramebuffer()->ReadPixel(1, pos.x, pos.y);
			if(id <= MAX_ENTITIES)
				id = m_application->GetSceneManager()->GetActiveScene()->GetEntity(id);
			bool result = SetGameObject(id);
			return result;
		}
		return true;
	}

	bool EditorLayer::SetGameObject(Entity id)
	{
		if (id > MAX_ENTITIES)
		{
			return false;
		}
			
		if (id != -1)
		{
			m_activeGameObject = std::make_shared<GameObject>(id, m_application->GetSceneManager()->GetActiveScene());
			m_activeID = m_activeGameObject->GetComponent<Tag>().id;
		}
		else
		{
			m_activeGameObject = nullptr;
			m_activeID = -1;
		}	

		m_gizmoSystem->SetActiveGameObject(m_activeGameObject);
		return true;
	}

	void EditorLayer::EditorDrawing()
	{
		if(m_application->GetSceneManager()->HasActiveScene())
		{
			for(auto cam : m_application->GetSceneManager()->GetActiveScene()->GetCameraSystem()->GetEntities())
			{
				m_application->GetDebugDraw()->AddCamera(m_application->GetSceneManager()->GetActiveScene()->GetCoordinator()->GetComponent<Transform>(cam));
			}
		}
		

		if(m_activeGameObject == nullptr)
			return;

		if(m_activeGameObject->HasComponent<Box2DCollider>())
		{
			const Box2DCollider& boxCollider = m_activeGameObject->GetComponent<Box2DCollider>();
			const Transform& transform = m_activeGameObject->GetComponent<Transform>();
			m_application->GetDebugDraw()->Add2DBox(boxCollider.offset + glm::vec2(transform.worldPos), boxCollider.halfSize, transform.rotation, glm::vec4(0.2f, 0.8f, 0.15f, 1.0f));
		}
	}

	bool EditorLayer::OnGameStart(GameStartEvent& event)
	{
		SaveSceneEvent SceneEvent;
		m_callback(SceneEvent);
		m_scenePlaying = true;
		m_application->GetSceneManager()->OnStart();
		return true;
	}

	bool EditorLayer::OnGameEnd(GameEndEvent& event)
	{
		m_activeGameObject = nullptr;
		m_activeID = -1;
		m_scenePlaying = false;
		m_application->GetSceneManager()->OnStop();
		LoadSceneEvent SceneEvent(m_application->GetSceneManager()->GetActiveScene()->GetPath());
		m_callback(SceneEvent);
		return true;
	}
	
	bool EditorLayer::OnLoadScene(LoadSceneEvent& event)
	{
		if(m_scenePlaying)
		{
			m_scenePlaying = false;
		}
		m_loading = true;
		m_application->GetSceneManager()->SetActiveScene(event.GetPath());
		return true;
	}

	bool EditorLayer::OnChangedScene(ChangedSceneEvent& event)
	{
		m_loading = false;

		return true;
	}

	bool EditorLayer::OnSaveScene(SaveSceneEvent& event)
	{
		if(!m_loading && !m_scenePlaying)
		{
			if(m_application->GetSceneManager()->GetActiveScene()->GetPath() == "")
			{
				std::string path = "assets/scenes/Default_Scene.zs";
				m_application->GetSceneManager()->GetActiveScene()->SetPath(path);
			}
			m_application->GetSceneManager()->SaveActiveScene();
		}
			
		return true;
	}

	void EditorLayer::SetEventCallback(const EventCallbackFn& callback)
	{
		m_callback = callback;
	}

}