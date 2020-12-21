#include "LightManager.h"
#include "ResourceManager.h"

shadow::LightManager& shadow::LightManager::getInstance()
{
    static LightManager lightManager{};
    return lightManager;
}

bool shadow::LightManager::initialize(GLsizei textureSize)
{
    if (textureSize <= 0)
    {
        SHADOW_ERROR("Invalid texture size ({})!", textureSize);
        return false;
    }
    this->textureSize = textureSize;
    uboLights = ResourceManager::getInstance().getUboLights();
    if (!dirFbo.initialize(false, GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT,
                           textureSize, textureSize, GL_DEPTH_COMPONENT, GL_FLOAT))
    {
        return false;
    }
    if (!spotFbo.initialize(false, GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT,
                            textureSize, textureSize, GL_DEPTH_COMPONENT, GL_FLOAT))
    {
        return false;
    }
    return true;
}

void shadow::LightManager::resize(GLsizei textureSize)
{
    assert(textureSize > 0);
    dirFbo.resize(textureSize, textureSize);
    spotFbo.resize(textureSize, textureSize);
    this->textureSize = textureSize;
}