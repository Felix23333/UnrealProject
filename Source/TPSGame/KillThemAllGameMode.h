// Copyright Felix(Bicheng) Li

#pragma once

#include "CoreMinimal.h"
#include "TPSGameGameModeBase.h"
#include "KillThemAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API AKillThemAllGameMode : public ATPSGameGameModeBase
{
	GENERATED_BODY()
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
	
};
