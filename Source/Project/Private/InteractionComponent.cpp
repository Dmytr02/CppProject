#include "InteractionComponent.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/CollisionProfile.h"
#include <Kismet/GameplayStatics.h>

UInteractionComponent::UInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::Interact()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    FVector CameraLocation;
    FRotator CameraRotation;
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerViewPoint(CameraLocation, CameraRotation);

    FVector BoxLocation = Owner->GetActorLocation();

    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(Owner);

   TArray<FHitResult> HitResults;

    UKismetSystemLibrary::SphereTraceMulti(
        this,
        BoxLocation,
        BoxLocation + CameraRotation.Vector() * InteractionDistance,
        50.f,
        UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility),
        false,
        ActorsToIgnore,
        EDrawDebugTrace::ForDuration,
        HitResults,
        true,
        FLinearColor::Red,
        FLinearColor::Green,
        2.f
    );

#pragma region DrowDebog
        DrawDebugLine(
        GetWorld(),
        BoxLocation,
        BoxLocation + CameraRotation.Vector() * InteractionDistance,
        FColor::Blue,
        false,
        2.f,
        0,
        1.f
    );

    DrawDebugSphere(
        GetWorld(),
        BoxLocation,
        50.f,
        12,
        FColor::Green,
        false,
        2.f
    );

    DrawDebugSphere(
        GetWorld(),
        BoxLocation + CameraRotation.Vector() * InteractionDistance,
        50.f,
        12,
        FColor::Red,
        false,
        2.f
    );
#pragma endregion

    if (HitResults.Num() > 0)
    {
        for (FHitResult& HitResult : HitResults)
        {
			AActor* Actor = HitResult.GetActor();

            if (Actor && Actor->Implements<UInteractionInterface>())
            {
                IInteractionInterface::Execute_Interact(Actor, Owner);
            }
        }
    }
}