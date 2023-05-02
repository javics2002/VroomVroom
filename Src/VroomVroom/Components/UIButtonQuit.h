#pragma once

#ifndef __VROOMVROOM_UIBUTTON_QUIT
#define __VROOMVROOM_UIBUTTON_QUIT

#include "EntityComponent/Components/UIButton.h"

namespace VroomVroom {
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
		Update UITransform info to image
		*/
		void update(const double& dt) override;

		void execute() override;
	};
}
#endif

