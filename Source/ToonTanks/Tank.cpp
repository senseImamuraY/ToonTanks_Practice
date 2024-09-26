// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h" 
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HealthComponent.h"
#include "ToonTankPlayerController.h"
#include "ToonTankGameMode.h"


ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));

	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	IA_MoveForwardBackforward = LoadObject<UInputAction>(NULL, TEXT("/Game/Inputs/IA_MoveForwardBackforward.IA_MoveForwardBackforward"), NULL, LOAD_None, NULL);
	IA_MoveLeftRight = LoadObject<UInputAction>(NULL, TEXT("/Game/Inputs/IA_MoveLeftRight.IA_MoveLeftRight"), NULL, LOAD_None, NULL);
	IA_Fire = LoadObject<UInputAction>(NULL, TEXT("/Game/Inputs/IA_Fire.IA_Fire"), NULL, LOAD_None, NULL);

	IMCTank = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Inputs/IMC_Tank.IMC_Tank"), NULL, LOAD_None, NULL);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ToonTankPlayerController)
	{
		FHitResult HitResult;

		ToonTankPlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);


		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::ActorDied()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "TankCalled");

	HandleDestruction();
	if (GetTankPlayerController())
	{
		ToonTankPlayerController->SetPlayerEnabledState(false);
		//DisableInput(GetTankPlayerController());
		//GetTankPlayerController()->bShowMouseCursor = false;
	}

	AToonTankGameMode* ToonTankGameMode = Cast<AToonTankGameMode>(UGameplayStatics::GetGameMode(this));
	ToonTankGameMode->GameOver(false);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();


	APlayerController* TankPlayerController = Cast<APlayerController>(GetController());
	ToonTankPlayerController = Cast< AToonTankPlayerController>(TankPlayerController);


	// “ü—Í‚ð—LŒø‚É‚·‚é
	//EnableInput(TankPlayerController);

	if (InputComponent)
	{
		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) 
		{
			// Input Action
			EnhancedInputComponent->BindAction(IA_MoveForwardBackforward, ETriggerEvent::Triggered, this, &ATank::Move);
			EnhancedInputComponent->BindAction(IA_MoveLeftRight, ETriggerEvent::Triggered, this, &ATank::Turn);
			EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Started, this, &ATank::Fire);
		}

		// Input Mapping Context‚ð“o˜^‚·‚é
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(ToonTankPlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMCTank, 0);
		}
	}


	//OnTakeAnyDamage.AddDynamic(this, &ATank::OnTakeDamage);
}

void ATank::EventAction(const FInputActionValue& Value)
{
}

void ATank::Fire()
{
	Super::Fire();

	if (ToonTankPlayerController)
	{
		FHitResult HitResult;

		ToonTankPlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);

		//DrawDebugSphere(
		//	GetWorld(),
		//	HitResult.ImpactPoint,
		//	25.f,
		//	12,
		//	FColor::Red,
		//	false,
		//	-1.f);

		//RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::Move(const FInputActionValue& Value)
{
	// FInputActionValue‚©‚çfloat’l‚ðŽæ“¾
	float FloatValue = Value.Get<float>();

	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = FloatValue * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);

	// ‘O•û‚ÉˆÚ“®
	if (FloatValue != 0.0f)
	{
		AddActorLocalOffset(DeltaLocation, true);
	}
}

void ATank::Turn(const FInputActionValue& Value)
{
	//// FInputActionValue‚©‚çfloat’l‚ðŽæ“¾
	float FloatValue = Value.Get<float>();
	FRotator DeltaRotation = FRotator::ZeroRotator;

	DeltaRotation.Yaw = FloatValue * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}
