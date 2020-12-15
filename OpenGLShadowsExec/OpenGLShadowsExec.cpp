#include "AppWindow.h"
#include "ResourceManager.h"
#include "MaterialModelMesh.h"
#include "SceneNode.h"
#include "Primitives.h"
#include "ShadowUtils.h"

int main()
{
    using namespace shadow;
    AppWindow& appWindow = AppWindow::getInstance();
    ResourceManager& resourceManager = ResourceManager::getInstance();
    if (!appWindow.initialize(1280, 720, "../../Resources"))
    {
        return 1;
    }
    std::shared_ptr<UboLights> uboLights = ResourceManager::getInstance().getUboLights();
    std::shared_ptr<DirectionalLight> dirLight = uboLights->getDirectionalLight();
    std::shared_ptr<SpotLight> spotLight = uboLights->getSpotLight();
    uboLights->setAmbient(0.1f);
    dirLight->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
    dirLight->setDirection(glm::vec3(-1.0f, -1.0f, 0.0f));
    //dirLight->setStrength(5.0f);
    spotLight->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
    spotLight->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
    spotLight->setStrength(222.0f);
    spotLight->setInnerCutOff(FPI * 0.5f);
    spotLight->setOuterCutOff(FPI);
    spotLight->setPosition(glm::vec3(0.0f, 5.0f, 0.0f));
    std::shared_ptr<Camera> camera = appWindow.getCamera();
    std::shared_ptr<PrimitiveData> planeData = Primitives::plane(5.0f, 5.0f);
    std::shared_ptr<TextureMesh> plane = std::make_shared<TextureMesh>(
        planeData->toTextureVertex(), planeData->getIndices(), resourceManager.getTexture("Grass.jpg"));
    //std::shared_ptr<ModelMesh> modelFlareGun = resourceManager.getModel("FlareGun/FlareGun.obj");
    //std::shared_ptr<ModelMesh> modelBackpack = resourceManager.getModel("Backpack/backpack.obj");
    //std::shared_ptr<MaterialModelMesh> modelCat = resourceManager.getMaterialModel("OrigamiCat/OrigamiCat.obj", std::make_shared<Material>(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.0f));
    std::shared_ptr<ModelMesh> modelGun = resourceManager.getModel("Gun/gun.obj");
    std::shared_ptr<Scene> scene = appWindow.getScene();
    std::shared_ptr<SceneNode> node = scene->addNode(), planeNode = scene->addNode();
    camera->setPosition(glm::vec3(0.0f, 1.0f, 1.0f));
    camera->setDirection(glm::vec3(0.0f, -1.0f, -1.0f));
    node->setMesh(modelGun);
    node->scale(glm::vec3(2.5f));
    planeNode->setMesh(plane);
    planeNode->translate(glm::vec3(0.0f, -1.5f, 0.0f));
    double timeDelta = 0.0;
    unsigned int secondCounter = 0U;
    while (!appWindow.shouldClose())
    {
        appWindow.loop(timeDelta);
        node->rotate(static_cast<float>(timeDelta) * 0.25f, glm::vec3(0.0f, 1.0f, 0.0f));
        resourceManager.updateShaders();
        double time = appWindow.getTime();
        if (static_cast<unsigned int>(time) > secondCounter)
        {
            secondCounter = static_cast<unsigned int>(time);
            SHADOW_INFO("{} FPS", appWindow.getFps());
        }
    }
    return 0;
}
