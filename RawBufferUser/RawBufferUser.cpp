// RawBufferProject.cpp : Defines the entry point for the application.
//

#include "RawBufferUser.h"

#include <vector>

void printCompilerInfo()
{
	#ifdef __cplusplus
		std::cout << "CPP Version: " << __cplusplus << std::endl;
	#endif
	#ifdef __GNUC_MINOR__ 
		std::cout << "GCC Version: " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << std::endl;
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
	
	return 0;
}
