#pragma once

#ifndef __VROOMVROOM_UIBUTTON_SCENE
#define __VROOMVROOM_UIBUTTON_SCENE

#include "EntityComponent/Components/UIButton.h"

#include <string>
#include <vector>

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
		UIButtonScene();
		//Destroy RenderManager map saved image
		~UIButtonScene();

		/*
		* Creates the sprite of the button.
		* @param name: the name of the value saved on the sprites map..
		* @param material: the name of the sprite file.
		* @param zOrder: a value that stablishes if a button is in front or behind something.
		*/
		void init(std::string name, std::string materialName, int zOrder);

		/**
		Get info for UITransform, create the Sprite and set the start pos
		*/
		void start() override;

		/*
		* Sets the next scene that will be switched to.
		* @param newScene: the name of the scene.
		*/
		void setNewScene(std::string newScene);

		/*
		* Sets the player that will rotate when hovering over this button.
		* @param playerLook: Which player will rotate.
		*/
		void setPlayerLook(std::string playerLook);

		/*
		*Update UITransform info to image
		*/
		void update(const double& dt) override;

		/*
		* Changes the current scene to the new set scene.
		*/
		void execute() override;

		/*
		*Makes a the player rotate in the main menu screen.
		*/
		void togglePlayerLook(const double&);

		/*
		*Changes certain values to allow a sound to be playied only ione time when hovwering a button
		*/
		void toggleHover();

	};
}
#endif

