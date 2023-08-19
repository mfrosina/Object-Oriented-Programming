// kr2_1MI8000006.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable:4996)

#include <iostream>
#include <cstring>

enum DeviceType
{
    UNKNOWN = -1,
    HEAT,
    TV,
    FRIDGE
};

class ElectricDevice
{
protected:
    char* brand;
    char* model;
    char* serialNumber;
    double consumedPower;
    bool isTurnedOn;
    DeviceType type;

    void copy(const ElectricDevice& other)
    {
        this->brand = new char[strlen(other.brand) + 1];
        strcpy(this->brand, other.brand);
        this->model = new char[strlen(other.model) + 1];
        strcpy(this->model, other.model);
        this->serialNumber = new char[strlen(other.serialNumber) + 1];
        strcpy(this->serialNumber, other.serialNumber);
        this->consumedPower = other.consumedPower;
        this->type = other.type;
    }
    void destroy()
    {
        delete[] this->brand;
        delete[] this->model;
        delete[] this->serialNumber;
        this->consumedPower = 1;
        this->isTurnedOn = false;
        this->type = DeviceType::UNKNOWN;
    }
public:
    ElectricDevice()
    {
        this->brand = new(std::nothrow) char[2];
        strcpy(this->brand, "\0");
        this->model = new(std::nothrow) char[2];
        strcpy(this->model, "\0");
        this->serialNumber = new(std::nothrow) char[2];
        strcpy(this->serialNumber, "\0");
        this->isTurnedOn = false;
        this->consumedPower = 1;
        this->type = DeviceType::UNKNOWN;
    }
    ElectricDevice(const char* brand, const char* model, const char* serialNumber, const double& power, const DeviceType& type)
    {
        if (brand == nullptr || model == nullptr || serialNumber == nullptr || power < 0)
        {
            throw std::invalid_argument("Invalid arguments");
        }
        this->brand = new(std::nothrow) char[strlen(brand) + 1];
        strcpy(this->brand, brand);
        this->model = new(std::nothrow) char[strlen(model) + 1];
        strcpy(this->model, model);
        this->serialNumber = new(std::nothrow) char[strlen(serialNumber) + 1];
        strcpy(this->serialNumber, serialNumber);
        this->isTurnedOn = false;
        this->consumedPower = power;
        this->type = type;
    }
    ElectricDevice(const ElectricDevice& other)
    {
        copy(other);
    }
    ElectricDevice& operator=(const ElectricDevice& other)
    {
        if (this != &other)
        {
            destroy();
            copy(other);

        }
        return *this;
    }
    virtual ~ElectricDevice()
    {
        destroy();
    }
    
    bool turnOn()
    {
        if (!this->isTurnedOn)
        {
            this->isTurnedOn = true;
            this->setPower();
            return true;
        }
        return false;
    }
    bool turnOff()
    {
        if (this->isTurnedOn)
        {
            this->isTurnedOn = false;
            return true;
        }
        return false;
    }
    void print() const
    {
        std::cout << this->model << " " << this->brand << " " << this->consumedPower << std::endl;
    }
    const DeviceType getType() const
    {
        return this->type;
    }
    const bool isTurnedON() const
    {
        return this->isTurnedOn;
    }
    const char* getSerialNumber() const
    {
        return this->serialNumber;
    }
    const double getConsumedPower() const
    {
        return this->consumedPower;
    }

    virtual ElectricDevice* clone() const = 0;
    virtual bool setPower() = 0;
};

class HeatDevice : public ElectricDevice
{
private:
    double fullPower;

    void copy(const HeatDevice& other)
    {
        this->fullPower = other.fullPower;
    }
    
public:
    HeatDevice(const char* brand, const char* model, const char* serialNumber, const double& power) : ElectricDevice(brand, model, serialNumber, 0,DeviceType::HEAT)
    {
        if (power < 0)
        {
            throw std::invalid_argument("Invalid argument");
        }
        this->fullPower = power;
    }
    HeatDevice(const HeatDevice& other) : ElectricDevice(other)
    {
        copy(other);
    }
    HeatDevice& operator=(const HeatDevice& other) 
    {
        if (this != &other)
        {
            ElectricDevice::operator=(other);
            this->fullPower = 1;
            copy(other);
        }
        return *this;
    }
    ~HeatDevice(){}

    bool setPower() override
    {
        if (this->isTurnedOn)
        {
            this->consumedPower = fullPower;
            return true;
        }
        return false;
    }

    HeatDevice* clone() const override
    {
        return new HeatDevice(*this);
    }

};

class TV : public ElectricDevice
{
private:
    double brightness;
    double fullPower;

