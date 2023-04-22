#pragma once
#ifndef __VROOMVROOM_CAMERAFOLLOW
#define __VROOMVROOM_CAMERAFOLLOW

#include "EntityComponent/Components/Component.h"
#include "Utils/Vector3.h"
#include <string>

namespace me {
	class Transform;
	class Entity;
	class Camera;
}

namespace VroomVroom {
	/*
	The CameraFollow component manages the Transform and Camera components
	to track a target.
	*/
	class CameraFollow : public me::Component
	{
	private:
	protected:
		/*
		Entity's transform that the camera follows
		*/
		std::string mTargetName;
		me::Transform* mTargetTransform;

		/*
		Transform of the camera
		*/
		me::Transform* mCameraTransform;
		me::Camera* mCamera;
		me::Vector3 mOffset;

	public:

		/*
		Construct a new CameraFollow component and assign the player
		*/
		CameraFollow();
		//Destroy renderManager() map saved camera
		~CameraFollow();

		/*
		Get info for mTransform and create ogreCamera and set the start pos
		*/
		void start() override;

		/*
		Update transform info to camera node
		*/
		void update() override;

		/*
		Sets the target to follow
		@params target The transform component of the target.
		*/
		void setTargetName(std::string targetName);

		/*
		Sets the target to follow
		@params target The transform component of the target.
		*/
		void setTarget(me::Transform* target);

		/**
		Sets the target to follow
		@params targetName The name of the entity to follow.
		*/
		void setTarget(std::string targetName);

		/**
		Sets offset to keep with the target
		@params target Offset to keep with the target.
		*/
		void setOffset(me::Vector3 offset);
	};
}
#endif