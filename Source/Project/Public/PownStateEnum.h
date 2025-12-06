// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PownStateEnum.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle,
	Attacking,
	GettingHit,
	OutOfStamina,
	Dead
};

UENUM(BlueprintType)
enum class EEnamyState : uint8
{
	Patrolling,
	Chasing,
	Attacking,
	GettingHit,
	Dead
};

