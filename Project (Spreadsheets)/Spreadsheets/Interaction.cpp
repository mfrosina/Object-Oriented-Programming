#include "Interaction.h"

Cell* Interaction::parseParameter(const unsigned& row, const unsigned& col, std::string str)
{
    if (str[0] == '+' || str[0] == '-' || Helpers::isDigit(str[0]))
    {
        if (str.find('.') != std::string::npos)
        {
            double fractNumber = std::stod(str);
            return new (std::nothrow) Fractional(fractNumber, row, col);
        }
        else
        {
            int intNumber = std::stoi(str);
            return new (std::nothrow) Integer(intNumber, row, col);
        }
    }
    if (Helpers::isCharacter(str[0]) || str[0] == '\"')
    {
        if (Helpers::hasOnlyDigits(str))
        {
            unsigned occurences = std::count(str.begin(), str.end(), '.');
            if (occurences <= 1)
            {
                std::string save = str;
                str.erase(remove(str.begin(), str.end(), '"'));
                double number = std::stod(str);
                return new String(number, row, col, save);
            }
        }
        return new (std::nothrow) String(0, row, col, str);
    }
    if (str[0] == '=')
    {
        str.erase(0,1);
        return new (std::nothrow) Formula(0, row, col, str);
    }
    else
    {
        throw std::invalid_argument("Invalid data");
    }
      
}

void Interaction::open()
{
    if (this->spreadsheet != nullptr)
    {
        std::cout << "A file is already opened!\nClose it to open another one. \n";
        return;
    }
    std::string fileName;
    std::cout << "Enter the name of the file you want to open:\n";
    std::cin >> fileName;
    std::cin.ignore();
    if (fileName.find('\\') != std::string::npos)
    {
        fileName = Helpers::parseFileName(fileName);
    }
    this->fileName = fileName;
    spreadsheet = new Spreadsheet(fileName);
    this->spreadsheet = (this->spreadsheet)->parse();
    if (this->spreadsheet == nullptr)
    {
        std::cout << "Can not open file! No loaded table. Please, try again...\n";
        return;
    }
    std::cout << "Successfully opened " << fileName << "!\n";
}
void Interaction::print()
{
    if (this->spreadsheet == nullptr)
    {
        std::cout << "No loaded table!\n";
        return;
    }
    (this->spreadsheet)->printSpreadsheet();
}
void Interaction::edit()
{
    if (this->spreadsheet == nullptr)
    {
        std::cout << "No loaded table!\n";
        return;
    }
    unsigned row, col;
    std::string value;
    std::cout << "Please, enter the number of the row and column of the cell you want to edit:\n";
    std::cin >> row >> col;
    std::cin.ignore();
    std::cout << "Please, enter the new value for the cell:\n";
    std::getline(std::cin, value);
    try
    {
        Cell* toEdit = parseParameter(row, col, value);
        try
        {
            if ((this->spreadsheet)->editCell(row, col, toEdit))
            {
                std::cout << "Successfully edited cell!\n";
            }
            else
            {
                std::cout << "Desired cell not edited! Please, try again...\n";
            }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    catch (...)
    {
        std::cout << "Invalid entered data! Please, try again...\n";
        return;
    }
    
}
void Interaction::save()
{
    if (this->spreadsheet == nullptr)
    {
        std::cout << "You need to open a file first and load a table, in order to use this command!\n";
        return;
    }
    if ((this->spreadsheet)->saveToFile(this->fileName))
    {
        std::cout << "Successfully saved table in file named " << this->fileName << "!\n";
        return;
    }
    std::cout << "Can not save table in file! Please, try again...\n";
    
}
void Interaction::saveAs()
{
    if (this->spreadsheet == nullptr)
    {
        std::cout << "You need to open a file first and load a table, in order to use this command!\n";
        return;
    }
    std::string filePath;
    std::cout << "Please, specify the file path:\n";
    std::getline(std::cin, filePath);

    if ((this->spreadsheet)->saveToFile(filePath))
    {
        std::cout << "Successfully saved table in file named " << filePath << "!\n";
        return;
    }
    std::cout << "Can not save table in file! Please, try again...\n";
}
void Interaction::close()
{
    if (this->spreadsheet == nullptr) {
        std::cout << "You need to open a file first, in order to close it!\n";
        return;
    }

    this->fileName = "";
    delete this->spreadsheet;
    this->spreadsheet = nullptr;
  
    std::cout << "File has been closed and table in memory is cleared!\n";
}
void Interaction::exit()
{
    if (this->spreadsheet != nullptr) {
        delete this->spreadsheet;
        this->spreadsheet = nullptr;
    }

    this->active = false;
    this->fileName = "";

}
void Interaction::help()
{
    std::cout << "open ...\n\topens a file from which a table is loaded\n";
    std::cout << "\texample: 'open input.txt'\n";
    std::cout << "close\n\tcloses opened file\n";
    std::cout << "print\n\tprints table's content\n";
    std::cout << "save\n\tsaves current table to the input file\n";
    std::cout << "saveas ...\n\tsaves current table to the specific file\n";
    std::cout << "\texample: 'saveas temp.txt'\n"; // TRY THIS
    std::cout << "edit ... ...\n\tsets new value to specified cell\n";
    std::cout << "\texample: 'edit <row> <col> <value>' (indices start from 1)\n";
    std::cout << "help\n\tdisplays available commands\n";
    std::cout << "exit\n\texits the program\n";
}

Interaction::Interaction()
{
	this->fileName = "";
	this->spreadsheet = nullptr;
	this->active = true;
}
Interaction::~Interaction()
{
    exit();
}

bool Interaction::isActive() const
{
	return this->active;
}

void Interaction::executeCommand()
{
    std::string command;
    getline(std::cin, command);

    if (command == "open") {
        this->open();
    }
    else if (command == "close") {
        this->close();
    }
    else if (command == "save") {
        this->save();
    }
    else if (command == "saveas") {
        this->saveAs();
    }
    else if (command == "help") {
        this->help();
    }
    else if (command == "exit") {
        this->exit();
        std::cout << "Exiting program...\n";
    }
    else if (command == "print") {
        this->print();
    }
    else if (command == "edit") {
        this->edit();
    }
    else {
        std::cout << "Invalid command! Type 'help' to view available commands.\n";
    }
}