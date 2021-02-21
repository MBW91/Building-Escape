#include "OpenDoor.h"
#include "GameFramework/actor.h"

#define OUT

UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component on it, but no PressurePlate is set!"), *GetOwner()->GetName());
	}

	DoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!DoorSound)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component on it, but it's missing an UAudioComponent!"), *GetOwner()->GetName());
	}

	InitialAngle = CurrentAngle = GetOwner()->GetActorRotation().Yaw;
	OpenAngle += InitialAngle;
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PressurePlate) return;

	if (GetTotalMassOfActors() >= OpenMassTreshold)
	{
		ToggleDoor(true, DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened >= DoorCloseDelay)
		{
			ToggleDoor(false, DeltaTime);
		}
	}
}

void UOpenDoor::ToggleDoor(bool open, float DeltaTime)
{
	if (FMath::IsNearlyEqual(CurrentAngle, open ? OpenAngle : InitialAngle, 0.1f)) return;

	CurrentAngle = FMath::FInterpTo(CurrentAngle, open ? OpenAngle : InitialAngle, DeltaTime, DoorAnimationSpeed * (open ? DoorOpenAnimationFactor : DoorCloseAnimationFactor));
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentAngle;
	GetOwner()->SetActorRotation(DoorRotation);

	if (DoorSound && ((open && !OpenDoorSoundPlayed) || (!open && !CloseDoorSoundPlayed)))
	{
		DoorSound->Play();
		OpenDoorSoundPlayed = open;
		CloseDoorSoundPlayed = !open;
	}
}

float UOpenDoor::GetTotalMassOfActors() const
{
	if (!PressurePlate) return 0.f;

	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}