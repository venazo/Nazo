#pragma once

#include <glm/glm.hpp>
#include "../Graphics/OpenGL/Renderables/SpriteSheet.h"
#include "core/Coordinator.h"
#include "../physics2d/Physics2D.h"
#include <boost/shared_ptr.hpp>
#include <array>
#include <unordered_map>
#include "../graphics/opengl/renderables/font.h"

namespace Zewada
{

	class ScriptableEntity;

	namespace Components
	{
		struct Tag
		{
			Tag() = default;
			Tag(std::string &str, int uuid)
				: name(str), id(uuid) {}
			std::string name;
			int id;
		};

		struct Transform
		{
			//read only at runtime
			glm::vec3 pos = glm::vec3();
			glm::vec3 worldPos = glm::vec3();
			glm::vec2 scale = glm::vec2(1.0f, 1.0f);
			glm::vec2 worldScale = glm::vec2();
			float rotation = 0.0f;
			
			//read and write at runtime
			int parent = -1;
			std::vector<int> children;
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
			glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
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

		struct NativeScript
		{
			std::string className = "NONE";
			std::shared_ptr<ScriptableEntity> script;

			NativeScript() = default;
			NativeScript(std::string c_className)
				: className(c_className)
			{}
		};

		struct Animation
		{
			struct Frame
			{
				std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
				float duration = 0.0f;

				Frame() = default;
				Frame(std::shared_ptr<Sprite> c_sprite)
					: sprite(c_sprite)
				{}
				Frame(float c_duration)
					: duration(c_duration)
				{}
				Frame(std::shared_ptr<Sprite> c_sprite, float c_duration)
					: sprite(c_sprite), duration(c_duration)
				{}
			};

			std::vector<Frame> frames{};
			int activeFrame = 0.0f;
			float dt = 0.0f;
			Animation() = default;
			Animation(std::vector<Frame> c_frames)
				: frames(c_frames)
			{}
		};

		struct AnimationManager
		{
			std::unordered_map<std::string, Animation> animations{};
			std::string activeAnimation;
		};

		struct Grid
		{
			float size = 1.0f;

			Grid() = default;
			Grid(float c_size)
				: size(c_size) {}

		};

		struct GridObject
		{
			glm::vec2 gridPos = glm::vec2();

			GridObject() = default;
			GridObject(const glm::vec2& vec)
				: gridPos(vec) {}
		};

		struct Text
		{
			std::string text = "";
			std::string font = "assets/fonts/OpenSans-Regular.TTF";
			float scale = 12;
			glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			Text() = default;
			Text(const std::string& c_text)
				: text(c_text) {}
		};
	}

	using namespace Components;
}