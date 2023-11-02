#include <zpch.h>
#include "CameraSystem.h"
#include "../../scene/Scene.h"
#include "../../scene/GameObject.h"

using namespace glm;

namespace Zewada {

	void CameraSystem::OnUpdate(float dt)
	{
		for(auto entity : m_entities)
		{
			Camera& cam = m_coordinator.lock()->GetComponent<Camera>(entity);
			Transform& transform = m_coordinator.lock()->GetComponent<Transform>(entity);
			if(cam.maincamera)
			{
				transform.scale.y = transform.scale.x / m_ratio;
			}
			AdjustProjection(transform, cam);
			AdjustViewMatrix(transform, cam);
		}
	}
	
	void CameraSystem::Resize(float width, float height)
	{
		m_ratio = width / height;
		if(m_maincamera != -1)
		{
			Transform& transform = m_coordinator.lock()->GetComponent<Transform>(m_maincamera);
			transform.scale = glm::vec2(transform.scale.x, transform.scale.x / m_ratio);
		}
	}

	void CameraSystem::AdjustProjection(const Transform& transform, Camera& cam)
	{
		cam.projectionMatrix = glm::ortho(-transform.scale.x / 2 * cam.zoom, transform.scale.x / 2 * cam.zoom, -transform.scale.y / 2 * cam.zoom, transform.scale.y / 2 * cam.zoom, -100.0f, 100.0f);
	}

	void CameraSystem::AdjustViewMatrix(const Transform& transform, Camera& cam)
	{
		glm::vec3 cameraFront(transform.pos.x, transform.pos.y, transform.pos.z);
		glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
		cam.viewMatrix = glm::lookAt(glm::vec3(transform.pos.x, transform.pos.y, transform.pos.z + 100.0f), transform.pos, cameraUp);
	}

	void CameraSystem::SetMaincamera(Entity entity)
	{
		if(m_maincamera != -1)
		{
			m_coordinator.lock()->GetComponent<Camera>(m_maincamera).maincamera = false;
		}
		m_maincamera = entity;
		if(entity != -1)
		{
			m_coordinator.lock()->GetComponent<Camera>(m_maincamera).maincamera = true;
			m_coordinator.lock()->GetComponent<Transform>(m_maincamera).scale = glm::vec2(16.0f, 16.0f / m_ratio);
		}
	}

	void CameraSystem::DestroyEntity(Entity entity)
	{
		if(m_coordinator.lock()->GetComponent<Camera>(entity).maincamera)
		{
			m_maincamera = -1;
		}
	}
	
	const Entity CameraSystem::GetMaincameraObject()
	{
		if(m_maincamera == -1)
		{
			for(auto& entity : m_entities)
			{
				GameObject go = GameObject(entity, m_scene.lock());
				if(go.GetComponent<Camera>().maincamera)
					m_maincamera = entity;
			}
		}	
		return m_maincamera;
	}

	Camera& CameraSystem::GetMaincamera() 
	{
		if(m_maincamera == -1)
		{
			for(auto& entity : m_entities)
			{
				GameObject go = GameObject(entity, m_scene.lock());
				if(go.GetComponent<Camera>().maincamera)
					m_maincamera = entity;
			}
		}	
		return m_coordinator.lock()->GetComponent<Camera>(m_maincamera);
	}
}