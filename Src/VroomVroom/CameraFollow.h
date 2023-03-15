#pragma once
#ifndef __VROOM_CAMERA_FOLLOW
#define __VROOM_CAMERA_FOLLOW


#include "EntityComponent/Component.h"
#include "Utils/Vector3.h"
#include <list>

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
		Transform* mPlayerTr = nullptr;
		//componenet transform of this.Entity
		Transform* mTransform;
		Vector3 mOffset;

	public:

		/**
		Construct a new CameraFollow component and assign the player
		*/
		CameraFollow(Transform* player);
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



	};
}
#endif