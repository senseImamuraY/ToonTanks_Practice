// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleComponent.h"

// Sets default values for this component's properties
USampleComponent::USampleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Locations.Emplace(FVector(1, 0, 0));
	// ...
}


// Called when the game starts
void USampleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ElapsedTime = 0.0f;
}


// Called every frame
void USampleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	ElapsedTime += DeltaTime;
	FString Message = FString::Printf(TEXT("Actor Elapsed: %f Delta: %f"), ElapsedTime, DeltaTime);

	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
}

void USampleComponent::AttachSampleComponent(AActor* Actor, FVector Location)
{
	if (!Actor) return;

	USampleComponent* Comp = NewObject<USampleComponent>(Actor);
	Comp->Locations.SetNum(1);
	Comp->Locations[0] = Location;
	Actor->AddInstanceComponent(Comp);
	Comp->RegisterComponent();
}