    void copy(const TV& other)
    {
        this->brightness = other.brightness;
        this->fullPower = other.fullPower;
    }

public:
    TV(const char* brand, const char* model, const char* serialNumber, const double& power, const double& brightness) : ElectricDevice(brand, model, serialNumber, 0.05, DeviceType::TV)
    {
        if (brightness < 0 || power < 0)
        {
            throw std::invalid_argument("Invalid argument");
        }
        this->brightness = brightness;
        this->fullPower = power;
    }
    TV(const TV& other) : ElectricDevice(other)
    {
        copy(other);
    }
    TV& operator=(const TV& other)
    {
        if (this != &other)
        {
            ElectricDevice::operator=(other);
            this->brightness = 1;
            copy(other);
        }
        return *this;
    }
    ~TV(){}

    bool setPower() override
    {
        if (this->isTurnedOn)
        {
            this->consumedPower = (this->brightness / 100) * fullPower;
            return true;
        }
        return false;
    }

    TV* clone() const override
    {
        return new TV(*this);
    }

};

class Fridge : public ElectricDevice
{
private:
    unsigned compressors;

    void copy(const Fridge& other)
    {
        this->compressors = other.compressors;
    }

public:
    Fridge(const char* brand, const char* model, const char* serialNumber, const double& power, const unsigned& compressors) : ElectricDevice(brand, model, serialNumber, 0, DeviceType::FRIDGE)
    {
        if (compressors <= 0 || power <= 0)
        {
            throw std::invalid_argument("Invalid argument");
        }
        this->compressors = compressors;
        this->consumedPower = compressors * power;
    }
    Fridge(const Fridge& other) : ElectricDevice(other)
    {
        copy(other);
    }
    Fridge& operator=(const Fridge& other)
    {
        if (this != &other)
        {
            ElectricDevice::operator=(other);
            this->compressors = 0;
            copy(other);
        }
        return *this;
    }
    ~Fridge() {}


    Fridge* clone() const override
    {
        return new Fridge(*this);
    }
    bool setPower() override
    {
        this->consumedPower = compressors * this->consumedPower;
    }
};


class Room
{
private:
    char name[30];
    unsigned contacts;
    double maxPower;
    DeviceType invalidDevices[3];
    unsigned invalidSize;
    ElectricDevice** devices;
    unsigned devicesSize;
    unsigned capacity;
    bool canAdd;

    //void resize()
    //{
    //    this->capacity *= 2;
    //    ElectricDevice** temp = new ElectricDevice * [this->capacity];
    //    for (unsigned i = 0; i < this->devicesSize; i++)
    //    {
    //        temp[i] = devices[i]->clone();
    //    }
    //    devices = temp;
    //    for (unsigned i = 0; i < this->devicesSize; i++)
    //    {
    //        delete temp[i];
    //    }
    //    delete[] temp;
    //}
    void copy(const Room& other)
    {
        strcpy(this->name, other.name);
        this->contacts = contacts;
        this->maxPower = maxPower;
        for (unsigned i = 0; i < invalidSize; i++)
        {
            this->invalidDevices[i] = other.invalidDevices[i];
        }
        this->invalidSize = invalidSize;
        this->capacity = other.capacity;
        this->devicesSize = other.devicesSize;
        this->devices = new(std::nothrow) ElectricDevice * [this->capacity];
        for (unsigned i = 0; i < this->devicesSize; i++)
        {
            this->devices[i] = other.devices[i]->clone();
        }
        this->canAdd = other.canAdd;
    }
    void destroy()
    {
        strcpy(this->name, "\0");
        this->contacts = 0;
        this->maxPower = 0;
        for (unsigned i = 0; i < invalidSize; i++)
        {
            this->invalidDevices[i] = DeviceType::UNKNOWN;
        }
        this->invalidSize = 0;
        this->capacity = 0;
        for (unsigned i = 0; i < this->devicesSize; i++)
        {
            delete this->devices[i];
        }
        delete[] this->devices;
        this->devicesSize = 0;
        this->canAdd = true;
    }

    bool isInvalidDevice(const DeviceType& type)
    {
        for (unsigned i = 0; i < invalidSize; i++)
        {
            if (this->invalidDevices[i] == type)
            {
                return true;
            }
        }
        return false;
    }
public:
    Room(const char* name, const unsigned& contacts, const double& maxPower, const DeviceType invalid[3], const unsigned& invalidSize)
    {
        if (strlen(name) >= 30 || contacts < 0 || maxPower < 0 || invalidSize > 3)
        {
            throw std::invalid_argument("Invalid argument");
        }
        strcpy(this->name, name);
        this->contacts = contacts;
        this->maxPower = maxPower;
        for (unsigned i = 0; i < invalidSize; i++)
        {
            this->invalidDevices[i] = invalid[i];
        }
        this->invalidSize = invalidSize;

        this->capacity = 8;
        this->devicesSize = 0;
        this->devices = new(std::nothrow) ElectricDevice * [capacity];
        this->canAdd = true;
    }
    Room(const Room& other)
    {
        copy(other);
    }
    Room& operator=(const Room& other)
    {
        if (this != &other)
        {
            destroy();
            copy(other);
        }
        return *this;
    }
    ~Room()
    {
        destroy();
    }

