// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "BasePawn.h"

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

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));


}
