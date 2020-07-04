// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

APawnTank::APawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
    PlayerControllerRef = Cast<APlayerController>(GetController());
	
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (PlayerControllerRef)
    {
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, true, HitResult);
        FVector HitLocation = HitResult.ImpactPoint;
        //UE_LOG(LogTemp, Warning, TEXT("%s"), *HitLocation.ToString());  //Test mouse location code

        RotateTurrent(HitLocation);
    }
    Rotate();
    Move();

}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("RotateAround", this, &APawnTank::CalculateRotateInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveInput(float Value)
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.f, 0.f);
}
void APawnTank::CalculateRotateInput(float Value)
{
    float Rotate = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator RotateAngle = FRotator(0, Rotate, 0);
    RotateDirection = FQuat(RotateAngle);
    
}
void APawnTank::Move()
{
    AddActorLocalOffset(MoveDirection, true);
}
void APawnTank::Rotate()
{
    AddActorLocalRotation(RotateDirection, true);
}

void APawnTank::HandleDestruction()
{
    Super::HandleDestruction();

    bAlive = false;

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

bool APawnTank::GetPlayerAlive()
{
    return bAlive;
}