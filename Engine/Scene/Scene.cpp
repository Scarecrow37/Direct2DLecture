#include "pch.h"
#include "Scene.h"

Scene::Scene(const std::shared_ptr<ILoggerUnicode>& logger)
    : Scene(logger, nullptr)
{
    _logger->Log(LogLevel::Trace, L"Scene constructor start.");
    _logger->Log(LogLevel::Trace, L"Scene constructor end.");
}

Scene::Scene(const std::shared_ptr<ILoggerUnicode>& logger, const Scene* parent)
    : _logger(logger), _parentScene(parent), _scale(1.f, 1.f), _rotation(0.f), _translation(0.f, 0.f),
      _transform(D2D1::Matrix3x2F::Identity()), _worldTransform(D2D1::Matrix3x2F::Identity())
{
    _logger->Log(LogLevel::Trace, L"Scene constructor start.");
    _logger->Log(LogLevel::Trace, L"Scene constructor end.");
}

void Scene::SetParentScene(const Scene* parentScene)
{
    _logger->Log(LogLevel::Trace, L"Scene set parent start.");
    _parentScene = parentScene;
    _logger->Log(LogLevel::Trace, L"Scene set parent end.");
}

Vector Scene::GetScale() const
{
    return _scale;
}

void Scene::SetScale(const Vector& scale)
{
    _logger->Log(LogLevel::Trace, L"Scene set scale start.");
    _scale = scale;
    _logger->Log(LogLevel::Trace, L"Scene set scale end.");
}

float Scene::GetRotation() const
{
    return _rotation;
}

void Scene::SetRotation(const float rotation)
{
    _logger->Log(LogLevel::Trace, L"Scene set rotation start.");
    _rotation = rotation;
    _logger->Log(LogLevel::Trace, L"Scene set rotation end.");
}

Vector Scene::GetTranslation() const
{
    return _translation;
}

void Scene::SetTranslation(const Vector& translation)
{
    _logger->Log(LogLevel::Trace, L"Scene set translation start.");
    _translation = translation;
    _logger->Log(LogLevel::Trace, L"Scene set translation end.");
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
    _logger->Log(LogLevel::Trace, L"Scene update transform start.");
    const Matrix scaleMatrix = Matrix::Scale(_scale);
    const Matrix rotationMatrix = Matrix::Rotation(_rotation);
    const Matrix translationMatrix = Matrix::Translation(_translation);
    _transform = scaleMatrix * rotationMatrix * translationMatrix;
    if (_parentScene != nullptr) _worldTransform = _transform * _parentScene->_worldTransform;
    else _worldTransform = _transform;
    _logger->Log(LogLevel::Trace, L"Scene update transform end.");
}
