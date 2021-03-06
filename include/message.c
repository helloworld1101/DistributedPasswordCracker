/* 2018/11/20
 * define a message structure
 * */

#include <string.h>
#include <stdlib.h>
#include "command.h"
#include "config.h"
#include "helper.h"
#include "message.h"

Message response(enum COMMAND command, int clientID, unsigned requestID, char *other){
	Message res;
	res.command = command;
	res.clientID = clientID;
	res.requestID = requestID;
	strcpy(res.other, other);

	return res;
}

char *getHash(char *other) {
	char *hash = slice(other, 0, HASH_LENGTH - 1);
	return hash;
}

char *getPassword(char *other) {
	char *password = slice(other, HASH_LENGTH, HASH_LENGTH + PW_LENGTH);
	return password;
}

int getPackage(char *other) {
	char *tmp = slice(other, HASH_LENGTH, HASH_LENGTH + 3);
	return stringToUInt(tmp);
}
