#pragma once
#ifndef __VROOMVROOM_CAMERAFOLLOW
#define __VROOMVROOM_CAMERAFOLLOW

#include "EntityComponent/Components/Component.h"
#include "Utils/Vector3.h"
#include <string>

namespace me {

	class Transform;
	class Entity;

	/**
	The CameraFollow class move camera to follow player assign
	*/
	class CameraFollow : public Component
	{
	private:
	protected:
		//entity player that we follow
		Transform* mTargetTransform = nullptr;
		//componenet transform of this.Entity
		Transform* mTransform;
		Vector3 mOffset;

	public:

		/**
		Construct a new CameraFollow component and assign the player
		*/
		CameraFollow();
		//Destroy om() map saved camera (ogreCamera)
		~CameraFollow();

		/**
		Get info for mTransform and create ogreCamera and set the start pos
		*/
		void start() override;

		/**
		Update transform info to camera node
		*/
		void update() override;

		/**
		Sets the target to follow
		@params target The transform component of the target.
		*/
		void setTarget(Transform* target);

		/**
		Sets the target to follow
		@params targetName The name of the entity to follow.
		*/
		void setTarget(std::string targetName);

		/**
		Sets offset to keep with the target
		@params target Offset to keep with the target.
		*/
		void setOffset(Vector3 offset);
	};
}
#endif