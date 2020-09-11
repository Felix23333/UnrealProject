// Copyright Felix(Bicheng) Li

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class TPSGAME_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetCurrentHealthPercent() const;

	UFUNCTION(BlueprintPure)
	FName GetCurrentGunName() const;

	UFUNCTION(BlueprintPure)
	int32 GetCurrentAmmo() const;

	UFUNCTION(BlueprintPure)
	int32 GetMaxAmmo() const;


	void Shoot();
	void Reload();

private:
	void MoveFoward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void LookUpController(float AxisValue);
	void LookRightController(float AxisValue);
	void ChangeWeapon();

	UPROPERTY(EditAnywhere)
	float RotationRate = 20;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> SideGunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY()
	AGun* SideGun;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 50.f;
	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;
	

	bool bMainGun = true;
	FTimerHandle ReloadTimerHandle;

	UPROPERTY(EditAnywhere)
	float MainReloadTime = 1.f;

	UPROPERTY(EditAnywhere)
	float SideReloadTime = 2.f;
};

