// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "BasePawn.h"
#include "ToonTankPlayerController.h"

void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
	if (!DeadActor) return;

	ABasePawn* BasePawn = Cast<ABasePawn>(DeadActor);
	BasePawn->ActorDied();
	//if (DeadActor == Tank)
	//{
	//	Tank->HandleDestruction();
	//	if (Tank->GetTankPlayerController())
	//	{
	//		Tank->DisableInput(Tank->GetTankPlayerController());
	//		Tank->GetTankPlayerController()->bShowMouseCursor = false;
	//	}
	//}
	//else if ()
	//{

	//}
}

void AToonTankGameMode::SubtractOneFromTowerCount()
{
	TargetTowers--;
	if (TargetTowers <= 0)
	{
		GameOver(true);
	}
}

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTankGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	StartGame();

	if (ToonTankPlayerController) 
	{
		ToonTankPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTankPlayerController,
			&AToonTankPlayerController::SetPlayerEnabledState,
			true
		);

		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false
		);
	}
}

int32 AToonTankGameMode::GetTargetTowerCount()
{
	TArray<AActor*> TowerArary;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), TowerArary);

	return TowerArary.Num();
}
