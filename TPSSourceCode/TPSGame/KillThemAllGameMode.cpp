// Copyright Felix(Bicheng) Li


#include "KillThemAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillThemAllGameMode::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);
    //UE_LOG(LogTemp, Warning, TEXT("A Pawn has been killed!"));

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!AIController->IsDead())
        {
            return;
        }
    }

    EndGame(true);
}

void AKillThemAllGameMode::EndGame(bool bIsPlayerWinner) 
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsPlayer = Controller->IsPlayerController();
        if (bIsPlayerWinner)
        {
            Controller->GameHasEnded(Controller->GetPawn(), bIsPlayer);
        }
        else
        {
            Controller->GameHasEnded(Controller->GetPawn(), !bIsPlayer);
        }
        
    }
}
