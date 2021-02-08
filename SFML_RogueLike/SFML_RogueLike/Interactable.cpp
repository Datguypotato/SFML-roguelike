#include "Interactable.h"

Interactable::Interactable(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
	:	Ground(texture, size, position),
		InTrigger(false),
		lastTimeIn(false)
{

}

Interactable::~Interactable()
{
}

void Interactable::CheckTrigger(Collider pColl)
{
	InTrigger = GetCollider().CheckTrigger(pColl);

	if (InTrigger)
		OnStay();

	if (InTrigger == true && lastTimeIn == false)
		OnEnter();

	if (InTrigger == false && lastTimeIn == true)
		OnExit();

	lastTimeIn = InTrigger;
}


