#include "pch.h"
#include "Scene.h"

Scene::Scene()
    : Scene(nullptr)
{
    Logger::Log(LogLevel::Trace, L"Scene constructor start.");
    Logger::Log(LogLevel::Trace, L"Scene constructor end.");
}

Scene::Scene(const Scene* parent)
    : _parentScene(parent),
      _scale(1.f, 1.f), _rotation(0.f), _translation(0.f, 0.f), _center(0.f, 0.f),
      _transform(D2D1::Matrix3x2F::Identity()), _worldTransform(D2D1::Matrix3x2F::Identity()),
      _centerMatrix(D2D1::Matrix3x2F::Identity())
{
    Logger::Log(LogLevel::Trace, L"Scene constructor start.");
    Logger::Log(LogLevel::Trace, L"Scene constructor end.");
}

void Scene::SetParentScene(const Scene* parentScene)
{
    Logger::Log(LogLevel::Trace, L"Scene set parent start.");
    _parentScene = parentScene;
    Logger::Log(LogLevel::Trace, L"Scene set parent end.");
}

Vector Scene::GetScale() const
{
    return _scale;
}

void Scene::SetScale(const Vector& scale)
{
    Logger::Log(LogLevel::Trace, L"Scene set scale start.");
    _scale = scale;
    Logger::Log(LogLevel::Trace, L"Scene set scale end.");
}

float Scene::GetRotation() const
{
    return _rotation;
}

void Scene::SetRotation(const float rotation)
{
    Logger::Log(LogLevel::Trace, L"Scene set rotation start.");
    _rotation = rotation;
    Logger::Log(LogLevel::Trace, L"Scene set rotation end.");
}

Vector Scene::GetTranslation() const
{
    return _translation;
}

void Scene::SetTranslation(const Vector& translation)
{
    Logger::Log(LogLevel::Trace, L"Scene set translation start.");
    _translation = translation;
    Logger::Log(LogLevel::Trace, L"Scene set translation end.");
}

void Scene::SetCenter(const Vector& center)
{
    Logger::Log(LogLevel::Trace, L"BitmapScene set center start.");
    _center = center;
    Logger::Log(LogLevel::Trace, L"BitmapScene set center end.");
}

Vector Scene::GetCenter() const
{
    return _center;
}


Matrix Scene::GetTransform() const
{
    return _transform;
}

Matrix Scene::GetWorldTransform() const
{
    return _worldTransform;
}

Vector Scene::GetWorldLocation() const
{
    return {_worldTransform._31, _worldTransform._32};
}


void Scene::UpdateTransform()
{
    Logger::Log(LogLevel::Trace, L"Scene update transform start.");
    const Matrix scaleMatrix = Matrix::Scale(_scale);
    const Matrix rotationMatrix = Matrix::Rotation(_rotation);
    const Matrix translationMatrix = Matrix::Translation(_translation);
    _transform = scaleMatrix * rotationMatrix * translationMatrix;
    if (_parentScene != nullptr) _worldTransform = _transform * _parentScene->_worldTransform;
    else _worldTransform = _transform;
    UpdateCenterTransform();
    Logger::Log(LogLevel::Trace, L"Scene update transform end.");
}
