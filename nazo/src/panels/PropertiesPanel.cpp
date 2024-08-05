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
			if(!m_activeGameObject->HasComponent<Camera>() && !m_activeGameObject->HasComponent<SpriteRenderer>())
			{
				if(ImGui::MenuItem("Add Camera"))
				{
					m_activeGameObject->AddComponent<Camera>(Camera());
				}
			}			
			if(!m_activeGameObject->HasComponent<SpriteRenderer>() && !m_activeGameObject->HasComponent<Camera>())
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

			if(!m_activeGameObject->HasCollider())
			{
				if(ImGui::MenuItem("Add Box2DCollider"))
				{
					m_activeGameObject->AddComponent<Box2DCollider>(Box2DCollider());
				}
				else if(ImGui::MenuItem("Add Circle2DCollider"))
				{
					m_activeGameObject->AddComponent<Circle2DCollider>(Circle2DCollider());
				}
				else if(ImGui::MenuItem("Add Edge2DCollider"))
				{
					m_activeGameObject->AddComponent<Edge2DCollider>(Edge2DCollider());
				}
				else if(ImGui::MenuItem("Add Polygon2DCollider"))
				{
					m_activeGameObject->AddComponent<Polygon2DCollider>(Polygon2DCollider());
				}

			}

			if(!m_activeGameObject->HasComponent<NativeScript>())
			{
				if(ImGui::MenuItem("Add NativeScript"))
				{
					m_activeGameObject->AddComponent<NativeScript>(NativeScript());
				}
			}

			if(!m_activeGameObject->HasComponent<Animation>() && !m_activeGameObject->HasComponent<AnimationManager>())
			{
				if(ImGui::MenuItem("Add Animation"))
				{
					m_activeGameObject->AddComponent<Animation>(Animation());
				}

				if(ImGui::MenuItem("Add AnimationManager"))
				{
					m_activeGameObject->AddComponent<AnimationManager>(AnimationManager());
				}
			}

			if(!m_activeGameObject->HasComponent<Grid>())
			{
				if(ImGui::MenuItem("Add Grid"))
				{
					m_activeGameObject->AddComponent<Grid>(Grid());
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
			ZImGui::DrawVec3Control("Position", transform.pos);
			ZImGui::DrawVec2Control("Scale", transform.scale);
			ZImGui::DragFloat("Rotation", transform.rotation);
		}
		
		if(m_activeGameObject->HasComponent<Camera>())
		{
			int temp = ZImGui::ComponentHeader("Camera");
			auto cameraSystem = m_application->GetSceneManager()->GetActiveScene()->GetCameraSystem();
			if(temp == 1)
			{
				Camera& camera = m_activeGameObject->GetComponent<Camera>();
				//maincamera
				bool maincamera = (cameraSystem->GetMaincameraObject() == m_activeGameObject->GetEntity());
				if(!maincamera && camera.maincamera)
				{
					camera.maincamera = false;
				}
				ImGui::Checkbox("Maincamera", &maincamera);
				if(maincamera && !camera.maincamera)
					cameraSystem->SetMaincamera(m_activeGameObject->GetEntity());
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
				ZImGui::ColorPicker4("Color", spriteRenderer.color);
				ZImGui::TextureInput("Texture", spriteRenderer.sprite);
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

				ZImGui::DragFloat("Angular damping", rigidbody2D.angularDamping);
				ZImGui::DragFloat("Linear damping", rigidbody2D.linearDamping);
				ZImGui::DragFloat("Restitution", rigidbody2D.restitution);
				ZImGui::DragFloat("Density", rigidbody2D.density);
				ZImGui::DragFloat("Friction", rigidbody2D.friction);
				
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
				ZImGui::DrawVec2Control("Gravity", gravity);
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
				ZImGui::DrawVec2Control("Halfsize", box2DCollider.halfSize);
				ZImGui::DrawVec2Control("Offset", box2DCollider.offset);
			}
			else if(temp == 2)
			{
				m_activeGameObject->RemoveComponent<Box2DCollider>();
			}
		}

		if(m_activeGameObject->HasComponent<Circle2DCollider>())
		{
			int temp = ZImGui::ComponentHeader("Circle2DCollider");
			if(temp == 1)
			{
				Circle2DCollider& circle2DCollider = m_activeGameObject->GetComponent<Circle2DCollider>();
				ZImGui::DragFloat("Radius", circle2DCollider.radius);
				ZImGui::DrawVec2Control("Offset", circle2DCollider.offset);
			}
			else if(temp == 2)
			{
				m_activeGameObject->RemoveComponent<Circle2DCollider>();
			}
		}
		
		if(m_activeGameObject->HasComponent<Polygon2DCollider>())
		{
			int temp = ZImGui::ComponentHeader("Polygon2DCollider");
			if(temp == 1)
			{
				Polygon2DCollider& polygon2DCollider = m_activeGameObject->GetComponent<Polygon2DCollider>();
				ZImGui::Vector<glm::vec2>("Vertices", "Vertex", polygon2DCollider.vertices, ZImGui::DrawVec2Control);
				ZImGui::DrawVec2Control("Offset", polygon2DCollider.offset);
			}
			else if(temp == 2)
			{
				m_activeGameObject->RemoveComponent<Polygon2DCollider>();
			}
		}

		if(m_activeGameObject->HasComponent<Edge2DCollider>())
		{
			int temp = ZImGui::ComponentHeader("Edge2DCollider");
			if(temp == 1)
			{
				Edge2DCollider& edge2DCollider = m_activeGameObject->GetComponent<Edge2DCollider>();
				ZImGui::Vector<glm::vec2>("Vertices", "Vertex", edge2DCollider.vertices, ZImGui::DrawVec2Control);
				ZImGui::DrawVec2Control("Previous Ghost", edge2DCollider.previousGhostVertex);
				ZImGui::DrawVec2Control("Next Ghost", edge2DCollider.nextGhostVertex);
				ZImGui::DrawVec2Control("Offset", edge2DCollider.offset);

			}
			else if(temp == 2)
			{
				m_activeGameObject->RemoveComponent<Edge2DCollider>();
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

		if(m_activeGameObject->HasComponent<Animation>() && !m_activeGameObject->HasComponent<AnimationManager>())
		{
			int temp = ZImGui::ComponentHeader("Animation");
			if(temp == 1)
			{
				auto& ac = m_activeGameObject->GetComponent<Animation>();

				ZImGui::Animation("Frames", ac);
			}
			else if(temp == 2)
			{
				m_activeGameObject->RemoveComponent<Animation>();
			}
		}

		if(m_activeGameObject->HasComponent<AnimationManager>())
		{
			int temp = ZImGui::ComponentHeader("AnimationManager");
			if(temp == 1)
			{
				auto& ac = m_activeGameObject->GetComponent<AnimationManager>();

				ZImGui::Unordered_map<std::string, Animation>("Animations", "Name", "Animation", ac.animations, ZImGui::TextInput, ZImGui::Animation);
			}
			else if(temp == 2)
			{
				m_activeGameObject->RemoveComponent<AnimationManager>();
			}
		}
		
		if(m_activeGameObject->HasComponent<Grid>())
		{
			int temp = ZImGui::ComponentHeader("Grid");
			if(temp == 1)
			{
				auto& grid = m_activeGameObject->GetComponent<Grid>();

				ZImGui::DragFloat("Size", grid.size);
			}
			else if(temp == 2)
			{
				m_activeGameObject->RemoveComponent<Grid>();
			}
		}
		
		ImGui::End();
	}

	void PropertiesPanel::SetTexture(std::shared_ptr<Texture> tex)
	{
		m_activeTexture = tex;
	}
}