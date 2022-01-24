#pragma once
#include "ArchTrace.h"

class AArcherCharacter;

class FCharacterMechanics
{
public:
	explicit FCharacterMechanics(UArchTrace* ArchTrace);
	
	void StartAim();
	void StopAim();

private:
	UArchTrace* ArchTrace;
};
