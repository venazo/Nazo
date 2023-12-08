#pragma once

#include <fstream>
#include <yaml-cpp/yaml.h>
#include <mutex>
#include "../physics2d/Physics2D.h"
#include "../graphics/openGL/renderer/Renderer2D.h"
#include "../utils/resource/AssetPool.h"
#include "../scene/SceneManager.h"

namespace Zewada {

	class GameObject;

	class SceneSerializer
	{
	private:
		std::string m_file;

		void SerializeEntity(YAML::Emitter& out, const GameObject& entity);
		void SerializeSpriteSheet(YAML::Emitter& out, std::shared_ptr<SpriteSheet> spriteSheet);
	public:
		SceneSerializer();
		void SerializeAssets(std::shared_ptr<AssetPool> assetPool);
		void DeserializeAssets(std::shared_ptr<AssetPool> assetPool);
		void Serialize(std::shared_ptr<Scene> scene);
		std::shared_ptr<Scene> Deserialize(const std::string& filepath);
	};
}