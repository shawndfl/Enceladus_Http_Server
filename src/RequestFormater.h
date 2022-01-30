/*
 * RequestFormater.h
 *
 *  Created on: Jan 30, 2022
 *      Author: shawn
 */

#ifndef SRC_REQUESTFORMATER_H_
#define SRC_REQUESTFORMATER_H_

#include <string>

/**
 * Gets a real path from a root path on the host and a location path from the URI
 */
class RequestFormater {
public:
	RequestFormater();
	virtual ~RequestFormater();

	/**
	 * Return the absolute path to the resource
	 */
	std::string getResourcePath(const std::string& root, const std::string& location);
};

#endif /* SRC_REQUESTFORMATER_H_ */
