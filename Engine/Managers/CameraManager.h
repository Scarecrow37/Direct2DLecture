#pragma once
#include "../Camera/Camera.h"
#include "../World/World.h"


class CameraManager
{
public:
    CameraManager(const CameraManager& other) = delete;
    CameraManager(CameraManager&& other) noexcept = delete;
    CameraManager& operator=(const CameraManager& other) = delete;
    CameraManager& operator=(CameraManager&& other) noexcept = delete;
    ~CameraManager();

    static void SetActivatedCamera(int index);
    static void SetActivatedCamera(Camera* camera);

    static void Initialize(World* world, D2DRenderer* renderer);
    static void Update();
    static void Finalize();

    template <typename T>
    static T* CreateCamera(const int index)
    {
        if (!std::is_base_of<Camera, T>::value) throw Exception(L"T is not derived from Camera");
        T* camera = new T();
        GetInstance()._cameras[index] = camera;
        return camera;
    }

private:
    CameraManager() = default;
    static CameraManager& GetInstance();
    static void SetWorldCullingBound();
    static void UpdateCameraTransform();
    
    World* _world;
    D2DRenderer* _renderer;
    Camera* _activatedCamera;
    std::unordered_map<int, Camera*> _cameras;
};
