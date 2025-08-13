#pragma once

#include "../Graphics/OpenGL/Renderer/RenderBatch.h"
#include "../Utils/Debug/Logger.h"
#include "../Utils/Input.h"
#include "../ECS/Systems/SpriteRendererSystem.h"
#include "../Utils/Resource/AssetPool.h"
#include "../ECS/systems/CameraSystem.h"
#include "../ECS/systems/TransformSystem.h"
#include "../ECS/systems/NativeScriptSystem.h"
#include "../ECS/systems/AnimationSystem.h"
#include "../ECS/systems/AnimationManagerSystem.h"
#include "../ECS/systems/GridObjectSystem.h"
#include "../ECS/systems/TextSystem.h"

#include "../application.h"

namespace Zewada {

	//to descerialize Scene
	struct ScenePlan
	{
		ScenePlan() = default;
		ScenePlan(glm::vec4 bgc, glm::vec2 g)
			:backgroundColor(bgc), gravity(g)
		{
			
		}
		glm::vec4 backgroundColor = glm::vec4(0.17f, 0.17f, 0.17f, 1.0f);
		glm::vec2 gravity = glm::vec2(0, -10.0f);
	};

	class GameObject;

	class Scene : public std::enable_shared_from_this<Scene>
	{
	private:
		std::string m_path = "Undefined";
		std::vector<int> m_ids;
		std::unordered_map<int, Entity> m_ID2Entity;
		
		ScenePlan m_scenePlan;

		Application* m_application;

		std::shared_ptr<Physics2D> m_physics2D;
	public:
		std::shared_ptr<Coordinator> m_coordinator;
		std::shared_ptr<TransformSystem> m_transformSystem;
		std::shared_ptr<SpriteRendererSystem> m_spriteRendererSystem;
		std::shared_ptr<CameraSystem> m_cameraSystem;
		std::shared_ptr<NativeScriptSystem> m_nativeScriptSystem;
		std::shared_ptr<AnimationSystem> m_animationSystem;
		std::shared_ptr<AnimationManagerSystem> m_animationManagerSystem;
		std::shared_ptr<GridObjectSystem> m_gridObjectSystem;
		std::shared_ptr<TextSystem> m_textSystem;

		Scene() = default;
		Scene(const std::string& path, ScenePlan scenePlan = ScenePlan());
		~Scene();
		void Init(Application* application);

		void OnStart();
		void OnStop();
		void OnUpdate(float dt);
		void OnRuntimeUpdate(float dt);
		void OnRender();

		void OnResize(WindowResizeEvent& event);
		Entity CreateEntity(std::string name);
		Entity CreateEntity(std::string name, int id);
		void Destroy();
		bool Exist(Entity entity) const;
		void DestroyEntity(Entity entity);

		Entity GetEntity(int id);

		void SetPath(const std::string& path);

		void Save();

		inline std::shared_ptr<Coordinator> GetCoordinator() const {return m_coordinator;}
		inline std::shared_ptr<TransformSystem> GetTransformSystem(){return m_transformSystem;}
		inline std::shared_ptr<SpriteRendererSystem> GetSpriteSystem(){return m_spriteRendererSystem;}
		inline std::shared_ptr<CameraSystem> GetCameraSystem(){return m_cameraSystem;}
		
		inline const std::string& GetPath() const {return m_path;}
		inline std::shared_ptr<Physics2D> GetPhysics2D() const {return m_physics2D;} 
		inline Application* GetApplication() const {return m_application;} 

		inline const glm::vec2 GetGravity(){return m_scenePlan.gravity;}
		inline const glm::vec4 GetBackgroundColor(){return m_scenePlan.backgroundColor;}
	};
}