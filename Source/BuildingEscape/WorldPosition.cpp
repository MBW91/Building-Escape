#include "WorldPosition.h"
#include "GameFramework/actor.h"

UWorldPosition::UWorldPosition()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	FString OwnerName = GetOwner()->GetName();
	FString OwnerPositionString = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is located at: %s"), *OwnerName, *OwnerPositionString);
}