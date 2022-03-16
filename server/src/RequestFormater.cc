/*
 * RequestFormater.cc
 *
 *  Created on: Jan 30, 2022
 *      Author: shawn
 */
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "RequestFormater.h"
#include "Logging.h"

namespace ehs {

/*************************************************/
RequestFormater::RequestFormater() {
	defaultLocation_ = "/index.html";
}

/*************************************************/
RequestFormater::~RequestFormater() {

}

/*************************************************/
std::string RequestFormater::getResourcePath(const std::string &root, const std::string &loc) {
	char rootPath[PATH_MAX] = {0};
	char path[PATH_MAX] = {0};
	std::string location  = loc;

	// set the default
	if(location == "") {
		location = defaultLocation_;
	}

	// make sure location starts with a /
	if(location.size() == 0 || location[0] != '/') {
		location = "/" + location;
	}

	// get the real root
	if(realpath(root.c_str(), rootPath) == NULL) {
		LOGD("Error: getting root path " << root);
		return "";
	}

	// put together a temp path to make sure it is in the root path
	std::string tmpPath = std::string(rootPath) + location;
	if(realpath(tmpPath.c_str(), path) == NULL) {
		LOGD("Warning: location does not exist " << tmpPath);
		return "";
	}

	// make sure the path has the root in it.
	if(strncmp(path, rootPath, strlen(rootPath)) != 0) {
		LOGD("Error: " << path << " is outside of root " << rootPath);
		return "";
	}

	return tmpPath;
}

/*************************************************/
const std::string& RequestFormater::getDefaultLocation() const {
	return defaultLocation_;
}

/*************************************************/
void RequestFormater::setDefaultLocation(const std::string &defaultLocation) {
	defaultLocation_ = defaultLocation;
}
}
