// Copyright Felix(Bicheng) Li


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComp);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	Mesh->SetupAttachment(RootComp);

}

void AGun::PullTriggerMethod() 
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return;

	FHitResult HitResult;
	FVector ShotDirection;
	bool bSuccess = GunTrace(HitResult, ShotDirection);

	//Check if is reloading time
	if(bCanShoot){
		if(bSuccess){
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitImpact, HitResult.Location, ShotDirection.Rotation());
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, HitResult.Location, ShotDirection.Rotation());
			AActor* HitActor = HitResult.GetActor();
			if(HitActor != nullptr)
			{
				FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
				HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}

		}
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
		//UE_LOG(LogTemp, Warning, TEXT("Shoot!"));
		Ammo--;
		if(!Ammo){
			ReloadWait();
		}
	}	
}

void AGun::Reload() 
{
	UE_LOG(LogTemp, Warning, TEXT("Reload Complete!"));
	Ammo = MaxAmmo;
	bCanShoot = true;
}

void AGun::ReloadWait() 
{
	if (Ammo == MaxAmmo) return;
	UE_LOG(LogTemp, Warning, TEXT("Reloading..."));
	bCanShoot = false;
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &AGun::Reload, ReloadTime, false);
}

void AGun::SwitchWeapon() 
{
	UE_LOG(LogTemp, Warning, TEXT("Change Weapon!"));
	this->SetActorHiddenInGame(true);
	//TO DO: Need To Save and Update Ammo;
}

FName AGun::GetGunName() const
{
	return GunName;
}

int32 AGun::GetGunAmmo() const
{
	return Ammo;
}

int32 AGun::GetMaxAmmo() const
{
	return MaxAmmo;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	Ammo = MaxAmmo;
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& HitResult, FVector& ShotDirection) 
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;

	FVector ViewpointLocation;
	FRotator ViewpointRotation;
	OwnerController->GetPlayerViewPoint(ViewpointLocation, ViewpointRotation);
	//DrawDebugCamera(GetWorld(), ViewpointLocation, ViewpointRotation, 90, 2, FColor::Red, true);

	FVector ViewpointEnd = ViewpointRotation.Vector() * MaxRange + ViewpointLocation;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, ViewpointLocation, ViewpointEnd, ECC_GameTraceChannel11, Params);
	ShotDirection = -ViewpointRotation.Vector();
	//DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Yellow, true);

	return bSuccess;


}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return nullptr;

	AController* OwnerController = OwnerPawn->GetController();
	
	return OwnerController;
}

