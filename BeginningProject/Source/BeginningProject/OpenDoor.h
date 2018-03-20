// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

#define OUT

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEGINNINGPROJECT_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
  void OpenDoor();
  void CloseDoor();
  float GetTotalMassOfActorsOnPlate();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
  UPROPERTY(EditAnywhere)
  float openAngle;

  UPROPERTY(EditAnywhere)
  ATriggerVolume *pressurePlate;

  UPROPERTY(EditAnywhere)
  float doorCloseDelay = 1.0f;

  float lastDoorOpenTime;
  float originalYaw;

  AActor *owner;
};
