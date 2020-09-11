// Copyright Felix(Bicheng) Li

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;
	bool IsDead() const;
protected:
	virtual void BeginPlay() override;	
private:
	//UPROPERTY(EditAnywhere)
	//float RadiusToPlayer = 200;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

};

