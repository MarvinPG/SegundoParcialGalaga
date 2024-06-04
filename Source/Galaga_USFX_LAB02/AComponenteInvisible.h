#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AComponenteInvisible.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALAGA_USFX_LAB02_API UAComponenteInvisible : public UActorComponent
{
	GENERATED_BODY()


public:	

	UAComponenteInvisible();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Invisibilidad(float Duracion);

private:
	// Function to make the owning actor visible again
	void HacerVisible();

	// Timer handle for making the actor visible again
	FTimerHandle TimerHandle_VisibleTimerExpired;
};
