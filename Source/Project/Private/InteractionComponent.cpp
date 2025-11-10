#include "InteractionComponent.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/CollisionProfile.h"

UInteractionComponent::UInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::Interact()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    // Box parameters (extent is half-size)
    FVector BoxLocation = Owner->GetActorLocation();
    FVector BoxExtent = FVector(100.0f, 100.0f, 100.0f);

    // Object types to consider for overlap (adjust as needed)
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(Owner);

    DrawDebugBox(GetWorld(), BoxLocation, BoxExtent, FColor::Green, false, 2.0f);

    // Use AActor::StaticClass() as the class filter (cannot pass interface class here)
    TArray<AActor*> OverlappingActors;
    bool bHit = UKismetSystemLibrary::BoxOverlapActors(
        this,                   // WorldContextObject
        BoxLocation,            // Box center
        BoxExtent,              // Box extent (half-size)
        ObjectTypes,            // Object types to overlap
        AActor::StaticClass(),  // Class filter - use AActor and filter by interface below
        ActorsToIgnore,         // Actors to ignore
        OverlappingActors       // Out actors
    );

    if (bHit)
    {
        for (AActor* Actor : OverlappingActors)
        {
            if (!Actor || Actor == Owner) continue;

            if (Actor->Implements<UInteractionInterface>())
            {
                IInteractionInterface::Execute_Interact(Actor, Owner);
            }
        }
    }
}