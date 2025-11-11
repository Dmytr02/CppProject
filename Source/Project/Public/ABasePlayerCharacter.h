#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "ABaseCharacter.h"
#include "InputActionValue.h"
#include "InteractionComponent.h"
#include "ABasePlayerCharacter.generated.h"

UCLASS()
class PROJECT_API AABasePlayerCharacter : public AABaseCharacter
{
	GENERATED_BODY()

public:
	AABasePlayerCharacter();

	UFUNCTION(BlueprintCallable)
	
	void EquipWeapon(AWeapon* Weapon);

	virtual void EnableWeaponCollision() override;

	virtual void DisableWeaponCollision() override;

	void StopAnim();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	AWeapon* CurrentWeapon;

protected:
	bool bIsAttacking = false;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* AttackAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	class UInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	UAnimMontage* AttackMontage;

	
};