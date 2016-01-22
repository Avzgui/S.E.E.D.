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
* \file directionnalLight.hpp
* \brief Directionnallights of the scene
* \author J�r�my RIFFET
* \version 0.1
* \copyright Copyright (c) 2015,
* Antoine "Avzgui" Richard and J�r�my "Chtimy" Riffet, S.E.E.D
* \license Zlib License.
*/


#ifndef DIRECTIONNALLIGHT_HPP
#define DIRECTIONNALLIGHT_HPP

//OTHGER INCLUDES
#include <glm/glm.hpp>
#include <iostream>
//SEED INCLUDES
#include <Seed/Graphics/lights/light.hpp>

/*! \class DirectionnalLight
* \brief DirectionnalLight of the scene
*/
class DirectionnalLight : public Light
{
public:
	/*!
	* \brief Constructor of class DirectionnalLight
	* \param name Name of the light
	* \param color Color of the light
	* \param position Position of the light
	* \param direction Direction of the light
	* \param K Attenuation coefficient of light
	* \param color Color of the light
	* \param near Near frustrum of the light
	* \param far Far frustrum of the light
	*/
	DirectionnalLight(const std::string &name, const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &K, const glm::vec3 &color = glm::vec3(1.0f), const float &near = 1.0f, const float &far = 10.0f);
	/*!
	* \brief Destructor of class DirectionnalLight
	*/
	~DirectionnalLight();
	void afficher(){}

	/*!
	* \brief get the direction of the light
	* \return the direction of the light
	*/
	glm::vec3 getDirection();
	/*!
	* \brief Get the light coefficients 
	* \return K(Ambiant, Diffuse, Specular)
	*/
	glm::vec3 getK();

private:
	glm::vec3 direction;
	glm::vec3 K;
};

//structure for UBO of light
struct directionnalLightStruct
{
	glm::vec4 direction;
	glm::vec4 color;
	glm::ivec4 size;
	glm::vec4 K;
};

#endif