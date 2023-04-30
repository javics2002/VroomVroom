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
	protected:
		//Smoothing of the camera. Should be between 0 and 1.
		float mSmooth;

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
		me::Vector3 mPositionOffset;
		me::Vector3 mLookOffset;

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
		void update(const double& dt) override;

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
		void setPositionOffset(me::Vector3 offset);

		/**
		Sets offset to the look point, which is the target at 0, 0, 0
		@params target Offset to look to the target.
		*/
		void setLookOffset(me::Vector3 offset);

		/**
		Sets smoothing of the camera movement.
		@params smoothing Smoothing of the camera movement. Should be between 0 and 1.
		*/
		void setSmoothing(float smoothing);
	};
}
#endif