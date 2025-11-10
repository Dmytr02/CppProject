#include "Weapon.h"
#include "ABasePlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Chaos/ChaosGameplayEventDispatcher.h"
//#include "BreakableVase.h"  

void AWeapon::PickUp_Implementation(AActor* Caller)
{
    if (!Caller) return;

    AABasePlayerCharacter* Player = Cast<AABasePlayerCharacter>(Caller);
    if (Player)
    {
        Player->EquipWeapon(this);
    }

	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapStart);
}

AWeapon::AWeapon()
{
    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;

    WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
    WeaponCollision->SetupAttachment(WeaponMesh);
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    WeaponCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    WeaponCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AWeapon::EnableCollision()
{
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    WeaponCollision->SetHiddenInGame(false);
    WeaponCollision->SetVisibility(true);
}

void AWeapon::DisableCollision()
{
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    WeaponCollision->SetHiddenInGame(true);
    WeaponCollision->SetVisibility(false);
}

void AWeapon::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other,
    UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation,
    FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s"), *Other->GetName());

	ownerCharacter->StopAnim();
}

void AWeapon::OnOverlapStart(UPrimitiveComponent* OverLappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped actor: %s | %s"), *OtherActor->GetName(), *ownerCharacter->GetName());
	if (ownerCharacter && ownerCharacter == OtherActor) return;
    if (OtherActor->Implements<UCombat>())
    {
		ICombat::Execute_GetHit(OtherActor, 50);
    }

    /*UGeometryCollectionComponent* collisionComponent = Cast<UGeometryCollectionComponent>(OtherComp);
    UE_LOG(LogTemp, Warning, TEXT("Overlapped actor: %s | IsNull: %s"), *OtherActor->GetName(), collisionComponent == nullptr ? TEXT("true") : TEXT("false"));

	if (collisionComponent == nullptr) return;

	FVector ImpulseDirection = FVector::RightVector;
    collisionComponent->AddImpulseAtLocation(ImpulseDirection * 1000000.f, OtherActor->GetActorLocation());*/
}
