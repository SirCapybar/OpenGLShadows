#pragma once

#include "DirectedLight.h"

namespace shadow
{
    struct SpotLightData
    {
        glm::vec3 color{ 0.0f, 0.0f, 0.0f };
        float strength{ 0.0f };
        glm::vec3 direction{ 0.0f, 0.0f, -1.0f };
        float innerCutOff{ 0.0f };
        glm::vec3 position{ 0.0f, 0.0f, 0.0f };
        float outerCutOff{ 0.0f };
    };

    class SpotLight final : public DirectedLight<SpotLightData>
    {
    public:
        SpotLight(SpotLightData& data, float nearZ, float farZ);
        glm::mat4 getLightSpaceMatrix() override;
        void setColor(glm::vec3 color) override;
        void setStrength(float strength) override;
        void setDirection(glm::vec3 direction) override;
        void setPosition(glm::vec3 position) override;
        void setInnerCutOff(float innerCutOff);
        void setOuterCutOff(float outerCutOff);
    private:
        glm::mat4 lightSpaceMatrix{};
    };
}