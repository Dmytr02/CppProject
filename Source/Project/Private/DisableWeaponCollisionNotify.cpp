// Fill out your copyright notice in the Description page of Project Settings.


#include "DisableWeaponCollisionNotify.h"
#include "ABasePlayerCharacter.h"
#include "ABaseCharacter.h"

void UDisableWeaponCollisionNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AABaseCharacter* Player = Cast<AABaseCharacter>(MeshComp->GetOwner()))
	{
		Player->DisableWeaponCollision();
	}
}
