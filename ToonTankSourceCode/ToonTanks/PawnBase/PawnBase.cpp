// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurrentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turrent Mesh"));
	TurrentMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurrentMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void APawnBase::RotateTurrent(FVector LookAtTarget)
{
	FVector StartLocation = TurrentMesh->GetComponentLocation();
	FRotator TurrentRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, FVector(LookAtTarget.X, LookAtTarget.Y, TurrentMesh->GetComponentLocation().Z));

	TurrentMesh->SetWorldRotation(TurrentRotation);
}
void APawnBase::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Fire!")); //Debug test fire
	if (ProjectileClass)
	{	
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
	
}
void APawnBase::HandleDestruction()
{
	if (DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), FRotator::ZeroRotator);
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if (DeathShake)
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(DeathShake, 1);
	}
}

void APawnBase::PawnDestroy()
{
	HandleDestruction();
}

