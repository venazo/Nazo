#pragma once

#include "../utils/debug/Logger.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Events/ApplicationEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"
#include <AL/alc.h>
#include <AL/al.h>

namespace Zewada {

	class Window {
	private:
		GLFWwindow* m_window;
		GLFWmonitor* m_monitor;

		ALCcontext* m_audioContext;
		ALCdevice* m_audioDevice;

		void Init();
		void SetupCallbacks();
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		unsigned int GetWidth() const { return m_data.width; }
		unsigned int GetHeight() const { return m_data.height; }

		void SetIcon(std::string path);
		void Maximize();
		void SetFullscreen(bool value);

		void SetWindowSize(int width, int height);

		void SetEventCallback(const EventCallbackFn& callback) 
		{
			m_data.EventCallback = callback; 
		}
		Window(const char* name, int width, int height, bool vSync, bool resizeable);
		void OnClear();
		void OnUpdate();
		~Window();

		inline GLFWwindow* GetGLFWwindow() { return m_window; };
		inline bool IsFullscreen() {return glfwGetWindowMonitor(m_window ) != nullptr;}

	private:
		struct WindowData
		{
			std::string title;
			int width, height;
			int xpos, ypos;
			bool vSync;
			bool resizeable;

			bool updateViewPort;

			EventCallbackFn EventCallback;
		};

		WindowData m_data;
	};
}