// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Grabber.h"

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
	
	FindPhysicsHandle();
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Get players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// Draw a line from player showing the reach.
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	// DrawDebugLine (
	// 	GetWorld(),
	// 	PlayerViewPointLocation,
	// 	LineTraceEnd,
	// 	FColor(0, 255, 0),
	// 	false,
	// 	0.f,
	// 	0,
	// 	5.f
	// );

	// Ray-cast out to a certain distance (reach)
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType (
		OUT HitResult,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return HitResult;
}

void UGrabber::FindPhysicsHandle()
{
	// Check for PhysicsHandlerComponent
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandler == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Failed to find UPhysicsHandleComponent in [%s]."), *GetOwner()->GetName());
		return;
	}
}

void UGrabber::SetupInputComponent()
{
	// Check for UInputComponent
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Failed to find UInputController in [%s]."), *GetOwner()->GetName());
		return;
	}

	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("You pressed: "));

	// Try and reach any actors with physics body collision channel set.
	// If we hit something, then attach physics handle.
	// TODO(adam): Attach physics handle.
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	if(HitResult.GetActor()) {
		UE_LOG(LogTemp, Warning, TEXT("Colliding with actor: %s"), *HitResult.GetActor()->GetName());
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("You released: "));
	// TODO(adam): Remove/release the physics handle.
}