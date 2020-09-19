// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UOpenDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float GetTotalMassOfActors() const;

private:
	float InitialYaw;
	float CurrentYaw;
	UPROPERTY(EditAnywhere) float TargetYaw = 90.f;
	UPROPERTY(EditAnywhere) float DoorLastOpened = 0.f;
	UPROPERTY(EditAnywhere) float DoorCloseDelay = 2.f;
	UPROPERTY(EditAnywhere) ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere) AActor* OpenActor;
	UPROPERTY(EditAnywhere) TArray<AActor*> OpenActors;
	UPROPERTY(EditAnywhere) float MinimumMass = 70.f;
};
