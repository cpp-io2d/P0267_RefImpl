
#include <cerrno>
#include <cstring>
#include <exception>
#include <iostream>
#include <system_error>

#if __has_include(<filesystem>)
	#include <filesystem>
#elif __has_include(<unistd.h>)
	#include <unistd.h>
#endif

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

// io2d uses its own main(), rather than Catch's, so as to set the running
// process' current working directory to that where input data files are
// located.
//
// Catch2 describes how to do a custom main(), at:
//   https://github.com/catchorg/Catch2/blob/master/docs/own-main.md

int main(int argc, char* argv[])
{
	// For now, set the app's CWD (Current Working Directory) to where the
	// app's executable is, presuming this info is available.
	if (argc >= 1 && argv[0] != nullptr) {
#if __has_include(<filesystem>)
		try {
			using namespace std::filesystem;
			current_path(path(argv[0]).parent_path());
		} catch (const std::exception & ex) {
			std::cerr <<
				"ERROR: Unable to set CWD via current_path(). what()=\"" <<
				ex.what() <<
				"\"\n";
			return 1;	// Return a non-zero integer to indicate failure
		}
#elif __has_include(<unistd.h>)
		std::string p = argv[0];
		const auto last_path_sep = p.find_last_of('/');
		if (last_path_sep != std::string::npos && last_path_sep > 0) {
			p = p.substr(0, last_path_sep);
			if (chdir(p.c_str()) != 0) {
				std::cerr <<
					"ERROR: Unable to set CWD via chdir(). strerror(errno)=\"" <<
					strerror(errno) <<
					"\"\n";
				return 1; // Return a non-zero integer to indicate failure
			}
		}
#endif
	}

	return Catch::Session().run(argc, argv);
}
