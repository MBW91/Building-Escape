#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f;
	UPROPERTY(EditAnywhere)
	float DoorOpenAnimationFactor = 1.f;
	UPROPERTY(EditAnywhere)
	float DoorCloseAnimationFactor = 4.f;
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;
	UPROPERTY(EditAnywhere)
	float DoorAnimationSpeed = 2.f;
	UPROPERTY(EditAnywhere)
	float OpenMassTreshold = 50.f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY()
	UAudioComponent* DoorSound = nullptr;

	float InitialAngle;
	float CurrentAngle;
	float DoorLastOpened = 0.f;
	bool OpenDoorSoundPlayed = false;
	bool CloseDoorSoundPlayed = true;

	void ToggleDoor(bool open, float DeltaTime);
	float GetTotalMassOfActors() const;

public:
	UOpenDoor();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
};
