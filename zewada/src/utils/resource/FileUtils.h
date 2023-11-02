#pragma once

#include <string.h>
#include <stddef.h>
#include "../Debug/Logger.h"
#include <filesystem>

namespace Zewada {
	struct FileUtils {
		static std::string read_file(const char* filepath) {
			FILE* file = fopen(filepath, "rt");
			if (file == NULL) {
				std::string error = "Could not open file: ";
				error.append(filepath);
				Z_ERROR(error);
				return " ";
			}
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}

		static std::filesystem::path RelativePath( const std::filesystem::path &path, 
        const std::filesystem::path &relative_to = std::filesystem::current_path())
    	{
        	std::filesystem::path p = std::filesystem::absolute(path);
        	std::filesystem::path r = std::filesystem::absolute(relative_to);

        	if( p.root_path() != r.root_path() )
        	    return p;

        	std::filesystem::path result;

        	std::filesystem::path::const_iterator itr_path = p.begin();
        	std::filesystem::path::const_iterator itr_relative_to = r.begin();
        	while( itr_path != p.end() && itr_relative_to != r.end() && *itr_path == *itr_relative_to ) {
        	    ++itr_path;
        	    ++itr_relative_to;
        	}

        	if( itr_relative_to != r.end() ) {
        	    ++itr_relative_to;
        	    while( itr_relative_to != r.end() ) {
        	        result /= "..";
        	        ++itr_relative_to;
        	    }
        	}

       		while( itr_path != p.end() ) {
         	   result /= *itr_path;
            	++itr_path;
        	}

        	return result;
    	}
	};
}