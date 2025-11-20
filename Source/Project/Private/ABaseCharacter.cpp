#include "ABaseCharacter.h"

AABaseCharacter::AABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}


bool AABaseCharacter::CanPayStaminaCost(float Cost)
{	
	return Stamina>Cost;
}

void AABaseCharacter::PayStamina(float Cost)
{
	Stamina = FMath::Clamp(Stamina - Cost, 0, MaxStamina);
	OnStaminaChanged.Broadcast(Stamina);
}

void AABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PayStamina(-StaminaRegen*DeltaTime);
}

void AABaseCharacter::GetHit_Implementation(int value)
{
	Health -= value;
	OnHealseChanged.Broadcast(Health);
	if (Health > MaxHealth) {
		Health = MaxHealth;
	}
	if (Health <= 0)
	{
		CharacterState = ECharacterState::Dead;
		Execute_Death(this);
	}
}

void AABaseCharacter::EnableWeaponCollision()
{
}

void AABaseCharacter::DisableWeaponCollision()
{
}
