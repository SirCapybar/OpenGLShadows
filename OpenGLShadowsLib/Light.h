#pragma once

#include <glm/glm.hpp>

namespace shadow
{
    template<typename T>
    class Light abstract
    {
    public:
        Light(T& t, float nearZ, float farZ);
        virtual ~Light() = default;
        void setData(T& data);
        T& getData();
        bool isDirty() const;
        bool isLightSpaceDirty() const;
        virtual glm::mat4 getLightSpace() = 0;
        virtual void updateLightSpace() = 0;
        virtual void setColor(glm::vec3 color) = 0;
        virtual void setStrength(float strength) = 0;
        virtual void setPosition(glm::vec3 position) = 0; // even if it's a directional light, it still needs a position for view matrix
        void setNearZ(float nearZ);
        void setFarZ(float farZ);
        float getNearZ() const;
        float getFarZ() const;
    protected:
        bool dirty{ true }, lightSpaceDirty{ true };
        T lightData{};
        float nearZ{}, farZ{};
    };
    template<typename T>
    inline void Light<T>::setData(T& data)
    {
        lightData = data;
        dirty = true;
    }
    template<typename T>
    inline T& Light<T>::getData()
    {
        dirty = false;
        return lightData;
    }
    template<typename T>
    inline bool Light<T>::isDirty() const
    {
        return dirty;
    }
    template<typename T>
    inline bool Light<T>::isLightSpaceDirty() const
    {
        return lightSpaceDirty;
    }
    template<typename T>
    inline void Light<T>::setNearZ(float nearZ)
    {
        this->nearZ = nearZ;
        lightSpaceDirty = true;
    }
    template<typename T>
    inline void Light<T>::setFarZ(float farZ)
    {
        this->farZ = farZ;
        lightSpaceDirty = true;
    }
    template<typename T>
    inline float Light<T>::getNearZ() const
    {
        return nearZ;
    }
    template<typename T>
    inline float Light<T>::getFarZ() const
    {
        return farZ;
    }
    template<typename T>
    inline Light<T>::Light(T& t, float nearZ, float farZ) : lightData(t), nearZ(nearZ), farZ(farZ)
    {}
}
