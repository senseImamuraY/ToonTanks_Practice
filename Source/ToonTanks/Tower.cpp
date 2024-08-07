// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!Tank) return;

	float DistToTank = FVector::Dist(Tank->GetActorLocation(), this->GetActorLocation());

	UE_LOG(LogTemp, Log, TEXT("SomeValue: %f"), DistToTank);

	if (DistToTank <= FireRange) 
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

}
