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

bool sendCoins(const unsigned fromUserId, const unsigned toUserId, const double amount);

double getUserCoins(const unsigned userId);

int verifyTransactions();

void swapBlocks(TransactionBlock& block1, TransactionBlock& block2); //helper function to find the biggest blocks
void sortBlocks(); //helper function to find the biggest blocks
void unsortBlocks(); //arranging the blocks as originally after the biggest blocks function is called

double getCoinsOfBlock(const TransactionBlock& block); //helper function to find the biggest blocks
bool biggestBlocks(const unsigned number);

void addBlocks(const TransactionBlock* blocksToAdd, const unsigned size);


#endif // !TRANSACTIONBLOCK_H