#pragma once

#include <fstream>
#include <yaml-cpp/yaml.h>
#include "../../physics2d/Physics2D.h"
#include "../../graphics/openGL/renderer/Renderer2D.h"
#include "../../utils/resource/AssetPool.h"
#include "../../scene/SceneManager.h"

namespace Zewada {

	class GameObject;

	class Serializer
	{
	private:
		std::string m_file;
	public:
		Serializer();
		void SerializeEntity(YAML::Emitter& out, const GameObject& entity);

		void SerializeSpriteSheet(YAML::Emitter& out, std::shared_ptr<SpriteSheet> spriteSheet);
		void SerializeAssets(std::shared_ptr<AssetPool> assetPool);

		void DeserializeAssets(std::shared_ptr<AssetPool> assetPool);
		void Serialize(std::shared_ptr<Scene> scene);
		std::shared_ptr<Scene> Deserialize(const std::string& filepath, Application* application);
	};
}