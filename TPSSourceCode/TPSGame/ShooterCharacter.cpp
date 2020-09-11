// Copyright Felix(Bicheng) Li


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "TPSGameGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	SideGun = GetWorld()->SpawnActor<AGun>(SideGunClass);
	SideGun->SetActorHiddenInGame(true);
	
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	SideGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	SideGun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveFoward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpController"), this, &AShooterCharacter::LookUpController);
	PlayerInputComponent->BindAxis(TEXT("LookRightController"), this, &AShooterCharacter::LookUpController);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("SwitchWeapon"), IE_Pressed, this, &AShooterCharacter::ChangeWeapon);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &AShooterCharacter::Reload);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(CurrentHealth, DamageApplied);
	CurrentHealth -= DamageApplied;
	UE_LOG(LogTemp, Warning, TEXT("Target current health is %f"), CurrentHealth);
	
	if(IsDead())
	{
		ATPSGameGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ATPSGameGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageApplied;
}

bool AShooterCharacter::IsDead() const
{
	if(!CurrentHealth)
	{
		return true;
	}
	return false;
}

float AShooterCharacter::GetCurrentHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

FName AShooterCharacter::GetCurrentGunName() const
{
	if(bMainGun)
	{
		return Gun->GetGunName();
	}
	else
	{
		return SideGun->GetGunName();
	}
}

int32 AShooterCharacter::GetCurrentAmmo() const
{
	if(bMainGun)
	{
		return Gun->GetGunAmmo();
	}
	else
	{
		return SideGun->GetGunAmmo();
	}
}

int32 AShooterCharacter::GetMaxAmmo() const
{
	if(bMainGun)
	{
		return Gun->GetMaxAmmo();
	}
	else
	{
		return SideGun->GetMaxAmmo();
	}
}

void AShooterCharacter::MoveFoward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUp(float AxisValue) 
{
	AddControllerPitchInput(AxisValue);
}

void AShooterCharacter::LookRight(float AxisValue) 
{
	AddControllerYawInput(AxisValue);
}

void AShooterCharacter::LookUpController(float AxisValue) 
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightController(float AxisValue) 
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot() 
{
	if(bMainGun)
	{
		Gun->PullTriggerMethod();
	}
	else
	{
		SideGun->PullTriggerMethod();
	}
}

void AShooterCharacter::Reload() 
{
	if(bMainGun)
	{
		Gun->ReloadWait();
	}
	else
	{
		SideGun->ReloadWait();
	}
}

void AShooterCharacter::ChangeWeapon() 
{
	if(bMainGun)
	{
		Gun->SwitchWeapon();
		SideGun->SetActorHiddenInGame(false);
		bMainGun = false;
	}
	else
	{
		SideGun->SwitchWeapon();
		Gun->SetActorHiddenInGame(false);
		bMainGun = true;
	}
	
}


