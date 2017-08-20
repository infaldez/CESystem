#include "ComponentInventory.h"


ComponentInventory::ComponentInventory()
	: Component(components::COMPONENT_INVENTORY)
{
}


ComponentInventory::~ComponentInventory()
{
}


void ComponentInventory::addItem(std::string item, int amount)
{
	auto it = _inventory.find(item);
	if (it != _inventory.end())
		_inventory.insert(std::pair<std::string, int>(item, amount));
	else
		it->second += amount;
}

void ComponentInventory::removeItem(std::string item, int amount)
{
	auto it = _inventory.find(item);
	if (it != _inventory.end())
	{
		it->second -= amount;
		if (it->second <= 0)
			_inventory.erase(item);
	}
		
}

int ComponentInventory::getAmount(std::string item)
{
	auto it = _inventory.find(item);
	if (it != _inventory.end())
		return it->second;
	else 
		return 0;
}