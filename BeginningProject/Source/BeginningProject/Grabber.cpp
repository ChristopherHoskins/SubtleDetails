// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#include "GameFramework/Actor.h"
#include "GameFramework//PlayerController.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

  UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player viewpoint this tick
  FVector viewLocation;
  FRotator viewRotation;
  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(viewLocation, viewRotation);
  //UE_LOG(LogTemp, Warning, TEXT("Location: %s Rotation: %s"), *viewLocation.ToString(), *viewRotation.ToString())

  // Draw a red trace in the world to visual
  FVector unitVector = FVector(1.0f, 1.0f, 1.0);
  FVector LineTraceEnd = viewLocation + viewRotation * unitVector * reach;

  // Ray-cast out to reach distance
  DrawDebugLine(
    GetWorld(),
    viewLocation,
    LineTraceEnd,
    FColor(255, 0, 0),
    false,
    0.0f,
    0.0f,
    10.0f
  );

  // See what we hit

}

