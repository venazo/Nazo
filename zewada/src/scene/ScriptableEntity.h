#pragma once

#include "GameObject.h"
#include <boost/config.hpp>

namespace Zewada {
    class ScriptableEntity
    {
        protected:
            template<typename T>
            T& GetComponent()
            {
                return m_gameObject.GetComponent<T>();
            }

            Application* GetApplication()
            {
                return m_gameObject.GetScene()->GetApplication();
            }
        public:

            virtual void OnStart(){}
            virtual void OnUpdate(float dt){}
            virtual void OnDestroy(){}

            virtual void OnBeginContact(const glm::vec2& hitNormal){}
            virtual void OnEndContact(const glm::vec2& hitNormal){}

            void SetGameObject(const GameObject go) {m_gameObject = go;}
            GameObject& GetGameObject() {return m_gameObject;}
        private:
            GameObject m_gameObject;
    };
}