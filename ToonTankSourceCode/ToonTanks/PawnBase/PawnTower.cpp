// Copyright Felix(Bicheng) Li


#include "PawnTower.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

APawnTower::APawnTower()
{

}
// Called when the game starts or when spawned
void APawnTower::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(FireRateTimeHandle, this, &APawnTower::CheckFireCondition, FireRate, true, false);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!PlayerPawn || DistanceToPlayer() > FireRange)
    {
        return;
    }

    RotateTurrent(PlayerPawn->GetActorLocation());
}

void APawnTower::CheckFireCondition()
{
    if (!PlayerPawn || !PlayerPawn->GetPlayerAlive())
    {
        return;
    }
    
    if (DistanceToPlayer() <= FireRange)
    {
        //Fire!
        Fire();
    }
    
}

float APawnTower::DistanceToPlayer()
{
    if (!PlayerPawn)
    {
        return 0.f;
    }
    float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
    return Distance;
}

void APawnTower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}