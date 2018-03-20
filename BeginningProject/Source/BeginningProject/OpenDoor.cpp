// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

  owner = GetOwner();
  originalYaw = owner->GetActorRotation().Yaw;
}

void UOpenDoor::OpenDoor()
{
  // Set the door rotation
  owner->SetActorRotation(FRotator(0.0f, openAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
  // Set the door rotation
  owner->SetActorRotation(FRotator(0.0f, originalYaw, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume
  // If the actorThatOpens is in the volume
  if (GetTotalMassOfActorsOnPlate() > 50.0f)
  {
    OpenDoor();
    lastDoorOpenTime = GetWorld()->GetTimeSeconds();
  }


  // Check if its time to close the door
  if (GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay)
  {
    CloseDoor();
  }
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
  float totalMass = 0.0f;

  // Find all overlapping actors
  TArray<AActor*> overlappingActors;
  pressurePlate->GetOverlappingActors(OUT overlappingActors);

  // Iterate through them adding their masses


  return totalMass;
}
