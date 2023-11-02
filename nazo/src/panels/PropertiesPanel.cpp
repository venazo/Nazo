#include <zpch.h>
#include "PropertiesPanel.h"
#include "../NazoApplication.h"

namespace Nazo {
	PropertiesPanel::PropertiesPanel(NazoApplication* application)
	{
		m_application = application;
	}
	
	void PropertiesPanel::SpriteSheetEditor()
	{
		std::filesystem::path fpath = FileUtils::RelativePath(m_activeTexture->GetPath().c_str());
		auto ss = m_application->GetAssetPool()->GetSpriteSheet(fpath.string().c_str());
		float padding = ImGui::GetStyle().FramePadding.x;
		float cellSize = 128.0f + padding;
        float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
        if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);
		for(auto sprite : ss->GetSprites())
		{
			ImTextureID textureid = (ImTextureID)sprite->GetTexture()->GetID();
			auto UV = sprite->GetUV();
			ImGui::Image(textureid, ImVec2(128.0f, 128.0f), ImVec2(UV[1].x, UV[1].y), ImVec2(UV[3].x, UV[3].y));
			ImGui::NextColumn();
		}

		static int width = ss->GetSpriteWidth(); 
		static int height = ss->GetSpriteHeight();
		static int numSprites = ss->GetNumSprites();
		static int spacing = ss->GetSpacing();
		ZImGui::DragInt("Width", width);
		ZImGui::DragInt("Height", height);
		ZImGui::DragInt("Sprites count", numSprites);
		ZImGui::DragInt("Spacing", spacing);

		if(ImGui::Button("Refresh SpriteSheet"))
		{
			auto spriteSheet = std::make_shared<SpriteSheet>(m_activeTexture, width, height, numSprites, spacing);
			m_application->GetAssetPool()->ReplaceSpriteSheet(spriteSheet);
		}

		if(ImGui::Button("Delete SpriteSheet"))
		{
			m_application->GetAssetPool()->DeleteSpriteSheet(fpath.string().c_str());
		}

