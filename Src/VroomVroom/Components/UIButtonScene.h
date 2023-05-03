#pragma once

#ifndef __VROOMVROOM_UIBUTTON_SCENE
#define __VROOMVROOM_UIBUTTON_SCENE

#include "EntityComponent/Components/Component.h"
#include <string>
#include <vector>

#include "EntityComponent/Components/UIButton.h"

namespace me {
	class UITransform;
	class Transform;
	class AudioSource;
}

namespace VroomVroom {

	/**
	The UISpriteRenderer class represents a visual object in 2D space as a screen overlay that will be attached to an entity.
	*/
	class UIButtonScene : public me::UIButton
	{
	protected:

		std::string mNewScene;

		std::string mPlayerLook;
		std::vector<me::Transform*> mPlayerLookTransform;

		me::AudioSource* mHoverAudio;
		/*me::AudioSource* mClickAudio;
		me::Transform* mTransform;
		me::Transform* mChildTransform;*/
		
		
		Ogre::TextAreaOverlayElement* mButtonArea;

		int x = 0;

		int windowWidth =0 , windowHeight=0;

		bool scaled = false;
		bool toggleSound = false;
		bool stoppedSound = true;
		/*bool clickGot = false;*/

		float playerRotateAngle = 20.0;

	public:
		/**
		Construct a new UISpriteRenderer component and save necesary info
		@param name: name saved in RenderManager map and used for entity that attached in node
		@param meshName: name of .png file
		*/
		UIButtonScene();
		//Destroy RenderManager map saved image
		~UIButtonScene();

		void init(std::string name, std::string materialName, int zOrder);

		/**
		Get info for UITransform, create the Sprite and set the start pos
		*/
		void start() override;

		void setNewScene(std::string newScene);

		void setPlayerLook(std::string playerLook);

		/**
		Update UITransform info to image
		*/
		void update(const double& dt) override;

		void execute() override;

		void togglePlayerLook(const double&);

		void toggleHover();

	};
}
#endif

