﻿#include "CameraManager.h"

#include <iostream>

#include "GameObjectManager.h"
#include "SceneCamera.h"

CameraManager* CameraManager::P_SHARED_INSTANCE = NULL;

Matrix4x4 CameraManager::getMainCameraViewMatrix()
{
	return this->mainCamera->getViewMatrix();
}

void CameraManager::setMainCamera(Camera* camera)
{
	mainCamera = camera;
}

void CameraManager::setMainCameraByIndex(int index)
{
	if (index > cameras.size())
	{
		std::cout << "Camera Index over Cameras in system" << std::endl;
		return;
	}
	setMainCamera(cameras[index]);
}

void CameraManager::addCamera(Camera* camera)
{
	if (mainCamera == NULL)
		setMainCamera(camera);
	this->cameras.push_back(camera);
}

void CameraManager::removeCamera(Camera* camera)
{
	std::string name = camera->getName();
	int index = -1;

	for (int i = 0; i < this->cameras.size() && index == -1; i++)
	{
		if (this->cameras[i] == camera)
			index = i;
	}

	if (index != -1)
	{
		this->cameras.erase(this->cameras.begin() + index);
	}
}


CameraManager::CameraManager() {}
CameraManager::CameraManager(const CameraManager&) {}

CameraManager* CameraManager::getInstance() {
	return P_SHARED_INSTANCE;
}

void CameraManager::initialize()
{
	std::cout << "Camera Manager Initialized" << std::endl;
	P_SHARED_INSTANCE = new CameraManager();
	P_SHARED_INSTANCE->mainCamera = new SceneCamera("Scene Camera");
	//P_SHARED_INSTANCE->mainCamera->setPosition(0, 0, -1);
	P_SHARED_INSTANCE->mainCamera->setPosition(4, 2, -2);
	P_SHARED_INSTANCE->mainCamera->setRotation(0.5, -0.75, 0);
	P_SHARED_INSTANCE->mainCamera->updateViewMatrix();
	Vector3D position = P_SHARED_INSTANCE->mainCamera->getLocalPosition();
	//std::cout << "Scene Camera Initialized at Position : (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
	GameObjectManager::getInstance()->addObject(P_SHARED_INSTANCE->mainCamera);
	P_SHARED_INSTANCE->addCamera(P_SHARED_INSTANCE->mainCamera);
}

void CameraManager::destroy()
{
	if (P_SHARED_INSTANCE != NULL)
	{
		delete P_SHARED_INSTANCE;
	}
}
