
#pragma once

#include "CoreMinimal.h"
#include "NaveEnemiga.h"
#include "NaveEnemigaHacker.generated.h"


UCLASS()
class GALAGA_USFX_LAB02_API ANaveEnemigaHacker : public ANaveEnemiga
{
	GENERATED_BODY()

	
public:
	ANaveEnemigaHacker();

	FString tipoHacker = "Hacker";
public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Mover(float DeltaTime);

protected:

	float speed = 1000.0f;

	float targetXLocations[4]; // Array of x-coordinates of target locations
	float targetYLocations[4]; // Array of y-coordinates of target locations
	int currentTargetIndex = 0; // Index of the current target location

};
