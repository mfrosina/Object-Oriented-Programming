#include "BlocksDatFile.h"


unsigned BlocksDatFile::findNumberOfSavedBlocks()
{
	std::ifstream binFile(FILE_NAME, std::ios::binary);
	if (!binFile.is_open())
	{
		std::cout << "Error: blocks.dat file can not be opened! There are not existing blocks of transactions yet.\n";
		return 0;
	}
	binFile.seekg(0, std::ios::end); //position on the end
	unsigned blocksNumber = binFile.tellg() / sizeof(TransactionBlock);
	binFile.close();
	return blocksNumber;
}
TransactionBlock* BlocksDatFile::readBlocksFromFile()
{
	std::ifstream binFile(FILE_NAME, std::ios::binary);
	if (!binFile.is_open())
	{
		std::cout << "Error: blocks.dat file can not be opened! There are not existing blocks of transactions yet.\n";
		return{};
	}
	unsigned blocksNumber = findNumberOfSavedBlocks();
	TransactionBlock* readedBlocks = new TransactionBlock[blocksNumber];
	for (unsigned i = 0; i < blocksNumber; i++)
	{
		binFile.read((char*)&readedBlocks[i], sizeof(TransactionBlock));
	}
	binFile.close();
	return readedBlocks;
}

void BlocksDatFile::addBlockToFile(const TransactionBlock& block)
{
	std::ofstream binFile(FILE_NAME, std::ios::binary|std::ios::app);
	if (!binFile.is_open())
	{
		std::cout << "Error: blocks.dat file can not be opened!\n";
		return;
	}
	binFile.write((const char*)&block, sizeof(TransactionBlock));
	binFile.close();
}

void BlocksDatFile::deleteBlock(const unsigned blockId)
{
	std::ifstream in(FILE_NAME, std::ios::binary);
	if (!in.is_open())
	{
		std::cout << "Error: blocks.dat file can not be opened!\n";
		return;
	}
	unsigned numberOfSavedBlocks = findNumberOfSavedBlocks();
	TransactionBlock* blocks = new TransactionBlock[numberOfSavedBlocks];
	for (unsigned i = 0; i < numberOfSavedBlocks; i++)
	{
		in.read((char*)&blocks[i], sizeof(TransactionBlock));
	}
	in.close();
	std::ofstream out(FILE_NAME, std::ios::binary);
	if (!out.is_open())
	{
		std::cout << "Error: blocks.dat file can not be opened!\n";
		return;
	}
	out.seekp(0);
	for (unsigned i = 0; i < numberOfSavedBlocks; i++)
	{
		if (blocks[i].id != blockId)
		{
			out.write((const char*)&blocks[i], sizeof(TransactionBlock));
		}
	}
	out.close();
	delete[]blocks;
}

