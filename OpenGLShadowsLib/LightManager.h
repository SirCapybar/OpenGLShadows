#pragma once

#include "UboLights.h"
#include "Framebuffer.h"

#include <memory>

namespace shadow
{
    class LightManager final
    {
    public:
        static LightManager& getInstance();
        bool initialize(GLsizei textureSize);
        void resize(GLsizei textureSize);
        inline GLsizei getTextureSize() const;
        inline GLuint getDirFbo() const;
        inline GLuint getSpotFbo() const;
        inline GLuint getTempFbo() const;
        inline GLuint getDirTexture() const;
        inline GLuint getSpotTexture() const;
        inline GLuint getTempTexture() const;
    private:
        LightManager() = default;
        std::shared_ptr<UboLights> uboLights{};
        GLsizei textureSize{};
        Framebuffer dirFbo{}, spotFbo{}, tempFbo{};
    };

    inline GLsizei LightManager::getTextureSize() const
    {
        assert(textureSize);
        return textureSize;
    }

    inline GLuint LightManager::getDirFbo() const
    {
        return dirFbo.getFbo();
    }

    inline GLuint LightManager::getSpotFbo() const
    {
        return spotFbo.getFbo();
    }
    inline GLuint LightManager::getTempFbo() const
    {
        return tempFbo.getFbo();
    }
    inline GLuint LightManager::getDirTexture() const
    {
        return dirFbo.getTexture();
    }
    inline GLuint LightManager::getSpotTexture() const
    {
        return spotFbo.getTexture();
    }
    inline GLuint LightManager::getTempTexture() const
    {
        return tempFbo.getTexture();
    }
}
