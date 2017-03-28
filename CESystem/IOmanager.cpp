#include "IOmanager.h"


namespace IOmanager
{
	void IOmanager::save(std::string name, EntityManager& em)
	{
		std::ofstream ofs(name, std::fstream::binary);
		boost::archive::binary_oarchive oa(ofs);
		oa << em;
	}

	void IOmanager::load(std::string name, EntityManager& em)
	{
		// Load entityList from file
		std::ifstream ifs(name, std::fstream::binary);
		boost::archive::binary_iarchive ia(ifs);
		ia >> em;

		std::cout << em._entityList.size() << std::endl;

		for (auto& ent : em._entityList)
		{
			if (!ent->getSave())
			{
				ent->componentKey[components::DELETE] = true;
			}
				
		}
		em.deleteEntities();

		std::cout << em._entityList.size() << std::endl;
	}
}

