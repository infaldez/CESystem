#pragma once

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <string>
#include <fstream>
#include "EntityManager.h"

//class EntityManager;

namespace IOmanager
{
	void save(std::string name, EntityManager& em);

	void load(std::string name, EntityManager& em);
}