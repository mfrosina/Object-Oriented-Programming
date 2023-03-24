#pragma once

#ifndef TRANSACTION_H
#define TRANSACTION_H


struct Transaction {
	unsigned sender;
	unsigned receiver;
	double coins;
	long long time;
};

unsigned computeHash(const unsigned char* memory, int length);


#endif // !TRANSACTION_H