// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

UENUM()
enum class ECharacterLocomotionState : uint8
{
	Normal = 0,
	Running,
	Jumping,
	Climbing,
	Dashing
};

UENUM()
enum class ECharacterAttackState : uint8
{
	NotAiming,
	Aiming,
	Drawback,
	Holding,
	Release
};

UENUM()
enum class EOrientationType : uint8
{
	Movement,
	AimDirection
};

