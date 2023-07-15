#include "TransactionBlock.h"
#include "User.h"
#include "Transaction.h"

const char IDS_FILE_NAME[28] = "unique-block-ids.txt";
unsigned numberOfBlocks = 0;
TransactionBlock blocks[512];


unsigned generateBlockID()
{
	if (numberOfBlocks == 0)
	{
		std::ofstream idsOut(IDS_FILE_NAME);
		if (!idsOut.is_open())
		{
			std::cout << "Can not assign unique id to the block.\n";
			return 0;
		}
		idsOut << 0;
		idsOut.close();
		return 0;
	}
	std::ifstream idsIn(IDS_FILE_NAME);
	if (!idsIn.is_open())
	{
		std::cout << "Can not assign unique id to the block.\n";
		return 0;
	}
	unsigned id;
	idsIn >> id;
	id += 1;
	idsIn.close();

	std::ofstream idsOut(IDS_FILE_NAME);
	if (!idsOut.is_open())
	{
		std::cout << "Can not assign unique id to the block.\n";
		return 0;
	}
	idsOut << id;
	idsOut.close();

	return id;
}

bool existsBlockID(const unsigned id, TransactionBlock& block)
{
	for (unsigned i = 0; i < numberOfBlocks; i++)
	{
		if (blocks[i].id == id)
		{
			block = blocks[i];
			return true;
		}
	}
	return false;
}

bool addTransactionToBlock(const Transaction& transaction)
{
	if (numberOfBlocks >= 256)
	{
		std::cout << "Error: can not add a new block\n";
		return false;
	}
	if (numberOfBlocks == 0)
	{
		TransactionBlock newBlock{};
		newBlock.id = generateBlockID();
		newBlock.prevBlockId = newBlock.id;
		newBlock.transactions[newBlock.validTransactions] = transaction;
		newBlock.validTransactions++;
		blocks[numberOfBlocks] = newBlock;
		numberOfBlocks++;
		BlocksDatFile::addBlockToFile(newBlock);
	}
	else if(blocks[numberOfBlocks-1].validTransactions < 16)
	{
		blocks[numberOfBlocks-1].transactions[blocks[numberOfBlocks-1].validTransactions] = transaction;
		blocks[numberOfBlocks-1].validTransactions++;
		BlocksDatFile::deleteBlock(blocks[numberOfBlocks - 1].id);
		BlocksDatFile::addBlockToFile(blocks[numberOfBlocks - 1]);
	}
	else
	{
		TransactionBlock newBlock{};
		unsigned prevId = blocks[numberOfBlocks-1].id;
		newBlock.id = generateBlockID();
		newBlock.prevBlockId = prevId;
		unsigned char* blockData = reinterpret_cast<unsigned char*>(&blocks[numberOfBlocks-1]);
		unsigned blockDataSize = sizeof(blocks[numberOfBlocks-1]);
		newBlock.prevBlockHash = computeHash(blockData, blockDataSize);
		newBlock.transactions[newBlock.validTransactions] = transaction;
		newBlock.validTransactions++;
		blocks[numberOfBlocks] = newBlock;
		numberOfBlocks++;
		BlocksDatFile::addBlockToFile(newBlock);
	}

	return true;
}

bool sendCoins(const unsigned fromUserId, const unsigned toUserId, double amount)
{
	User fromUser;
	User toUser;
	if (!existsUserById(fromUserId) || !existsUserById(toUserId))
	{
		std::cout << "Users with the given ids do not exist!\n";
		return false;
	}
	bool flag = false;
	if (toUserId != 0)
	{
		amount *= 420;
	}
	if (fromUserId != 0)
	{
		double oopCoins = 0;
		for (unsigned i = 0; i < numberOfBlocks; i++)
		{
			for (unsigned j = 0; j < blocks[i].validTransactions; j++)
			{
				if (blocks[i].transactions[j].receiver == fromUserId)
				{
					flag = true;
					oopCoins += blocks[i].transactions[j].coins;
				}
			}
		}
		if (oopCoins < amount)
		{
			std::cout << "The sender does not have enough coins to make a transaction\n";
			return false;
		}
	}
	Transaction transaction;
	transaction.sender = fromUserId;
	transaction.receiver = toUserId;
	transaction.coins = amount;
	long long now = time(nullptr);
	long long secondsFrom1970 = difftime(now, 1970);
	transaction.time = secondsFrom1970;

	addTransactionToBlock(transaction);

	if (fromUserId != 0 && toUserId != 0)
	{
		Transaction transactionMin;
		transactionMin.sender = 0;
		transactionMin.receiver = fromUserId;
		transactionMin.coins = -amount;
		transactionMin.time = secondsFrom1970;

		addTransactionToBlock(transactionMin);
	}

	return true;
}
double getUserCoins(const unsigned userId)
{
	double userCoins = 0;
	for (unsigned i = 0; i < numberOfBlocks; i++)
	{
		for (unsigned j = 0; j < blocks[i].validTransactions; j++)
		{
			if (blocks[i].transactions[j].receiver == userId)
			{
				userCoins += blocks[i].transactions[j].coins;
				
			}
		}
	}
	return userCoins;
}

