/*
* Copyright (c) <2015> <Antoine Richard and J�r�my Riffet, S.E.E.D>
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

/*!
* \file engine.hpp
* \author J�r�my RIFFET
* \version 0.1
* \copyright Copyright (c) 2015,
* Antoine "Avzgui" Richard and J�r�my "Chtimy" Riffet, S.E.E.D
* \license Zlib License.
*/

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#include <Seed/Graphics/control.hpp>
#include <Seed/Graphics/scene.hpp>



#define GLFW_INCLUDE_GLCOREARB


/*! \class Engine
* \brief class Engine, init the system and the scene
*/
class Engine
{
	public:
		/*!
		* \brief Constructor of class Scene
		*/
		Engine();
		/*!
		* \brief Destructor of class Node
		*/
		~Engine();

		void mainRender(Scene *scene);

		bool initSystem();

		bool initController();
		
		GLFWwindow* window;
		Controller *controller;

	private:

};

void mouse_buttonID_callback(GLFWwindow* window, int button, int action, int mods);

#endif