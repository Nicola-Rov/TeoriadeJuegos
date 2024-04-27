#pragma once
#include "GLtexture.h"
#include <string>
using namespace std;
class ImageLoader
{
public:
	static GLtexture loadPng(string filePath);

};

