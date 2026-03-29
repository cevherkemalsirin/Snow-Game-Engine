#include "Framework/Object.h"
#include "Framework/Core.h"

namespace snw
{
	Object::Object() : m_isPendingDestroy{false}
	{
	}


	void Object::Destroy()
	{
		m_isPendingDestroy = true; 
	}


	Object::~Object()
	{
		LOG("Object Destroyed");
	}

}