// Copyright Felix(Bicheng) Li


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot() 
{
    NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;

    AShooterCharacter* EnemyCharacter = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if(EnemyCharacter == nullptr) return EBTNodeResult::Failed;

    EnemyCharacter->Shoot();

    return EBTNodeResult::Succeeded;
}


