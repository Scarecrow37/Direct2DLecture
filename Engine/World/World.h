#pragma once

class GameObject;
class D2DRenderer;

class World
{
public:
    World(const AABB& defaultCullingBound);
    World(const World& other) = default;
    World(World&& other) noexcept = default;
    World& operator=(const World& other) = default;
    World& operator=(World&& other) noexcept = default;
    virtual ~World();

    void Initialize() const;
    void Update(float deltaTime);
    void LazyUpdate(float deltaTime);
    void Render(const D2DRenderer* renderer);
    void Clear();
    void SetCullingBound(AABB* bound);

    void AddGameObject(GameObject* gameObject);

    template <typename T>
    T* CreateGameObject()
    {
        if (!std::is_base_of<GameObject, T>::value) throw Exception(L"T is not derived from GameObject");
        T* gameObject = new T();
        AddGameObject(gameObject);
        return gameObject;
    }


    size_t GetRenderingObjectCount() const;

private:
    std::list<GameObject*> _gameObjects;
    AABB* _cullingBound;
    AABB _defaultCullingBound;

    void IncreaseRenderingObjectCount();
    void ResetRenderingObjectCount();

    size_t _renderingObjectCount;
    size_t _previousRenderingObjectCount;

    void UpdateCollision() const;
};
