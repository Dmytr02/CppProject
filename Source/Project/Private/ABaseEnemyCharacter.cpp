// Fill out your copyright notice in the Description page of Project Settings.



#include "ABaseEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AABaseEnemyCharacter::AABaseEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
    PawnSensingComp->SightRadius = 1500.f;      // Радиус зрения
    PawnSensingComp->SetPeripheralVisionAngle(150.f); // Угол обзора
}

void AABaseEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (PawnSensingComp)
    {
        PawnSensingComp->OnSeePawn.AddDynamic(this, &AABaseEnemyCharacter::OnSeePawn);
    }

    if (WeaponClass) // WeaponClass задаём в BP
    {
        CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
        CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
		CurrentWeapon->SubscribeHit();
		CurrentWeapon->ownerCharacter = this;
		DisableWeaponCollision();
    }

    AAIController* AI = Cast<AAIController>(GetController());


    if (AI)
    {
        UBlackboardComponent* BB = AI->GetBlackboardComponent();
        if (BB)
        {
            BB->SetValueAsObject("ChassingTarget", TargetActor);
        }
    }
}

void AABaseEnemyCharacter::OnSeePawn(APawn* Pawn)
{
    UE_LOG(LogTemp, Warning, TEXT("AI %s!, x - %f | y - %f | %f"), *Pawn->GetName(), Pawn->GetActorLocation().X, Pawn->GetActorLocation().Y, FVector::Dist(GetActorLocation(), TargetActor->GetActorLocation()))

    float Distance = FVector::Dist(GetActorLocation(), Pawn->GetActorLocation());
    TargetActor->TeleportTo(Pawn->GetActorLocation(), FRotator::ZeroRotator);

	if(Distance < AttackRange && !bIsAttacking)
		CharacterState = EEnamyState::Attacking;
    /*else if(FVector::Dist(GetActorLocation(), TargetActor->GetActorLocation()) < 50){
		CharacterState = EEnamyState::Patrolling;
    }*/
    else {
        CharacterState = EEnamyState::Chasing;
    }

    AAIController* AI = Cast<AAIController>(GetController());

    if (AI)
    {
        UBlackboardComponent* BB = AI->GetBlackboardComponent();
        if (BB)
        {
            BB->SetValueAsEnum("EnemyState", (uint8)CharacterState);
            BB->SetValueAsObject("CombatTarget", Pawn);
        }
    }
    //if (!Pawn) return;

    //UE_LOG(LogTemp, Warning, TEXT("AI увидел %s!"), *Pawn->GetName());

    //AAIController* AICon = Cast<AAIController>(GetController());
   
    //float Distance = FVector::Dist(GetActorLocation(), Pawn->GetActorLocation());

    //if (Distance > AttackRange && !bIsAttacking)
    //{
    //    // Двигаться к игроку
    //    AICon->MoveToActor(Pawn, 5.0f); // 5.0f = дистанция 
    //}
    //else
    //{
    //    // Остановить движение
    //    AICon->StopMovement();

    //    // Запустить анимацию атаки
    //    if (AttackMontage && !bIsAttacking)
    //    {
    //        PlayAnimMontage(AttackMontage);
    //        bIsAttacking = true;
    //    }
    //}

}

void AABaseEnemyCharacter::TryAttack()
{
    if (AttackMontage && !bIsAttacking)
    {
        PlayAnimMontage(AttackMontage);
        bIsAttacking = true;
    }
}

void AABaseEnemyCharacter::Death_Implementation()
{
    if (CurrentWeapon)
        CurrentWeapon->Destroy();
	Destroy();
}

void AABaseEnemyCharacter::EnableWeaponCollision()
{
    if (CurrentWeapon)
        CurrentWeapon->EnableCollision();
	bIsAttacking = true;
}

void AABaseEnemyCharacter::DisableWeaponCollision()
{
    if (CurrentWeapon)
        CurrentWeapon->DisableCollision();
    bIsAttacking = false;

	CharacterState = EEnamyState::Chasing;

    AAIController* AI = Cast<AAIController>(GetController());

    if (AI)
    {
        UBlackboardComponent* BB = AI->GetBlackboardComponent();
        if (BB)
        {
            BB->SetValueAsEnum("EnemyState", (uint8)CharacterState);
        }
    }
}

void AABaseEnemyCharacter::GetHit_Implementation(int value)
{
    Super::GetHit_Implementation(value);
    if (GetHitMontage)
    {
        PlayAnimMontage(GetHitMontage);
        CurrentWeapon->DisableCollision();
    }
    if (MySound) {
        UGameplayStatics::PlaySoundAtLocation(this, MySound, GetActorLocation());
    }
}