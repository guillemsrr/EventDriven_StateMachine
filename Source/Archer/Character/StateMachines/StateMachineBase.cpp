// Copyright (c) Guillem Serra. All Rights Reserved.

#include "StateMachineBase.h"

#include "Archer/Character/ArcherCharacter.h"

FStateMachineBase::FStateMachineBase(AArcherCharacter* ArcherCharacter)
{
	this->ArcherCharacter = ArcherCharacter;
}

FCharacterMovement* FStateMachineBase::GetCharacterMovement() const
{
	return ArcherCharacter->GetArcherMovement();
}

FCharacterMechanics* FStateMachineBase::GetCharacterMechanics() const
{
	return ArcherCharacter->GetCharacterMechanics();
}

UCharacterAnimations* FStateMachineBase::GetCharacterAnimations() const
{
	return ArcherCharacter->GetArcherAnimations();
}

UWorld* FStateMachineBase::GetWorld() const
{
	return ArcherCharacter->GetWorld();
}

bool FStateMachineBase::IsPlayerUsingGamepad() const
{
	return ArcherCharacter->GetPlayerController()->IsPlayerUsingGamepad;
}
