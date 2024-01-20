#include <zpch.h>
#include "SceneSerializer.h"
#include <Scene/GameObject.h>

namespace YAML {

	using namespace Zewada;

	template <typename K, typename V>
	struct convert<std::unordered_map<K, V>> {
	  	static Node encode(const std::unordered_map<K, V>& rhs) {
    		Node node(NodeType::Map);
    		for (const auto& element : rhs)
      			node.force_insert(element.first, element.second);
    		return node;
  		}

  		static bool decode(const Node& node, std::unordered_map<K, V>& rhs) {
			if (!node.IsMap())
      			return false;

			rhs.clear();

    		for (const auto& element : node)
			{
				K key = element.first.as<K>();
				YAML::Node valueNode = element.second.as<YAML::Node>();
				V value = valueNode.as<V>();
				rhs.insert({key, value});
			}

    		return true;
  		}
	};

	template<>
	struct convert<glm::vec2>
	{
		static Node encode(const glm::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Zewada::Animation::Frame>
	{
		static Node encode(const Zewada::Animation::Frame& rhs)
		{
			Node node;
			node["Duration"] = rhs.duration;
			const std::shared_ptr<Texture> texture = rhs.sprite->GetTexture();	
			if(texture->operator bool())
			{
				std::filesystem::path texPath(rhs.sprite->GetTexture()->GetPath());
				texPath = FileUtils::RelativePath(texPath);
				node["TexPath"] = texPath.string();
				const std::array<glm::vec2, 4>& UV = rhs.sprite->GetUV();
				node["UV"] = UV;
			}
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Zewada::Animation::Frame& rhs)
		{
			if(!node.IsMap())
				return false;

			if(node.size() == 1)
			{
				rhs.duration = node["Duration"].as<float>();
				rhs.sprite = std::make_shared<Sprite>();

				return true;
			}

			if(node.size() == 3)
			{
				rhs.duration = node["Duration"].as<float>();
				rhs.sprite = std::make_shared<Sprite>();
				std::string texPath = node["TexPath"].as<std::string>();
				rhs.sprite->SetTextureToLoad(texPath);
				std::array<glm::vec2, 4> uv = node["UV"].as<std::array<glm::vec2, 4>>();
				rhs.sprite->SetTexCoords(uv);

				return true;
			}

			return false;
		}
	};

	template<>
	struct convert<Zewada::Animation>
	{
		static Node encode(const Zewada::Animation& rhs)
		{
			Node node;
			node.push_back(rhs.frames);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Zewada::Animation& rhs)
		{
			if (!node.size() == 1)
				return false;

			rhs.frames = node.as<std::vector<Animation::Frame>>();

			return true;
		}
	};

	//only converter from library
	template <typename T, std::size_t N>
	Emitter& operator<<(Emitter& emitter, const std::array<T, N>& m) 
	{
  		emitter << BeginSeq;
  		for (const auto& v : m)
    		emitter << v;
  		emitter << EndSeq;
  		
		return emitter;
	}

	template <typename K, typename V>
	inline Emitter& operator<<(Emitter& emitter, const std::unordered_map<K, V>& m) {
  		emitter << BeginMap;
  		for (const auto& v : m)
    		emitter << Key << v.first << Value << v.second;
  		emitter << EndMap;
  		return emitter;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Zewada::Animation::Frame& v)
	{
		out << YAML::Flow;
		out << YAML::BeginMap;
		out << YAML::Key << "Duration" << YAML::Value << v.duration;
		const std::shared_ptr<Texture> texture = v.sprite->GetTexture();
		if(texture->operator bool())
		{
			std::filesystem::path texPath(v.sprite->GetTexture()->GetPath());
			texPath = FileUtils::RelativePath(texPath);
			out << YAML::Key << "TexPath" << YAML::Value << texPath.string();
			const std::array<glm::vec2, 4> UV = v.sprite->GetUV();
			out << YAML::Key << "UV" << YAML::Value << UV;
		}
		out << YAML::EndMap;

		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Zewada::Animation& v)
	{
		out << YAML::Flow;

		out << v.frames;

		return out;
	}

}




namespace Zewada {

