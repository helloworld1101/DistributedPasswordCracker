/* 2018/12/12
 * version 1.0
 * */

#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/helper.h"
#include "../lib/config.h"
#include "../lib/message.h"

char *slice(char *string, int from, int to) {
	if(from > to) return NULL;
	if(from > strlen(string)) return NULL;
	if(to - from > strlen(string)) return NULL;

	char *substr = malloc(to - from);
	int i = 0;
	for(i = 0; i < to - from; i++) {
		substr[i] = string[i + from];
	}
	substr[i] = '\0';

	return substr;
}

unsigned int stringToUInt(char *string) {
	unsigned int i;
	char *ptr;

	return (unsigned int) strtol(string, &ptr, 10);
}

char *getFrom(char *other) {
	unsigned int package = getPackage(other);

	char *from = malloc(PW_LENGTH);
	memset(from, 'a', PW_LENGTH);
	from[0] = package + 96;

	return from;
}

char *getTo(char *from) {
	char *to = malloc(PW_LENGTH);
	strcpy(to, from);
	to[0]++;

	return to;
}

// password combine only lower characters
char *getNext(const char *from) {
	char *result = (char*)malloc(PW_LENGTH);
	strcpy(result, from);

	int i = PW_LENGTH;

	while(result[--i] == 'z');
	result[i]++;
	while(result[++i] == 'z')
		result[i] = 'a';

	return result;
}

char *solve(char *from, char *to, char *hash) {
	char *iterator = (char *)malloc(PW_LENGTH);
	strcpy(iterator, from);

	while(strcmp(iterator, to) < 0) {
		if(strcmp(crypt(iterator, SALT), hash) == 0) {
			return iterator;
		}
		iterator = getNext(iterator);
	}
	
	return NULL;
}

char *solvePassword(char *other) {
	char *hash = getHash(other);
	char *from = getFrom(other);
	char *to = getTo(from);

	char  *password = solve(from, to, hash);

	return password;
}