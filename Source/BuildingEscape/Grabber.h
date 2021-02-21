#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()
	UInputComponent* InputComponent = nullptr;

	UPROPERTY(EditAnywhere)
	float Reach = 100.f;

	FCollisionObjectQueryParams ObjectQueryParams;
	FCollisionQueryParams TraceParams;

	void Initialize();
	void Grab();
	void Release();
	FHitResult GetFirstHitResultInReach() const;
	FVector GetPlayersWorldPosition() const;
	FVector GetReachPosition() const;

public:	
	UGrabber();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
};