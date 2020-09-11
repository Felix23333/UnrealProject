// Copyright Felix(Bicheng) Li


#include "BTService_UpdatePlayerLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"


UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation() 
{
    NodeName = "Update Player Location if Seen";
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (OwnerComp.GetAIOwner() == nullptr) return;

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(PlayerPawn == nullptr) 
    {
        UE_LOG(LogTemp, Error, TEXT("Didn't detected playerpawn!"));
        return;
    }

    bool bCanSee = OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn);
    if(bCanSee)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}
