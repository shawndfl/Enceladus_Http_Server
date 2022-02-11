/*
 * webSockets.h
 *
 *  Created on: Jan 31, 2022
 *      Author: shawn
 */

#ifndef SRC_WEBSOCKETS_H_
#define SRC_WEBSOCKETS_H_
/**
 * Handles web socket upgrades
 * See: https://datatracker.ietf.org/doc/html/rfc6455
 *
 */
class webSockets {
public:
	webSockets();
	virtual ~webSockets();
};

#endif /* SRC_WEBSOCKETS_H_ */
