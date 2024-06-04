#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AComponenteMovimiento.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALAGA_USFX_LAB02_API UAComponenteMovimiento : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAComponenteMovimiento();



public:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float limiteInferiorY = 1600.0f;
	int DireccionMovimientoHorizontal = 1;
};
