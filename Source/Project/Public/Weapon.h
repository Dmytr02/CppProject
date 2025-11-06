#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ABaseCharacter.h"
#include "Weapon.generated.h"

UCLASS()
class PROJECT_API AWeapon : public AItem
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UBoxComponent* WeaponCollision;

	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other,
		UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation,
		FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	class AABasePlayerCharacter* ownerCharacter;
	AWeapon();
	virtual void PickUp_Implementation(AActor* Caller) override;
	void EnableCollision();
	void DisableCollision();
};
