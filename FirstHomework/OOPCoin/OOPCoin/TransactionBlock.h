#pragma once
#ifndef TRANSACTIONBLOCK_H
#define TRANSACTIONBLOCK_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include "Transaction.h"
#include "BlocksDatFile.h"

struct TransactionBlock {
	unsigned id;
	unsigned prevBlockId;
	unsigned prevBlockHash;
	int validTransactions;
	Transaction transactions[16];
};


unsigned generateBlockID();
bool existsBlockID(const unsigned id, TransactionBlock& block);

bool addTransactionToBlock(const Transaction& transaction);

bool sendCoins(const char* fromUserName, const char* toUserName, const double amount);
void printTransactions(const TransactionBlock& block);//to test
void printTBlock();//to test

double getUserCoins(const unsigned userId);

bool verifyTransactions();

void swapBlocks(TransactionBlock& block1, TransactionBlock& block2);
void sortBlocks();

double getCoinsOfBlock(const TransactionBlock& block);
void biggestBlocks(const unsigned number);

void addBlocks(const TransactionBlock* blocksToAdd, const unsigned size);


#endif // !TRANSACTIONBLOCK_H