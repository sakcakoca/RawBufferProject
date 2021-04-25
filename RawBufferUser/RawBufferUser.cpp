﻿// RawBufferProject.cpp : Defines the entry point for the application.
//

#include "RawBufferUser.h"

#include <vector>

void printCompilerInfo()
{
	#ifdef __cplusplus
		std::cout << "CPP Version: " << __cplusplus << std::endl;
	#endif
	#ifdef __GNUC_MINOR__ 
		std::cout << "GCC Version: " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC__PATCH_LEVEL__ << std::endl;
	#endif
	#ifdef __clang__
		std::cout << "Clang Version: " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__ << std::endl;
	#endif
	#ifdef _MSC_VER
			std::cout << "MSC Version: " << _MSC_VER << std::endl;
	#endif
}

int main()
{
	printCompilerInfo();
	/**
	std::vector<int> v{ 1, 2, 3};
	auto two = std::find(v.begin(), v.end(), 2);
	for(int i = 0; i < 4096; i++)
	{
		v.push_back(i);
	}
	std::cout << *two << std::endl;
	*/
	return 0;
}