	SceneSerializer::SceneSerializer()
	{
		m_file = "settings.nazo";
	}

	void SceneSerializer::SerializeEntity(YAML::Emitter& out, const GameObject& go)
	{
		out << YAML::BeginMap;

		if (go.HasComponent<Tag>())
		{
			out << YAML::Key << "Tag";
			out << YAML::BeginMap;

			auto& tag = go.GetComponent<Tag>();
			out << YAML::Key << "Tag" << YAML::Value << tag.name;
			out << YAML::Key << "ID" << YAML::Value << tag.id;

			out << YAML::EndMap;
		}

		if (go.HasComponent<Transform>())
		{
			out << YAML::Key << "Transform";
			out << YAML::BeginMap;

			auto& tc = go.GetComponent<Transform>();
			out << YAML::Key << "Position" << YAML::Value << tc.pos;
			out << YAML::Key << "Rotation" << YAML::Value << tc.rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.scale;

			out << YAML::Key << "Parent" << YAML::Value << tc.parent;
			out << YAML::Key << "ChildrenCount" << YAML::Value << tc.children.size();
			out << YAML::Key << "Children";
			out << YAML::BeginMap;
			for(int i = 0; i < tc.children.size(); i++)
			{
				out << YAML::Key << i << YAML::Value << tc.children[i];
			}
			out << YAML::EndMap;

			out << YAML::EndMap;
		}

		if (go.HasComponent<SpriteRenderer>())
		{
			out << YAML::Key << "SpriteRenderer";
			out << YAML::BeginMap;

			auto& sprite = go.GetComponent<SpriteRenderer>();
			out << YAML::Key << "Color" << YAML::Value << sprite.color;
			const std::shared_ptr<Texture> texture = sprite.sprite->GetTexture();	
			if(texture->operator bool())
			{
				out << YAML::Key << "Sprite";
				out << YAML::BeginMap;
				std::filesystem::path texPath(sprite.sprite->GetTexture()->GetPath());
				texPath = FileUtils::RelativePath(texPath);
				out << YAML::Key << "TexturePath" << YAML::Value << texPath.string();
				out << YAML::Key << "UV";
				out << YAML::BeginMap;
				const std::array<glm::vec2, 4>& UV = sprite.sprite->GetUV();
				for(int i = 0; i < 4; i++)
				{
					out << YAML::Key << i << YAML::Value << UV[i]; 
				}
				out << YAML::EndMap;
				out << YAML::EndMap;
			}
			out << YAML::EndMap;
		}

		if(go.HasComponent<Camera>())
		{
			out << YAML::Key << "Camera";
			out << YAML::BeginMap;

			const Camera& camera = go.GetComponent<Camera>();
			out << YAML::Key << "Maincamera" << YAML::Value << camera.maincamera;

			out << YAML::EndMap;
		}

		if(go.HasComponent<Rigidbody2D>())
		{
			out << YAML::Key << "RigidBody2D";
			out << YAML::BeginMap;

			const Rigidbody2D& rb = go.GetComponent<Rigidbody2D>();
			out << YAML::Key << "AngularDamping" << YAML::Value << rb.angularDamping;
			out << YAML::Key << "LinearDamping" << YAML::Value << rb.linearDamping;
			out << YAML::Key << "Mass" << YAML::Value << rb.mass;
			out << YAML::Key << "BodyType" << YAML::Value << bodyType2Names[rb.bodyType];
			out << YAML::Key << "FixedRotation" << YAML::Value << rb.fixedRotation;
			out << YAML::Key << "ContinuousCollision" << YAML::Value << rb.continuousCollision;

			out << YAML::EndMap;
		}

		if(go.HasComponent<Box2DCollider>())
		{
			out << YAML::Key << "Box2DCollider";
			out << YAML::BeginMap;

			const Box2DCollider& cc = go.GetComponent<Box2DCollider>();
			out << YAML::Key << "HalfSize" << YAML::Value << cc.halfSize;
			out << YAML::Key << "Offset" << YAML::Value << cc.offset;

			out << YAML::EndMap;	
		}

		if(go.HasComponent<Circle2DCollider>())
		{
			out << YAML::Key << "Circle2DCollider";
			out << YAML::BeginMap;

			const Circle2DCollider& cc = go.GetComponent<Circle2DCollider>();
			out << YAML::Key << "Radius" << YAML::Value << cc.radius;
			out << YAML::Key << "Offset" << YAML::Value << cc.offset;

			out << YAML::EndMap;	
		}

		if(go.HasComponent<Polygon2DCollider>())
		{
			out << YAML::Key << "Polygon2DCollider";
			out << YAML::BeginMap;

			const Polygon2DCollider& pc = go.GetComponent<Polygon2DCollider>();
			out << YAML::Key << "Vertices" << YAML::Value << pc.vertices;
			out << YAML::Key << "Offset" << YAML::Value << pc.offset;

			out << YAML::EndMap;	
		}
		
		if(go.HasComponent<Edge2DCollider>())
		{
			out << YAML::Key << "Edge2DCollider";
			out << YAML::BeginMap;

			const Edge2DCollider& ec = go.GetComponent<Edge2DCollider>();
			out << YAML::Key << "Vertices" << YAML::Value << ec.vertices;
			out << YAML::Key << "Offset" << YAML::Value << ec.offset;
			out << YAML::Key << "PreviousGhost" << YAML::Value << ec.previousGhostVertex;
			out << YAML::Key << "NextGhost" << YAML::Value << ec.nextGhostVertex;

			out << YAML::EndMap;
		}

		if(go.HasComponent<NativeScript>())
		{
			out << YAML::Key << "NativeScript";
			out << YAML::BeginMap;

			const NativeScript& ns = go.GetComponent<NativeScript>();
			out << YAML::Key << "ClassName" << YAML::Value << ns.className;

			out << YAML::EndMap;
		}

		if(go.HasComponent<Animation>() && !go.HasComponent<AnimationManager>())
		{
			out << YAML::Key << "Animation";
			out << YAML::BeginMap;

			const Animation& ac = go.GetComponent<Animation>();
			out << YAML::Key << "Frames" << YAML::Value << ac.frames;

			out << YAML::EndMap;
		}

		if(go.HasComponent<AnimationManager>())
		{
			out << YAML::Key << "AnimationManager";
			out << YAML::BeginMap;

			AnimationManager& am = go.GetComponent<AnimationManager>();
			for(auto& animation : am.animations)
			{
				if(animation.second.frames.size() == 0)
				{
					Animation::Frame newFrame = Animation::Frame();
					animation.second.frames.push_back(newFrame);
				}
			}
			out << YAML::Key << "Animations" << YAML::Value << am.animations;

			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	void SceneSerializer::SerializeAssets(std::shared_ptr<AssetPool> assetPool)
	{
		const std::string filepath = std::filesystem::current_path().string() + "/" + m_file;
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "SpriteSheets" << YAML::Value << YAML::BeginSeq;
		auto& spriteSheets = assetPool->GetAllSpriteSheets();
		for(auto& ss : spriteSheets)
		{
			SerializeSpriteSheet(out, ss.second);
		}

		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	void SceneSerializer::DeserializeAssets(std::shared_ptr<AssetPool> assetPool)
	{
		YAML::Node data;
		try
		{
			std::string path = std::filesystem::current_path().string() + "/" + m_file;
			std::ifstream f(path.c_str());
			if(f.good())
				data = YAML::LoadFile(path);
			else
			{
				Z_INFO() << "No Settings File yet!";
				return;
			}
		}
		catch (YAML::ParserException e)
		{
			Z_INFO() << "No Settings File yet!";
			return;
		}
		if(data["SpriteSheets"])
		{
			for(auto ss : data["SpriteSheets"])
			{
				std::string path = ss["Path"].as<std::string>();
				int width = ss["Width"].as<int>();
				int height = ss["Height"].as<int>();
				int num = ss["Num"].as<int>();
				int spacing = ss["Spacing"].as<int>();
				std::shared_ptr<SpriteSheet> srcSpriteSheet = std::make_shared<SpriteSheet>(assetPool->GetTextureAbsolutePath(path.c_str()), width, height, num, spacing);
				assetPool->AddSpriteSheet(srcSpriteSheet);
			}
		}
	}

	void SceneSerializer::SerializeSpriteSheet(YAML::Emitter& out, std::shared_ptr<SpriteSheet> spriteSheet)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Path" << YAML::Value << spriteSheet->GetTexture()->GetPath();
		out << YAML::Key << "Width" << YAML::Value << spriteSheet->GetSpriteWidth();
		out << YAML::Key << "Height" << YAML::Value << spriteSheet->GetSpriteHeight();
		out << YAML::Key << "Num" << YAML::Value << spriteSheet->GetNumSprites();
		out << YAML::Key << "Spacing" << YAML::Value << spriteSheet->GetSpacing();
		out << YAML::EndMap;
	}

	static std::mutex mutex;

	void SceneSerializer::Serialize(std::shared_ptr<Scene> scene)
	{
		std::filesystem::path path = FileUtils::RelativePath(scene->GetPath());
		if(path.has_extension())
		{
			if(!(path.extension() == ".zs"))
			{
				return;
			}
		}
		else
		{
			return;
		}

		std::lock_guard<std::mutex> lock(mutex);
		const std::string& filepath = scene->GetPath();
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << scene->GetPath();
		out << YAML::Key << "BackgroundColor" << YAML::Value << scene->GetBackgroundColor();
		out << YAML::Key << "Gravity" << YAML::Value << scene->GetGravity();
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		auto entities = scene->GetCoordinator()->GetAllEntities();
		for(auto entity : entities)
		{
			GameObject gameObject = { entity, scene };
			if (!gameObject)
				break;
			if(gameObject.HasComponent<UnSerializable>())
				break;	

			SerializeEntity(out, gameObject);	
		}
		out << YAML::EndSeq;
		out << YAML::EndMap;
		std::string folder = std::filesystem::current_path().string() + "/" + filepath;
		std::ofstream fout(folder);
		fout << out.c_str();
	}

	std::shared_ptr<Scene> SceneSerializer::Deserialize(const std::string& filepath)
	{
		std::lock_guard<std::mutex> lock(mutex);
		YAML::Node data;
		try
		{
			data = YAML::LoadFile(std::filesystem::current_path().string() + "/" + filepath);
		}
		catch (YAML::ParserException e)
		{
			Z_ERROR() << "Failed to load file: " + filepath;
			return std::make_shared<Scene>("");
		}

		if(data.size() == 0)
		{
			Z_INFO() << filepath + " is empty.";
			return std::make_shared<Scene>(filepath);
		}

		if (!data["Scene"])
		{
			Z_ERROR() << "File " + filepath + " is not functional!";
			return std::make_shared<Scene>("");
		}
		
		ScenePlan scenePlan = {data["BackgroundColor"].as<glm::vec4>(), data["Gravity"].as<glm::vec2>()};

		std::shared_ptr<Scene> result = std::make_shared<Scene>(filepath, scenePlan);

		auto entities = data["Entities"];

		DeserializeEntities(entities, result);

		return result;
	}

	void SceneSerializer::SerializePrefabs(const GameObject& go, const std::string& filepath)
	{
		std::filesystem::path path = FileUtils::RelativePath(filepath);
		if(path.has_extension())
		{
			if(!(path.extension() == ".zp"))
			{
				return;
			}
		}
		else
		{
			return;
		}

		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Name" << YAML::Value << go.GetComponent<Tag>().name;
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		SerializeEntitesForPrefabs(out, go, go.GetScene());

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::string folder = (std::filesystem::current_path() / path).string();
		std::ofstream fout(folder);
		fout << out.c_str();
	}

	void SceneSerializer::DeserializePrefabs(const std::string& filepath, std::shared_ptr<Scene> scene)
	{
		std::filesystem::path relativePath = FileUtils::RelativePath(std::filesystem::path(filepath));
		YAML::Node data;
		try
		{
			data = YAML::LoadFile((std::filesystem::current_path() / relativePath).string());
		}
		catch (YAML::ParserException e)
		{
			Z_ERROR() << "Failed to load file: " + filepath;
		}

		if(data.size() == 0)
		{
			Z_INFO() << filepath + " is empty.";
		}
		
		auto& entities = data["Entities"];

		DeserializeEntities(entities, scene, true);
	}

	void SceneSerializer::SerializeEntitesForPrefabs(YAML::Emitter& out, const GameObject& go, std::shared_ptr<Scene> scene)
	{
		if(go.HasComponent<UnSerializable>())
		{
			return;
		}

		auto& transform = go.GetComponent<Transform>();		

		SerializeEntity(out, go);

		if(transform.children.size() != 0)
		{
			for(auto& child : transform.children)
			{
				GameObject childgo(child, go.GetScene());
				SerializeEntitesForPrefabs(out, childgo, scene);
			}
		}
	}


	void SceneSerializer::DeserializeEntities(const YAML::Node& entities, std::shared_ptr<Scene> scene, bool prefabs)
	{
		if (entities)
		{
			for (auto entity : entities)
			{
				std::unordered_map<ID, ID> OLDToID;
				std::string name;
				ID id;
				auto tagComponent = entity["Tag"];
				if (tagComponent)
				{
					name = tagComponent["Tag"].as<std::string>();
					id = tagComponent["ID"].as<ID>();
				}

				GameObject deserializedEntity;
				if(!prefabs)
				{
					deserializedEntity = GameObject(scene->CreateEntity(name, id), scene);
				}
				else
				{
					deserializedEntity = GameObject(scene->CreateEntity(name), scene);
					OLDToID.insert({id, deserializedEntity.GetComponent<Tag>().id});
				}

				auto transformComponent = entity["Transform"];
				if (transformComponent)
				{
					auto& tc = deserializedEntity.GetComponent<Transform>();
					tc.pos = transformComponent["Position"].as<glm::vec3>();
					tc.rotation = transformComponent["Rotation"].as<float>();
					tc.scale = transformComponent["Scale"].as<glm::vec2>();
					tc.parent = transformComponent["Parent"].as<Entity>();
					int count = transformComponent["ChildrenCount"].as<int>();
					for(int i = 0; i < count; i++)
					{
						tc.children.push_back(transformComponent["Children"][i].as<Entity>());
					}


					//based on that the parent will be the first object and then it goes down
					if(prefabs)
					{
						if(tc.parent != -1)
						{
							tc.parent = OLDToID[tc.parent];
							GameObject parent(scene->GetEntity(tc.parent), scene);
							auto& children = parent.GetComponent<Transform>().children;
							children.erase(std::remove(children.begin(), children.end(), id));
							children.push_back(deserializedEntity.GetComponent<Tag>().id);
						}
					}
				}

				auto spriteRendererComponent = entity["SpriteRenderer"];
				if (spriteRendererComponent)
				{
					deserializedEntity.AddComponent<SpriteRenderer>(SpriteRenderer());
					auto& src = deserializedEntity.GetComponent<SpriteRenderer>();
					src.color = spriteRendererComponent["Color"].as<glm::vec4>();
					if (spriteRendererComponent["Sprite"])
					{
						std::string texPath = spriteRendererComponent["Sprite"]["TexturePath"].as<std::string>();
						//idk why
						if(!prefabs)
							src.sprite->SetTextureToLoad(texPath);
						else
							src.sprite->SetTexture(scene->GetApplication()->GetAssetPool()->GetTexture(texPath.c_str()));
						std::array<glm::vec2, 4> uv;
						for(int i = 0; i < 4; i++)
						{
							uv[i] = spriteRendererComponent["Sprite"]["UV"][i].as<glm::vec2>();
						}
						src.sprite->SetTexCoords(uv);
					}
					else
					{
						src.sprite = std::make_shared<Sprite>();
					}
				}

				auto cameraComponent = entity["Camera"];
				if(cameraComponent)
				{
					deserializedEntity.AddComponent<Camera>(Camera());
					Camera& camera = deserializedEntity.GetComponent<Camera>();
					camera.maincamera = cameraComponent["Maincamera"].as<bool>();
				}

				auto rigidbodyComponent = entity["RigidBody2D"];
				if(rigidbodyComponent)
				{
					deserializedEntity.AddComponent<Rigidbody2D>(Rigidbody2D());
					auto& src = deserializedEntity.GetComponent<Rigidbody2D>();

					src.angularDamping = rigidbodyComponent["AngularDamping"].as<float>();
					src.linearDamping = rigidbodyComponent["LinearDamping"].as<float>();
					src.mass = rigidbodyComponent["Mass"].as<float>();				
					src.bodyType = names2BodyType[rigidbodyComponent["BodyType"].as<std::string>()];				
					src.fixedRotation = rigidbodyComponent["FixedRotation"].as<bool>();
					src.continuousCollision = rigidbodyComponent["ContinuousCollision"].as<bool>();
				}

				auto box2DCollider = entity["Box2DCollider"];
				if(box2DCollider)
				{
					deserializedEntity.AddComponent<Box2DCollider>(Box2DCollider());
					auto& src  = deserializedEntity.GetComponent<Box2DCollider>();

					src.halfSize = box2DCollider["HalfSize"].as<glm::vec2>();
					src.offset = box2DCollider["Offset"].as<glm::vec2>();
				}
				
				auto circle2DCollider = entity["Circle2DCollider"];
				if(circle2DCollider)
				{
					deserializedEntity.AddComponent<Circle2DCollider>(Circle2DCollider());
					auto& src  = deserializedEntity.GetComponent<Circle2DCollider>();

					src.radius = circle2DCollider["Radius"].as<float>();
					src.offset = circle2DCollider["Offset"].as<glm::vec2>();
				}		

				auto polygon2DCollider = entity["Polygon2DCollider"];
				if(polygon2DCollider)
				{
					deserializedEntity.AddComponent<Polygon2DCollider>(Polygon2DCollider());
					auto& src  = deserializedEntity.GetComponent<Polygon2DCollider>();

					src.vertices = polygon2DCollider["Vertices"].as<std::vector<glm::vec2>>();
					src.offset = polygon2DCollider["Offset"].as<glm::vec2>();
				}
				
				auto edge2DCollider = entity["Edge2DCollider"];
				if(edge2DCollider)
				{
					deserializedEntity.AddComponent<Edge2DCollider>(Edge2DCollider());
					auto& src  = deserializedEntity.GetComponent<Edge2DCollider>();

					src.vertices = edge2DCollider["Vertices"].as<std::vector<glm::vec2>>();
					src.offset = edge2DCollider["Offset"].as<glm::vec2>();
					src.previousGhostVertex = edge2DCollider["PreviousGhost"].as<glm::vec2>();
					src.nextGhostVertex = edge2DCollider["NextGhost"].as<glm::vec2>();
				}

				auto nativeScript = entity["NativeScript"];
				if(nativeScript)
				{
					deserializedEntity.AddComponent<NativeScript>(NativeScript());
					auto& src = deserializedEntity.GetComponent<NativeScript>();

					src.className = nativeScript["ClassName"].as<std::string>();
				}
				
				auto animation = entity["Animation"];
				if(animation)
				{
					deserializedEntity.AddComponent<Animation>(Animation());
					auto& src = deserializedEntity.GetComponent<Animation>();

					src.frames = animation["Frames"].as<std::vector<Animation::Frame>>();
				}

				auto animationManager = entity["AnimationManager"];
				if(animationManager)
				{
					deserializedEntity.AddComponent<AnimationManager>(AnimationManager());
					auto& src = deserializedEntity.GetComponent<AnimationManager>();
					
					src.animations = animationManager["Animations"].as<std::unordered_map<std::string, Animation>>();
				}
			}
		}
	}
}