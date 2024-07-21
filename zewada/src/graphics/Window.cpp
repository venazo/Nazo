#include <zpch.h>
#include "Window.h"

#include <stb_image.h>

namespace Zewada {

	Window::Window(const char* title, int width, int height, bool vSync, bool resizeable) 
	{
		m_data.title = title;
		m_data.width = width;
		m_data.height = height;
		m_data.vSync = vSync;
		m_data.resizeable = resizeable;

		Init();
	}

	void Window::Init() {
		if (!glfwInit()) {
			std::cout << "Failed to initialize GLFW!" << std::endl;
			return;
		}

		if(m_data.resizeable)
			glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		else
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), NULL, NULL);
		if (!m_window) {
			glfwTerminate();
			std::cout << "Failed to create GLFW window!" << std::endl;
			return;
		}
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);
		SetupCallbacks();

		//vsyncON = 1, vsyncOFF = 0
		if(m_data.vSync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		int ok = gladLoadGL();
		if(ok == 0)
		{
			std::cout <<"Failed to initialize Glad!/n";
		}
		std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;

		m_monitor =  glfwGetPrimaryMonitor();
		glfwGetWindowPos(m_window, &m_data.xpos, &m_data.ypos);
		m_data.updateViewPort = true;

		const ALCchar* defaultDeviceName = alcGetString(0, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
		m_audioDevice = alcOpenDevice(defaultDeviceName);

		int* attributes = {0};
		m_audioContext = alcCreateContext(m_audioDevice, attributes);
		alcMakeContextCurrent(m_audioContext);
	}

	void Window::SetupCallbacks()
	{
		glfwSetWindowUserPointer(m_window, &m_data);

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.width = width;
			data.height = height;
			data.updateViewPort = true;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, true);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

    void Window::SetIcon(std::string path)
    {
		std::string path_c = std::filesystem::current_path().string() + "/" + path;

		GLFWimage* image = new GLFWimage;
		stbi_set_flip_vertically_on_load(true);
		int width, height;
		image->pixels = stbi_load(path_c.c_str(), &image->width, &image->height, 0, 4);
		glfwSetWindowIcon(m_window, 1, image);
		stbi_image_free(image->pixels);
    }

	void Window::Maximize()
	{
		glfwMaximizeWindow(m_window);
	}

    void Window::SetFullscreen(bool value)
    {
		if(value == IsFullscreen())
			return;

		static int width, height;

		if(value)
		{
			const GLFWvidmode * mode = glfwGetVideoMode(m_monitor);
			glfwGetWindowPos( m_window, &m_data.xpos, &m_data.ypos );
			glfwGetWindowSize( m_window, &width, &height );
			glfwSetWindowMonitor(m_window, m_monitor, 0, 0, mode->width, mode->height, 0);
			m_data.updateViewPort = true;
		}
		else
		{
			glfwSetWindowMonitor(m_window, nullptr, m_data.xpos, m_data.ypos, width, height, 0);
			m_data.width = width;
			m_data.height = height;
			m_data.updateViewPort = true;
		}
    }

    void Window::SetWindowSize(int width, int height)
    {
		glfwSetWindowSize(m_window, width, height);
		m_data.updateViewPort = true;
	}
	
	void Window::OnClear()
	{
		if(m_data.updateViewPort)
		{
			static int width, height;
            glfwGetFramebufferSize(m_window, &width, &height);
			glViewport(0, 0, width, height);
			m_data.updateViewPort = false;
		}
	}

	void Window::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	Window::~Window() 
	{
		alcDestroyContext(m_audioContext);
		alcCloseDevice(m_audioDevice);
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
	
}
