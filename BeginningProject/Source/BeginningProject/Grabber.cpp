// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#include "GameFramework/Actor.h"
#include "GameFramework//PlayerController.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

#define OUT

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

  // Look for attached physics handle
  physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
  if(physicsHandle)
  {
    
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
  }

  input = GetOwner()->FindComponentByClass<UInputComponent>();
  if (input)
  {
    UE_LOG(LogTemp, Warning, TEXT("Input component found"))
    // Bind input axis
    input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
  }
}

void UGrabber::Grab()
{
  UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
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
  FVector lineTraceEnd = viewLocation + viewRotation.Vector() * reach;

  // Ray-cast out to reach distance
  DrawDebugLine(
    GetWorld(),
    viewLocation,
    lineTraceEnd,
    FColor(255, 0, 0),
    false,
    0.0f,
    0.0f,
    10.0f
  );

  // Setup query parameters
  FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());

  // Line-trace
  FHitResult hitResults;
  GetWorld()->LineTraceSingleByObjectType(
    OUT hitResults,
    viewLocation,
    lineTraceEnd,
    FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
    traceParameters
  );

  // See what we hit
  AActor* hitActor = hitResults.GetActor();
  if (hitActor)
  {
    UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *(hitActor->GetName()))
  }
}