    void removeInvalid(const DeviceType& type)
    {
        for (unsigned i = 0; i < invalidSize; i++)
        {
            if (this->invalidDevices[i] == type)
            {
                this->invalidDevices[i] = DeviceType::UNKNOWN;
                invalidSize--;
                break;
            }
        }
    }
    void addInvalid(const DeviceType& type)
    {
        if (invalidSize >= 3)
        {
            std::cout << "All devices are invalid for this type of room. Can not add invalid!\n";
            return;
        }
        invalidDevices[invalidSize++] = type;
    }

    Room& operator+=(const ElectricDevice* toAdd)
    {
        if (this->devicesSize == contacts || isInvalidDevice(toAdd->getType()) || toAdd->isTurnedON() || !this->canAdd)
        {
            std::cout << "Can not add device!\n";
            return *this;
        }
        this->devices[this->devicesSize++] = toAdd->clone();
        return *this;
    }
    Room& operator+(const ElectricDevice* toAdd)
    {
        if (devicesSize == contacts || isInvalidDevice(toAdd->getType()) || toAdd->isTurnedON() || !this->canAdd)
        {
            std::cout << "Can not add device!\n";
            return *this;
        }
        Room room = *this;
        room += (toAdd);
        return room;
    }

    Room& operator-=(const ElectricDevice* toRemove)
    {
        for (unsigned i = 0; i < devicesSize; i++)
        {
            if (strcmp(this->devices[i]->getSerialNumber(), toRemove->getSerialNumber()) == 0)
            {
                for (unsigned j = i + 1; j < devicesSize; j++)
                {
                    this->devices[i] = this->devices[j];
                }
                devicesSize--;
            }
        }
        return *this;
    }
    Room& operator-(const ElectricDevice* toRemove)
    {
        Room room = *this;
        room -= (toRemove);
        return room;
    }

    ElectricDevice* operator[](const char* serialNum) const
    {
        for (unsigned i = 0; i < devicesSize; i++)
        {
            if (strcmp(this->devices[i]->getSerialNumber(), serialNum) == 0)
            {
                return this->devices[i];
            }
        }
        std::cout << "Device with given serial number is not in the room.\n";
        return nullptr;
    }

    double getConsumedPowerOnTurnedOnDevices() const
    {
        double consumed = 0;
        for (unsigned i = 0; i < devicesSize; i++)
        {
            if (this->devices[i]->isTurnedON())
            {
                consumed += this->devices[i]->getConsumedPower();
            }
        }
        return consumed;
    }

    bool turnOnDevice(const ElectricDevice* toTurnOn)
    {
        double consumed = getConsumedPowerOnTurnedOnDevices();
        for (unsigned i = 0; i < devicesSize; i++)
        {
            if (strcmp(this->devices[i]->getSerialNumber(), toTurnOn->getSerialNumber()) == 0)
            {
                if (consumed + toTurnOn->getConsumedPower() >= maxPower
                    || this->devices[i]->isTurnedON())
                {
                    std::cout << "Can not turn on the device. Turn off other device, to turn on this one!\n";
                    return false;
                }
                this->devices[i]->turnOn();
                return true;
            }
        }
        if (consumed > maxPower)
        {
            for (unsigned i = 0; i < devicesSize; i++)
            {
                this->operator-=(this->devices[i]);
            }
            this->canAdd = false;
        }
        return false;
    }
    bool turnOffDevice(const ElectricDevice* toTurnOff)
    {
        for (unsigned i = 0; i < devicesSize; i++)
        {
            if (strcmp(this->devices[i]->getSerialNumber(), toTurnOff->getSerialNumber()) == 0)
            {
                if (this->devices[i]->isTurnedON())
                {
                    this->devices[i]->turnOff();
                    return true;
                }
            }
        }
        return false;
    }

    void roomInfo() const
    {
        std::cout << this->name << "\n";
        std::cout << "Has turned on devices:\n ";
        for (unsigned i = 0; i < devicesSize; i++)
        {
            if (this->devices[i]->isTurnedON())
            {
                this->devices[i]->print();
            }
        }
        std::cout << "Has turned off devices:\n ";
        for (unsigned i = 0; i < devicesSize; i++)
        {
            if (!this->devices[i]->isTurnedON())
            {
                this->devices[i]->print();
            }
        }
    }
};
int main()
{
    ElectricDevice* dev = new HeatDevice("Peshy", "Mega Heat", "P MH140-7765d", 2000);
    DeviceType invalidTypes[2];
    invalidTypes[0] = DeviceType::TV;
    invalidTypes[1] = DeviceType::FRIDGE;

    Room* room = new Room("Bedroom", 30, 2.1, invalidTypes, 2);
    room->operator+=(dev);
    room->turnOnDevice(dev);
    room->roomInfo();

    Room* guestroom(room);
    guestroom->removeInvalid(DeviceType::TV);

    //ElectricDevice* tv = new TV("HP", "hppp", "H140-776", 0.250, 100); //expected a type specifier???
    return 0;
}

