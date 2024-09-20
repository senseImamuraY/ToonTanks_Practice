// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "HealthComponent.h"


ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange()) 
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::ActorDied()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "TowerCalled");

	HandleDestruction();
	
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
	//OnTakeAnyDamage.AddDynamic(this, &ATower::OnTakeDamage);
}

void ATower::CheckFireCondition()
{
	if (InFireRange()) 
	{
		//DrawDebugSphere(
		//	GetWorld(),
		//	Tank->GetActorLocation(),
		//	25.f,
		//	12,
		//	FColor::Blue,
		//	false,
		//	2.f);
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (!Tank) return false;

	float DistToTank = FVector::Dist(Tank->GetActorLocation(), this->GetActorLocation());
	if (FireRange >= DistToTank) return true;
	
	return false;
}

