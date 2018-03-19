// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

  // Look for attached physics handle
  physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
  findPhysicsHandleComponent();
  SetupInputComponent();
}

// Look for attached physics handle
void UGrabber::findPhysicsHandleComponent()
{
  physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
  if(!physicsHandle)
  {
    UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
  }
}

// Look for attached input component (only appears at run time)
void UGrabber::SetupInputComponent()
{
  input = GetOwner()->FindComponentByClass<UInputComponent>();
  if (input)
  {
    // Bind input axis
    input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
    input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
  }
}

void UGrabber::Grab()
{
  // LINE TRACE Try and reach any actors with physics body collision channel set
  FHitResult hit = getFirstPhysicsBodyInReach();
  auto componentToGrab = hit.GetComponent();
  auto actorHit = hit.GetActor();

  // If we hit something then attach a physics handle
  // attach physics handle
  if (actorHit)
  {
    physicsHandle->GrabComponent(
      componentToGrab,
      NAME_None,
      componentToGrab->GetOwner()->GetActorLocation(),
      true);
  }
}

void UGrabber::Release()
{
  physicsHandle->ReleaseComponent();
}

FVector UGrabber::getLineTraceStart()
{
  FVector viewLocation;
  FRotator viewRotation;
  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(viewLocation, viewRotation);
  return viewLocation;
}

FVector UGrabber::getLineTraceEnd()
{
  FVector viewLocation;
  FRotator viewRotation;
  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(viewLocation, viewRotation);
  return viewLocation + viewRotation.Vector() * reach;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  FVector lineTraceEnd = getLineTraceEnd();

  // If the physics handle is attached
  if (physicsHandle->GrabbedComponent)
  {
    // Move the object what we're holding
    physicsHandle->SetTargetLocation(lineTraceEnd);
  }
}

const FHitResult UGrabber::getFirstPhysicsBodyInReach()
{
  // Draw a red trace in the world to visual
  FVector lineTraceEnd = getLineTraceEnd();

  // Setup query parameters
  FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());

  // Line-trace
  FHitResult hitResults;
  GetWorld()->LineTraceSingleByObjectType(
    OUT hitResults,
    getLineTraceStart(),
    lineTraceEnd,
    FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
    traceParameters
  );

  return hitResults;
}