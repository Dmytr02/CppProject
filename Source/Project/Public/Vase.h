// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Combat.h"
#include "Vase.generated.h"

UCLASS()
class PROJECT_API AVase : public AActor, public ICombat
{
	GENERATED_BODY()
	

protected:
	virtual void GetHit_Implementation(int value) override;

};
