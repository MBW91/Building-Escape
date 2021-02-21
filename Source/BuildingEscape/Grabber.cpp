#include "Grabber.h"
#include "Engine/Public/DrawDebugHelpers.h"

#define OUT

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReachPosition());
	}
}

void UGrabber::Grab()
{
	FHitResult Hit = GetFirstHitResultInReach();
	if (PhysicsHandle && Hit.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation(Hit.GetComponent(), NAME_None, GetReachPosition());
	}
}

void UGrabber::Release()
{
	if (!PhysicsHandle) return;

	PhysicsHandle->ReleaseComponent();
}

FVector UGrabber::GetPlayersWorldPosition() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT(PlayerViewPointLocation),
		OUT(PlayerViewPointRotation)
	);
	return PlayerViewPointLocation;
}

FHitResult UGrabber::GetFirstHitResultInReach() const
{
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT(Hit), GetPlayersWorldPosition(), GetReachPosition(), ObjectQueryParams, TraceParams);
	return Hit;
}

FVector UGrabber::GetReachPosition() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT(PlayerViewPointLocation),
		OUT(PlayerViewPointRotation)
	);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

void UGrabber::Initialize()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the Grabber component on it, but no PhysicsHandle is set!"), *GetOwner()->GetName());
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction(TEXT("Grab"), IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction(TEXT("Grab"), IE_Released, this, &UGrabber::Release);
	}

	TraceParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	ObjectQueryParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
}