		if(ImGui::Button("OK"))
		{
			m_activeTexture = nullptr;
		}
	}

	void PropertiesPanel::SpriteEditor()
	{
		std::string path = m_activeTexture->GetPath();
		ImGui::Text("Path: "); 
		ImGui::SameLine();
		ImGui::Text(path.c_str());

		std::filesystem::path fpath = FileUtils::RelativePath(m_activeTexture->GetPath().c_str());

		if(!m_application->GetAssetPool()->ExistSpriteSheet(fpath.string().c_str()))
		{
			ImTextureID textureid = (ImTextureID)m_activeTexture->GetID();
			ImGui::Image(textureid, ImVec2(256.0f, 256.0f), ImVec2(0, 1), ImVec2(1, 0));
			if(ImGui::Button("Create SpriteSheet"))
			{
				std::shared_ptr<SpriteSheet> ss = std::make_shared<SpriteSheet>(m_activeTexture, 
					m_activeTexture->GetWidth(), m_activeTexture->GetHeight(), 1.0f, 0.0f);
				m_application->GetAssetPool()->AddSpriteSheet(ss);
			}

			if(ImGui::Button("OK"))
			{
				m_activeTexture = nullptr;
			}
		}
		else
			SpriteSheetEditor();
	}

	void PropertiesPanel::ImGui()
	{
		ImGui::Begin("Inspector");

		if(m_activeTexture != nullptr)
		{
			SpriteEditor();
			ImGui::End();
			return;
		}

		m_activeGameObject = m_application->GetEditorLayer()->GetActiveGameObject();
		
		if(m_activeGameObject == nullptr)
		{
			ImGui::End();
			return;
		}

		if(!m_activeGameObject->operator bool())
		{
			ImGui::End();
			return;
		}

		if(ImGui::BeginPopupContextWindow("ComponentAdder"))
		{
			if(!m_activeGameObject->HasComponent<Camera>())
			{
				if(ImGui::MenuItem("Add Camera"))
				{
					m_activeGameObject->AddComponent<Camera>(Camera());
				}
			}			
			if(!m_activeGameObject->HasComponent<SpriteRenderer>())
			{
				if(ImGui::MenuItem("Add SpriteRenderer"))
				{
					m_activeGameObject->AddComponent<SpriteRenderer>(SpriteRenderer());
				}
			}

			if(!m_activeGameObject->HasComponent<Rigidbody2D>())
			{
				if(ImGui::MenuItem("Add Rigidbody2D"))
				{
					m_activeGameObject->AddComponent<Rigidbody2D>(Rigidbody2D());
				}
			}

			if(!m_activeGameObject->HasComponent<Box2DCollider>())
			{
				if(ImGui::MenuItem("Add Box2DCollider"))
				{
					m_activeGameObject->AddComponent<Box2DCollider>(Box2DCollider());
				}
			}

			if(!m_activeGameObject->HasComponent<NativeScript>())
			{
				if(ImGui::MenuItem("Add NativeScript"))
				{
					m_activeGameObject->AddComponent<NativeScript>(NativeScript());
				}
			}

			ImGui::EndPopup();
		}
		
		if(ImGui::CollapsingHeader("Tag"))
		{
			Tag& tag = m_activeGameObject->GetComponent<Tag>();
			ZImGui::TextInput("Tag", tag.name);
		}
		if(ImGui::CollapsingHeader("Transform"))
		{
			Transform& transform = m_activeGameObject->GetComponent<Transform>();
			ZImGui::DrawVec3Control("Position", transform.pos, 0.0f);
			ZImGui::DrawVec2Control("Scale", transform.scale, 100.0f);
			ZImGui::DragFloat("Rotation", transform.rotation, 0.0f);
		}
		
		if(m_activeGameObject->HasComponent<Camera>())
		{
			int temp = ZImGui::ComponentHeader("Camera");
			auto cameraSystem = m_application->GetSceneManager()->GetActiveScene()->GetCameraSystem();
			if(temp == 1)
			{
				Camera& camera = m_activeGameObject->GetComponent<Camera>();
				//maincamera
				bool maincamera = (cameraSystem->GetMaincameraObject() == m_activeGameObject->GetID());
				if(!maincamera && camera.maincamera)
				{
					camera.maincamera = false;
				}
				ImGui::Checkbox("Maincamera", &maincamera);
				if(maincamera && !camera.maincamera)
					cameraSystem->SetMaincamera(m_activeGameObject->GetID());
				if(!maincamera && camera.maincamera)
				{
					cameraSystem->SetMaincamera(-1);
					camera.maincamera = false;
				}
				
				static glm::vec4 backgroundColor;
				backgroundColor = m_application->GetRenderer2D()->GetBackgroundColor();
				ZImGui::ColorPicker4("BackgroundColor", backgroundColor);
				m_application->GetRenderer2D()->SetBackgroundColor(backgroundColor);
			}
			else if(temp == 2)
			{
				Camera& camera = m_activeGameObject->GetComponent<Camera>();
				if(camera.maincamera)
				{
					camera.maincamera = false;
					cameraSystem->SetMaincamera(-1);
				}
				m_activeGameObject->RemoveComponent<Camera>();
			}
		}
		if(m_activeGameObject->HasComponent<SpriteRenderer>())
		{
			int temp = ZImGui::ComponentHeader("SpriteRenderer");
			if(temp == 1)
			{
				SpriteRenderer& spriteRenderer = m_activeGameObject->GetComponent<SpriteRenderer>();
				ZImGui::ColorPicker4("Color", spriteRenderer.color, 0.0f);
				const std::string path = spriteRenderer.sprite->GetTexture()->GetPath();
				std::filesystem::path realPath(path);
				std::string name = realPath.filename().string();
				ZImGui::TextureInput(name, spriteRenderer);
			}
			else if(temp == 2)
			{
				m_activeGameObject->RemoveComponent<SpriteRenderer>();
			}
		}

		if(m_activeGameObject->HasComponent<Rigidbody2D>())
		{
			int temp = ZImGui::ComponentHeader("Rigidbody2D");
			if(temp == 1)
			{
				Rigidbody2D& rigidbody2D = m_activeGameObject->GetComponent<Rigidbody2D>();

				ZImGui::DragFloat("Angular damping", rigidbody2D.angularDamping, 0.8f);
				ZImGui::DragFloat("Linear damping", rigidbody2D.linearDamping, 0.9f);
				ZImGui::DragFloat("Mass", rigidbody2D.mass, 1.0f);
				
				if (ImGui::BeginCombo("##BodyType", bodyType2Names[rigidbody2D.bodyType].c_str()))
				{
					if(ImGui::Selectable(bodyType2Names[BodyType::Static].c_str()))
					{
						rigidbody2D.bodyType = Static;
					}
					if(ImGui::Selectable(bodyType2Names[BodyType::Dynamic].c_str()))
					{
						rigidbody2D.bodyType = Dynamic;
					}
					if(ImGui::Selectable(bodyType2Names[BodyType::Kinematic].c_str()))
					{
						rigidbody2D.bodyType = Kinematic;
					}
					ImGui::EndCombo();
				}

				ImGui::Checkbox("Fixed rotation", &rigidbody2D.fixedRotation);
				ImGui::Checkbox("Continuous collision", &rigidbody2D.continuousCollision);

				glm::vec2 gravity = m_application->GetPhysics2D()->GetGravity();
				ZImGui::DrawVec2Control("Gravity", gravity, -10.0f);
				m_application->GetPhysics2D()->SetGravity(gravity.x, gravity.y);
			}
			else if(temp == 2)
			{
				m_activeGameObject->RemoveComponent<Rigidbody2D>();
			}
		}

		if(m_activeGameObject->HasComponent<Box2DCollider>())
		{
			int temp = ZImGui::ComponentHeader("Box2DCollider");
			if(temp == 1)
			{
				Box2DCollider& box2DCollider = m_activeGameObject->GetComponent<Box2DCollider>();
				ZImGui::DrawVec2Control("Halfsize", box2DCollider.halfSize, 0.0f);
				ZImGui::DrawVec2Control("Offset", box2DCollider.offset, 0.0f);
				ZImGui::DrawVec2Control("Origin", box2DCollider.origin, 0.0f);
			}
			else if(temp == 2)
			{
				m_activeGameObject->RemoveComponent<Box2DCollider>();
			}
		}

		if(m_activeGameObject->HasComponent<NativeScript>())
		{
			int temp = ZImGui::ComponentHeader("NativeScript");
			if(temp == 1)
			{
				auto& ns = m_activeGameObject->GetComponent<NativeScript>();

				ZImGui::ScriptInput(ns.className, ns);
			}
			else if(temp == 2)
			{
				m_activeGameObject->RemoveComponent<NativeScript>();
			}
		}
		
		ImGui::End();
	}

	void PropertiesPanel::SetTexture(std::shared_ptr<Texture> tex)
	{
		m_activeTexture = tex;
	}
}