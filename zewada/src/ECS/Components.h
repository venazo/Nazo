#pragma once

#include <glm/glm.hpp>
#include "../Graphics/OpenGL/Renderables/SpriteSheet.h"
#include "core/Coordinator.h"
#include "../physics2d/Physics2D.h"
#include <boost/shared_ptr.hpp>

using ID = int;

namespace Zewada
{

	class ScriptableEntity;

	namespace Components
	{
		struct Tag
		{
			Tag() = default;
			Tag(std::string &str, ID uuid)
				: name(str), id(uuid) {}
			std::string name;
			ID id;
		};

		struct Transform
		{
			//read only at runtime
			glm::vec3 pos = glm::vec3();
			glm::vec3 worldPos = glm::vec3();
			glm::vec2 scale = glm::vec2();
			glm::vec2 worldScale = glm::vec2();
			float rotation = 0.0f;
			
			//read and write at runtime
			ID parent = -1;
			std::vector<ID> children;
			bool destroyed = false;

			Transform() = default;
			Transform(glm::vec3 c_pos)
				: pos(c_pos) {}
			Transform(glm::vec3 c_pos, glm::vec2 c_scale)
				: pos(c_pos), scale(c_scale) {}
			Transform(glm::vec3 c_pos, glm::vec2 c_scale, float c_rotation)
				: pos(c_pos), scale(c_scale), rotation(c_rotation) {}
		};

		struct SpriteRenderer
		{
			glm::vec4 color;
			std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
			SpriteRenderer() = default;
			SpriteRenderer(glm::vec4 c_color)
				: color(c_color) {}
			SpriteRenderer(std::shared_ptr<Sprite> c_sprite)
				: color(1.0f, 1.0f, 1.0f, 1.0f), sprite(c_sprite) {}
			SpriteRenderer(std::shared_ptr<Texture> c_texture)
				: color(1.0f, 1.0f, 1.0f, 1.0f), sprite(std::make_shared<Sprite>(c_texture)) {}
			SpriteRenderer(std::shared_ptr<Sprite> c_sprite, glm::vec4 c_color)
				: color(c_color), sprite(c_sprite) {}
			SpriteRenderer(std::shared_ptr<Texture> c_texture, glm::vec4 c_color)
				: color(c_color), sprite(std::make_shared<Sprite>(c_texture)) {}
		};

		struct Camera
		{
			float zoom = 1.0f;
			glm::mat4 projectionMatrix, viewMatrix;
			bool maincamera = false;

			Camera() = default;
			Camera(bool c_maincamera)
				: maincamera(c_maincamera) {}
		};

		struct UnSerializable
		{
		};

		struct Rigidbody2D
		{
			//read only is only needed to initialize
			float angularDamping = 0.8f;
			float linearDamping = 0.9f;
			float mass = 1.0f;
			BodyType bodyType = BodyType::Static;
			bool fixedRotation = false;
			bool continuousCollision = false;

			b2Body *rawBody = nullptr;
			Rigidbody2D() = default;
		};

		struct Box2DCollider
		{
			glm::vec2 halfSize = glm::vec2(1.0f, 1.0f);
			glm::vec2 offset = glm::vec2();
			glm::vec2 origin = glm::vec2();
		};

		struct NativeScript
		{
			std::string className = "NONE";
			std::shared_ptr<ScriptableEntity> script;

			NativeScript() = default;
			NativeScript(std::string c_className)
				: className(c_className)
			{}
		};
	}

	using namespace Components;
}