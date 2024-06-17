#include "Scene.h"

Scene::Scene():
    _parentScene(nullptr), _scale({1.f, 1.f}), _rotation(0.f), _translation({0.f, 0.f}),
    _transform(D2D1::Matrix3x2F::Identity()), _worldTransform(D2D1::Matrix3x2F::Identity())
{
}

void Scene::SetParentScene(const Scene* parentScene)
{
    _parentScene = parentScene;
}

Vector Scene::GetScale() const
{
    return _scale;
}

void Scene::SetScale(const Vector& scale)
{
    _scale = scale;
}

float Scene::GetRotation() const
{
    return _rotation;
}

void Scene::SetRotation(float rotation)
{
    _rotation = rotation;
}

Vector Scene::GetTranslation() const
{
    return _translation;
}

void Scene::SetTranslation(const Vector& translation)
{
    _translation = translation;
}

Matrix Scene::GetTransform() const
{
    return _transform;
}

Matrix Scene::GetWorldTransform() const
{
    return _worldTransform;
}

void Scene::UpdateTransform()
{
    const Matrix scaleMatrix = Matrix::Scale(_scale);
    const Matrix rotationMatrix = Matrix::Rotation(_rotation);
    const Matrix translationMatrix = Matrix::Translation(_translation);
    _transform = scaleMatrix * rotationMatrix * translationMatrix;
    if (_parentScene != nullptr) _worldTransform = _transform * _parentScene->_worldTransform;
    else _worldTransform = _transform;
}
