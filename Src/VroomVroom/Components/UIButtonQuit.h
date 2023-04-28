#pragma once

#ifndef __VROOMVROOM_UIBUTTON_QUIT
#define __VROOMVROOM_UIBUTTON_QUIT

#include "EntityComponent/Components/Component.h"
#include <string>

namespace Ogre {
	class TextAreaOverlayElement;
}

namespace me {
	class UITransform;
}

namespace VroomVroom {
	/**
	The UISpriteRenderer class represents a visual object in 2D space as a screen overlay that will be attached to an entity.
	*/
	class UIButtonQuit : public me::Component
	{
	protected:
		//name for RenderManager map and for entity that attached in node
		std::string mName;
		//name of .png file
		std::string mSpriteName;
		//componenet transform of this.Entity
		me::UITransform* mUITransform;
		//static state of this.Entity 
		bool mStaticObject = false;

		std::string mNewScene;

		Ogre::TextAreaOverlayElement* mButtonArea;

		int x = 0;

	public:
		/**
		Construct a new UISpriteRenderer component and save necesary info
		@param name: name saved in RenderManager map and used for entity that attached in node
		@param meshName: name of .png file
		*/
		UIButtonQuit();
		//Destroy RenderManager map saved image
		~UIButtonQuit();

		void init(std::string name, std::string materialName, int zOrder);

		/**
		Get info for UITransform, create the Sprite and set the start pos
		*/
		void start() override;


		/**
		Update UITransform info to image
		*/
		void update(const double& dt) override;

		void execute();

		/**
			Set material.
			@param materialName: name of material, as written in MaterialResource.material.
		*/
		void setSpriteMaterial(std::string materialName);

		/**
		Name getter
		*/
		std::string getName();
	};
}
#endif

