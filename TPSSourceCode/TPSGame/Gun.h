// Copyright Felix(Bicheng) Li

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class TPSGAME_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTriggerMethod();
	void Reload();
	void ReloadWait();
	void SwitchWeapon();
	FName GetGunName() const;
	int32 GetGunAmmo() const;
	int32 GetMaxAmmo() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxAmmo = 10;

	UPROPERTY(EditAnywhere)
	float ReloadTime = 1.0f;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitImpact;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY(EditAnywhere)
	FName GunName;


	bool GunTrace(FHitResult& HitResult, FVector& ShotDirection);
	AController* GetOwnerController() const;

	int32 Ammo;
	FTimerHandle ReloadTimerHandle;
	bool bCanShoot = true;
};
