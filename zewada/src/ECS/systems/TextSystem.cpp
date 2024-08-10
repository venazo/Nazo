#include "TextSystem.h"
#include <zpch.h>
#include "../../scene/Scene.h"
#include "../../scene/GameObject.h"

namespace Zewada
{
    void TextSystem::OnUpdate(float dt)
    {
        while(m_transforms.size() > 0)
        {
            Transform* trans = m_transforms.back();
            m_transforms.pop_back();
            delete trans;

            SpriteRenderer* sprite = m_spriteRenderers.back();
            m_spriteRenderers.pop_back();
            delete sprite;
        }

        for(auto entity : m_entities)
        {
            GameObject go(entity, m_scene);
            auto& transform = go.GetComponent<Transform>();
            auto& text = go.GetComponent<Text>();
            std::shared_ptr<Font> font;
            if(text.font.c_str() != "")
                font = m_scene->GetApplication()->GetAssetPool()->GetFont(text.font.c_str());
            else
                font = m_scene->GetApplication()->GetAssetPool()->GetFont("Assets\\Fonts\\OpenSans-Regular.TTF");
            auto characters = font->GetCharacters();

            float scale = text.scale;

            float x = transform.worldPos.x;
            float y = transform.worldPos.y;
            float z = transform.worldPos.z;

            float realsize = (text.scale * P2M) / 12.0f;

            std::string::const_iterator c;
            for (c = text.text.begin(); c != text.text.end(); c++)
            {
                const Character ch = characters[*c];

                float w = ch.size.x * realsize;
                float h = ch.size.y * realsize;

                float xpos = x + 0.5f * w + ch.bearing.x * realsize;
                float ypos = y + + 0.5f * h + (ch.size.y - ch.bearing.y) * realsize;

                Transform* transform = new Transform();
                SpriteRenderer* spriteRenderer = new SpriteRenderer();

                transform->worldPos = glm::vec3(xpos, ypos, z);
                transform->worldScale = glm::vec2(w, h);

                spriteRenderer->color = text.color;
                spriteRenderer->sprite = ch.sprite;

                m_transforms.push_back(transform);
                m_spriteRenderers.push_back(spriteRenderer);

                m_scene->GetApplication()->GetRenderer2D()->Submit(transform, spriteRenderer, (int)-2);

                x += ch.advance * realsize;
            }
        }
    }
}