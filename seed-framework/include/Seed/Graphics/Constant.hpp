#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include <iostream>

const int WIDTH = 1024;
const int HEIGHT = 768;

const std::string pathToShaders = "ressources/Materials/DefaultMaterial/Shaders/";
const std::string pathToTextures = "ressources/textures/";
const std::string pathToModels = "ressources/models/";
const std::string pathToDefaultShadersDir = "default/";

#define TEXTURE_AMBIANT 0
#define TEXTURE_DIFFUSE 1
#define TEXTURE_SPECULAR 2

#define SEED_ERROR_FILE_LOCATION 50;
#define SEED_ERROR_DEFAULT_SHADER_NOT_FOUND 51
#define SEED_SUCCESS 1

#endif