void printTransactions(const TransactionBlock& block)
{
	for (unsigned i = 0; i < block.validTransactions; i++)
	{
		std::cout << "from: " << block.transactions[i].sender << " to: " << block.transactions[i].receiver << " amount: " << block.transactions[i].coins
			<< " time of transaction: " << block.transactions[i].time << "\n";
	}
}
void printTBlock()
{
	for (unsigned i = 0; i < numberOfBlocks; i++)
	{
		std::cout << "Transactions of block: " << blocks[i].id << " " << blocks[i].prevBlockId << " " << blocks[i].prevBlockHash << " :\n";
		printTransactions(blocks[i]);
	}
}

int verifyTransactions()
{
	for (unsigned i = 0; i < numberOfBlocks; i++)
	{
		if (blocks[i].validTransactions > 16
			|| blocks[i].validTransactions < 1)
		{
			return blocks[i].id;
		}
		if (i == 0)
		{

			continue;
		}
		else
		{
			if (blocks[i].prevBlockId != blocks[i - 1].id)
			{
				return blocks[i].id;
			}
			unsigned char* prevBlockData = reinterpret_cast<unsigned char*>(&blocks[i-1]);
			unsigned prevBlockDataSize = sizeof(blocks[i-1]);
			unsigned prevBlockHash = computeHash(prevBlockData, prevBlockDataSize);
			if (blocks[i].prevBlockHash != prevBlockHash)
			{
				return blocks[i].id;
			}
		}
	}
	return -1;
}

void swapBlocks(TransactionBlock& block1, TransactionBlock& block2)
{
	TransactionBlock temp = block1;
	block1 = block2;
	block2 = temp;
}
void sortBlocks()
{
	if (numberOfBlocks == 1)
	{
		return;
	}
	for (unsigned i = 0; i < numberOfBlocks; i++)
	{
		double coinsIBlock = 0, coinsKBlock = 0;
		for (unsigned j = i + 1; j < numberOfBlocks; j++)
		{
			coinsIBlock = getCoinsOfBlock(blocks[i]);
			coinsKBlock = getCoinsOfBlock(blocks[j]);
			if (coinsIBlock < coinsKBlock)
			{
				swapBlocks(blocks[i], blocks[j]);
			}
		}
	}
}
void unsortBlocks()
{
	for (unsigned i = 0; i < numberOfBlocks; i++)
	{
		for (unsigned j = i + 1; j < numberOfBlocks; j++)
		{
			if (blocks[i].id > blocks[j].id)
			{
				swapBlocks(blocks[i], blocks[j]);
			}
		}
		
	}
}
double getCoinsOfBlock(const TransactionBlock& block)
{
	double coinsInBlock = 0;
	for (unsigned i = 0; i < block.validTransactions; i++)
	{
		coinsInBlock += block.transactions[i].coins;
	}
	return coinsInBlock;
}

bool biggestBlocks(const unsigned number)
{
	if (number > numberOfBlocks)
	{
		std::cout << "Too big number is entered. There are not that much blocks in the system!\n";
		return false;
	}
	sortBlocks();
	long long now = time(nullptr);
	char time[128];
	sprintf(time, "%lld", now);
	char fileName[256];
	strcpy(fileName, "biggest-blocks-");
	strcat(fileName, time);
	strcat(fileName, ".txt");
	std::ofstream out(fileName);
	if (!out.is_open())
	{
		std::cout << "Error: can not open txt file\n";
		return false;
	}
	for (unsigned i = 0; i < number; i++)
	{
		double blockCoins = getCoinsOfBlock(blocks[i]);
		out << "Block-Coins: " << blockCoins << " Block-Serial-Number: " << blocks[i].id << '\n'; //I implemented the function "generateBlockId" so that it matches the serial number of the block being created next
	}
	out.close();
	unsortBlocks();
	return true;
}

void addBlocks(const TransactionBlock* blocksToAdd, const unsigned size)
{
	for (unsigned i = 0; i < size; i++)
	{
		blocks[numberOfBlocks++] = blocksToAdd[i];
	}
}

