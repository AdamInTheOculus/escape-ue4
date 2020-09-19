// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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
	UE_LOG(LogTemp, Warning, TEXT("About to call FindPhysicsHandle"));
	FindPhysicsHandle();
	UE_LOG(LogTemp, Warning, TEXT("About to call SetupInputComponent"));
	SetupInputComponent();
	UE_LOG(LogTemp, Warning, TEXT("Finished call SetupInputComponent"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(PhysicsHandler->GrabbedComponent) {
		FVector LineTraceEnd = GetLineTraceEnd();
		PhysicsHandler->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Attempting to grab ..."));

	// Try and reach any actors with physics body collision channel set.
	// If we hit something, then attach physics handle.
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	if(HitResult.GetActor()) {
		UE_LOG(LogTemp, Warning, TEXT("Did we collide with PhysicsBody?"));
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
		PhysicsHandler->GrabComponentAtLocation(
			ComponentToGrab, 			// What is getting grabbed?
			NAME_None, 					// ... unsure about this one.
			GetLineTraceEnd() 	// Where (3d coordinates) are you trying to grab?
		);
	}
}

void UGrabber::Release()
{	
	if(PhysicsHandler->GrabbedComponent) {
		PhysicsHandler->ReleaseComponent();
	}
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

	UE_LOG(LogTemp, Warning, TEXT("Initialized SetupInputComponent!"));

	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Ray-cast out to a certain distance (reach)
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType (
		OUT HitResult,
		GetPlayerWorldPosition(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return HitResult;
}

FVector UGrabber::GetLineTraceEnd() const
{
	// Get player location/rotation.
	// Then calculate ray-trace end starting from player.
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FVector UGrabber::GetPlayerWorldPosition() const
{
	return GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
}