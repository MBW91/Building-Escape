#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldPosition.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UWorldPosition : public UActorComponent
{
	GENERATED_BODY()

public:
	UWorldPosition();

protected:
	virtual void BeginPlay() override;
};