//
//  Utils.h
//  
//
//  Created by David Reed on 2/15/15.
//  Copyright (c) 2015 David Reed. All rights reserved.
//

#ifndef __MacGLFW__Utils__
#define __MacGLFW__Utils__

#include <string>


/**
 try to find file with filePath

 @param filePath string containing the file name
 @param environmentVariable environment variable to use if filePath does not exist
 @return if filePath exists, it is returned as is. if filePath does not exist it looks for filePath in the directory specified by the environmentVariableParameter; if that exists, the full path (environmentVariable/filePath) is returned, otherwise and empty string is returned.
 */
std::string pathUsingEnvironmentVariable(std::string filePath, std::string environmentVariable);

/*!
 * \param filePath - path to the file
 * \returns contes of the file at filePath or empty string if file does not exist
 */


/**
 return contents of the file at filePath

 @param filePath path to the file
 @return contents of the file at filePath or empty string if file does not exist
 */
std::string contentsOfFile(std::string filePath);

/**
 returns new string with leading and trailing characters specified by whitespace parameter removed

 @param str string that is to be trimmed
 @param whitespace characters you want removed from the string (defaults to space and tab)
 @return string with leading and trailing whitespace characters removed
 */
std::string trim(const std::string& str, const std::string& whitespace = " \t");


#endif /* defined(__MacGLFW__Utils__) */
