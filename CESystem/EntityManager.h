#pragma once

#include <boost/serialization/access.hpp>
#include <vector>
#include <memory>

#include "Entity.h"
#include "ComponentPosition.h"
#include "ComponentRender.h"
#include "ComponentEvent.h"
#include "ComponentPlayerInput.h"
#include "ComponentMovement.h"
#include "componentMouseInput.h"
#include "ComponentHealth.h"
#include "componentDamage.h"
#include "ComponentCollision.h"
#include "ComponentAABB.h"
#include "ComponentText.h"

class EntityManager
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar.register_type(static_cast<ComponentPosition*>(NULL));
		ar.register_type(static_cast<ComponentRender*>(NULL));
		ar.register_type(static_cast<ComponentEvent*>(NULL));
		ar.register_type(static_cast<ComponentPlayerInput*>(NULL));
		ar.register_type(static_cast<ComponentMovement*>(NULL));
		ar.register_type(static_cast<componentMouseInput*>(NULL));
		ar.register_type(static_cast<ComponentHealth*>(NULL));
		ar.register_type(static_cast<componentDamage*>(NULL));
		ar.register_type(static_cast<ComponentCollision*>(NULL));
		ar.register_type(static_cast<ComponentAABB*>(NULL));
		ar.register_type(static_cast<ComponentText*>(NULL));

		ar.register_type(static_cast<MoveBlock*>(NULL));
		ar.register_type(static_cast<DoDamage*>(NULL));
//		ar.register_type(static_cast<Click*>(NULL));
		ar.register_type(static_cast<Save*>(NULL));

		ar & _entityList;
	}
public:
	EntityManager();
	~EntityManager();
	std::vector<std::unique_ptr<Entity>> _entityList;

	void add(std::unique_ptr<Entity>& Ent, bool save = true);
	void deleteEntities();
};




