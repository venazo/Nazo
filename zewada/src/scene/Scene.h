#pragma once

#include "../Graphics/OpenGL/Renderer/RenderBatch.h"
#include "../Utils/Debug/Logger.h"
#include "../Utils/Input.h"
#include "../ECS/Systems/SpriteRendererSystem.h"
#include "../Utils/Resource/AssetPool.h"
#include "../ECS/systems/CameraSystem.h"
#include "../ECS/systems/TransformSystem.h"
#include "../ECS/systems/Rigidbody2DSystem.h"
#include "../ECS/systems/NativeScriptSystem.h"

#include "../application.h"

namespace Zewada {

	class GameObject;

	class Scene : public std::enable_shared_from_this<Scene>
	{
	private:
		std::string m_path = "Undefined";
		std::vector<ID> m_ids;
		std::unordered_map<ID, Entity> m_ID2Entity;

		Application* m_application;

		std::shared_ptr<Physics2D> m_physics2D;
	public:
		std::shared_ptr<Coordinator> m_coordinator;
		std::shared_ptr<TransformSystem> m_transformSystem;
		std::shared_ptr<SpriteRendererSystem> m_spriteRendererSystem;
		std::shared_ptr<CameraSystem> m_cameraSystem;
		std::shared_ptr<Rigidbody2DSystem> m_rigidBody2Dsystem;
		std::shared_ptr<NativeScriptSystem> m_nativeScriptSystem;

		Scene() = default;
		Scene(const std::string& path, Application* application);
		~Scene();
		void Init();

		void OnStart();
		void OnStop();
		void OnUpdate(float dt);
		void OnRuntimeUpdate(float dt);
		void OnRender();

		void OnResize(WindowResizeEvent& event);
		Entity CreateEntity(std::string name);
		Entity CreateEntity(std::string name, ID id);
		void Destroy();
		bool Exist(Entity entity) const;
		void DestroyEntity(Entity entity);

		Entity GetEntity(ID id);

		void SetPath(const std::string& path);

		inline std::shared_ptr<Coordinator> GetCoordinator(){return m_coordinator;}
		inline std::shared_ptr<TransformSystem> GetTransformSystem(){return m_transformSystem;}
		inline std::shared_ptr<SpriteRendererSystem> GetSpriteSystem(){return m_spriteRendererSystem;}
		inline std::shared_ptr<CameraSystem> GetCameraSystem(){return m_cameraSystem;}
		inline std::shared_ptr<Rigidbody2DSystem> GetRigidbody2DSystem(){return m_rigidBody2Dsystem;}
		inline const std::string& GetPath() const {return m_path;}
		inline std::shared_ptr<Physics2D> GetPhysics2D() const {return m_physics2D;} 
		inline Application* GetApplication() const {return m_application;} 
	};
}