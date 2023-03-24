#pragma once
#ifndef BLOCKSDATFILE_H
#define BLOCKSDATFILE_H
#include <fstream>
#include <cstring>
#include "TransactionBlock.h"
#include "Transaction.h"

struct TransactionBlock;

struct BlocksDatFile
{
	constexpr static const char FILE_NAME[16] = "blocks.dat";

	static unsigned findNumberOfSavedBlocks();
	static TransactionBlock* readBlocksFromFile();
	static void addBlockToFile(const TransactionBlock& block);
	static void deleteBlock(const unsigned blockId);
};


#endif // !BLOCKSDATFILE_H

