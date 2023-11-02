#pragma once

#include "../Events/Event.h"
#include <memory>

namespace Zewada {

	class Application;

	class Layer
	{
	public:
		Layer( const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float dt) {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_debugName; }
	protected:
		std::string m_debugName;
	};

}