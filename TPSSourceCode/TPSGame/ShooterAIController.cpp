// Copyright Felix(Bicheng) Li


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"


void AShooterAIController::BeginPlay() 
{
    Super::BeginPlay();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    APawn* EnemyPawn = GetPawn();

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), EnemyPawn->GetActorLocation());

    }    
}

void AShooterAIController::Tick(float DeltaSeconds) 
{
    Super::Tick(DeltaSeconds);
    
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(GetPawn());
    if (ShooterCharacter != nullptr)
    {
        return ShooterCharacter->IsDead();
    }
    else
    {
        return true;
    }
}
