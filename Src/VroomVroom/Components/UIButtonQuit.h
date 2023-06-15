#pragma once

#ifndef __VROOMVROOM_UIBUTTON_QUIT
#define __VROOMVROOM_UIBUTTON_QUIT

#include "Render/UIComponents/UIButton.h"
#include "EntityComponent/FactoryComponent.h"

namespace me {
	class AudioSource;
}

namespace VroomVroom {
	

	class FactoryUIButtonQuit : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};

	
	/**
	The UISpriteRenderer class represents a visual object in 2D space as a screen overlay that will be attached to an entity.
	*/
	class UIButtonQuit : public me::UIButton
	{
		int windowWidth = 0, windowHeight = 0;

	public:
		/**
		Construct a new UISpriteRenderer component and save necesary info
		@param name: name saved in RenderManager map and used for entity that attached in node
		@param meshName: name of .png file
		*/
		UIButtonQuit();
		//Destroy RenderManager map saved image
		~UIButtonQuit();

		/**
		Get info for mButtonAudio
		*/
		void start() override;

		/**
		Update UITransform info to image
		*/
		void update(const double& dt) override;
		/*
		* Exits the game itself.
		*/
		void execute() override;
		/*
		*Changes certain values to allow a sound to be playied only ione time when hovwering a button
		*/
		void toggleHover();
	private:
		me::AudioSource* mButtonAudio;
		bool toggleSound = false;
		bool stoppedSound = true;
	};
}
#endif

