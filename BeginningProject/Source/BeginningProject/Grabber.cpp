// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#include "GameFramework/Actor.h"
#include "GameFramework//PlayerController.h"

#include "Engine/World.h"

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
  UE_LOG(LogTemp, Warning, TEXT("Location: %s Rotation: %s"), *viewLocation.ToString(), *viewRotation.ToString())

  // Ray-cast out to reach distance


  // See what we hit

}

