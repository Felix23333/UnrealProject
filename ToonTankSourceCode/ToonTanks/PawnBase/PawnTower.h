// Copyright Felix(Bicheng) Li

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTower.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTower : public APawnBase
{
	GENERATED_BODY()
	
public:
	APawnTower();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attack", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.f;
	FTimerHandle FireRateTimeHandle;

	APawnTank* PlayerPawn;

	void CheckFireCondition();

	float DistanceToPlayer();


protected:
	virtual void HandleDestruction() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
