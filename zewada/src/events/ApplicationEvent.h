#pragma once

#include "Event.h"

namespace Zewada {

	class Scene;

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_width(width), m_height(height) {}

		unsigned int GetWidth() const { return m_width; }
		unsigned int GetHeight() const { return m_height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_width, m_height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class GameStartEvent : public Event
	{
	public:
		GameStartEvent() = default;

		EVENT_CLASS_TYPE(GameStart)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class GameEndEvent : public Event
	{
	public:
		GameEndEvent() = default;

		EVENT_CLASS_TYPE(GameEnd)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class LoadSceneEvent : public Event
	{
	private:
		std::string m_path;
	public:
		LoadSceneEvent(const std::string& path)
			: m_path(path) {}

		inline const std::string& GetPath() {return m_path;}
		
		EVENT_CLASS_TYPE(LoadScene)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ChangedSceneEvent : public Event
	{
	private:
		std::shared_ptr<Scene> m_scene;
	public:
		ChangedSceneEvent(std::shared_ptr<Scene> scene)
			: m_scene(scene) {}

		inline std::shared_ptr<Scene> GetScene() {return m_scene;}
		
		EVENT_CLASS_TYPE(ChangedScene)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class SaveSceneEvent : public Event
	{
	public:
		SaveSceneEvent() = default;

		EVENT_CLASS_TYPE(SaveScene)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
