#include <Seed/Graphics/parserImage.hpp>

parserImage::parserImage()
{}

bool parserImage::readImage(const std::string path)
{
	int format = this->getFormat(path);
	switch (format)
	{
	case JPEG_FORMAT:
		break;
	case PNG_FORMAT:
		return PNG_parser(path);
		break;
	case BMP_FORMAT:
		return BMP_parser(path);
		break;
	case TGA_FORMAT:
		return TGA_parser(path);
		break;
	}
}

unsigned short parserImage::isBMPImage(const char* img)
{
	//Bitmap Windows -> BM ; bitmap OS/2 -> BA ; bitmap color icon OS/2 -> CI ; bitmap pointer of color OS/2 -> CP ; bitmap icon OS/2 -> IC ; bitmap pointer OS/2 -> PT
	if(img[0] == 'B')
	{
		if(img[1] == 'M')
		{
			return 1;
		}
		else if(img[1] == 'A')
		{
			return 2;
		}
	}
	else if(img[0] == 'C')
	{
		if(img[1] == 'I')
		{
			return 3;
		}
		else if(img[1] == 'P')
		{
			return 4;
		}
	}
	else if(img[0] == 'I' && img[1] == 'C')
	{
		return 5;
	}
	else if(img[0] == 'P' && img[1] == 'T')
	{
		return 6;
	}
	return 0;
}

bool parserImage::setPixels(char* img, int offset, int size)
{
	this->pixels = (void*)malloc(sizeof(char) * size);
	this->pixels = (void*)&img[offset];
	return true;
}

void parserImage::setWidth(unsigned int w)
{
	this->width = w;
}

void parserImage::setHeight(unsigned int h)
{
	this->height = h;
}

void parserImage::setDepth(unsigned short d)
{
	switch (d)
	{
		case 32:
			this->depth = GL_RGBA;
			break;
		case 24:
			this->depth = GL_RGB;
			break;
		default:
			printf("ERROR: format of palet of colors not supported\n");
	}
}

void parserImage::setCompression(unsigned short c)
{
	this->compression = c;
}

unsigned int parserImage::getWidth()
{
	return this->width;
}

unsigned int parserImage::getHeight()
{
	return this->height;
}

unsigned short parserImage::getDepth()
{
	return this->depth;
}

unsigned short parserImage::getCompression()
{
	return this->compression;
}

void* parserImage::getPixels()
{
	return this->pixels;
}

int parserImage::getFormat(const std::string path)
{
	std::string type;
	int i = 0;
	while (path[path.size() - i - 1] != '.' && i < path.size())
	{
		type[i] = path[path.size() - i - 1];
		i++;
	}

	//std::cout << type << std::endl;

	//BMP
	if ((type[0] == 'p' || type[0] == 'P') && (type[1] == 'm' || type[1] == 'M') && (type[2] == 'b' || type[2] == 'B'))
	{
		return BMP_FORMAT;
	}
	else if ((type[0] == 'g' || type[0] == 'G') && (type[1] == 'n' || type[1] == 'N') && (type[2] == 'p' || type[2] == 'P'))
	{
		return PNG_FORMAT;
	}
	else if ((type[0] == 'g' || type[0] == 'G') && ((type[1] == 'p' || type[1] == 'P') && (type[2] == 'j' || type[2] == 'J')) || ((type[1] == 'e' || type[1] == 'E') && (type[2] == 'p' || type[2] == 'P') && (type[3] == 'j' || type[2] == 'J')))
	{
		return JPEG_FORMAT;
	}
	else if ((type[0] == 'a' || type[0] == 'A') && (type[1] == 'g' || type[1] == 'G') && (type[2] == 't' || type[2] == 'T'))
	{
		return TGA_FORMAT;
	}
	return 0;
}

bool parserImage::BMP_parser(const std::string path)
{
	std::ifstream imgFile(path, std::ios::binary);
	//type of bmp image
	unsigned short type;

	//open fails?
	if (imgFile)
	{
		char* img;
		int size;

		//get length of file
		imgFile.seekg(0, imgFile.end);
		size = (int)imgFile.tellg();
		imgFile.seekg(0, imgFile.beg);

		//alloc size buf to img array
		img = (char*)malloc(size * sizeof(char));

		//copy image into char* buffer
		imgFile.read(img, size);

		//verify if file has been reading totally
		if (!imgFile)
		{
			printf("ERROR: error reading file %s\n", path);
			imgFile.close();
			return false;
		}

		//close file
		imgFile.close();

		//type of image BMP, 0 if it's not a BMP image
		type = isBMPImage(img);

		//test if image is a bmp image
		if (type > 0)
		{
			//read header of BMP image
			if (!readBMP(this, img, type))
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool parserImage::PNG_parser(const std::string path)
{
	//vector of char who caontains data of image loading
	std::vector<unsigned char> img;
	//load image
	unsigned error = lodepng::decode(img, this->width, this->height, path);
	//if image not loading
	if (error)
	{
		std::cout << "Error: parsing image PNG" << std::endl;
		return false;
	}
	//sizing pixels to contain data
	this->pixels = (void*)malloc(sizeof(char) * img.size());
	//copy data from img to pixels
	memcpy(this->pixels, &img[0], img.size());
	//get the depth of the img
	this->depth = GL_RGBA;
	return true;
}

bool parserImage::TGA_parser(const std::string path)
{
	TGA img;
	if (img.Load(path.c_str()))
	{
		struct tga_header t = img.tgaheader;
		int size = t.width * t.height * (t.bpp / 8);
		//sizing pixels to contain data
		this->pixels = (void*)malloc(sizeof(char) * size);
		//copy data from img to pixels
		memcpy(this->pixels, &img.imageData[0], size);
		this->height = t.height;
		this->width = t.width;
		//this->compression = 0;
		switch ((int)t.bpp)
		{
		case 24:
			this->depth = GL_RGB;
			break;
		case 32: 
			this->depth = GL_RGBA;
			break;
		}
		return true;
	}
}
