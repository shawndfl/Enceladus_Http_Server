/*
 * Config.h
 *
 *  Created on: Feb 1, 2022
 *      Author: shawn
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

#include <string>

namespace ehs {
/**
 * This class reads a json config
 */
class Config {
public:
	virtual ~Config();

	static const Config& load(const std::string &jsonFilename);

	static const Config& get();

	std::string     cert;
	std::string     pass;
	int             threads;
	std::string     content;
	int             listeningPort;

private:
	Config();
	Config(const Config&);
	Config& operator =(const Config&);

	static Config config_;

};
}
#endif /* SRC_CONFIG_H_ */
