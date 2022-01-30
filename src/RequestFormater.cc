/*
 * RequestFormater.cc
 *
 *  Created on: Jan 30, 2022
 *      Author: shawn
 */
#include <stdlib.h>
#include <limits.h>
#include "RequestFormater.h"

/*************************************************/
RequestFormater::RequestFormater() {

}

/*************************************************/
RequestFormater::~RequestFormater() {

}

/*************************************************/
std::string RequestFormater::getResourcePath(const std::string &root, const std::string &location) {
	char path[PATH_MAX];
	realpath(root.c_str(), path);
	return path;
}
