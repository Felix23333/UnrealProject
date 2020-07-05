// Copyright Felix(Bicheng) Li


#include "TankGameModeBase.h"
#include "ToonTanks/PawnBase/PawnTank.h"
#include "ToonTanks/PawnBase/PawnTower.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerController/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    TargetNumber = GetTargetNumber();

    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

    HandleGameStart();

}
int32 ATankGameModeBase::GetTargetNumber()
{
    TSubclassOf<APawnTower> ClassToFind;
    ClassToFind = APawnTower::StaticClass();
    TArray<AActor*> TowerActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TowerActors);
    return TowerActors.Num();
}
void ATankGameModeBase::ActorDead(AActor* DeadActor)
{
    if (DeadActor == PlayerTank)
    {
        PlayerTank->PawnDestroy();
        HandleGameOver(false);

        if (PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
        }
        
    }
    else if(APawnTower* DestoryTower = Cast<APawnTower>(DeadActor))
    {
        DestoryTower->PawnDestroy();
        TargetNumber -= 1;
        if(TargetNumber == 0)
        {
            HandleGameOver(true);
        }
    }
    
}
void ATankGameModeBase::HandleGameStart()
{
    GameStart();
    if (PlayerControllerRef)
    {   
        PlayerControllerRef->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);

        GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay + 3.f, false);
        
    }
}
void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    PlayerControllerRef->SetPlayerEnabledState(false);
    PlayerTank->SetActorTickEnabled(false);
    GameOver(PlayerWon);
}


