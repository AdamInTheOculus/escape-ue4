// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UGlobalPosition::UGlobalPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGlobalPosition::BeginPlay()
{
	Super::BeginPlay();
	// FString Log = TEXT("Hello");
	// FString* PrintLog = &Log;
	// printf("%s", "Hello, World!");

	// UE_LOG(LogTemp, Warning, TEXT("%s"), *Log);
	// UE_LOG(LogTemp, Warning, TEXT("%s"), **PrintLog);

	// ...
	FTransform Transform = GetOwner()->GetTransform();
	FString OwnerName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Name - %s"), *GetOwner()->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Location - %s"), *GetOwner()->GetActorLocation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Velocity - %s"), *GetOwner()->GetVelocity().ToString());
}


// Called every frame
void UGlobalPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

