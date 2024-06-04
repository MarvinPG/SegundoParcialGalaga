// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveEnemiga.h"

#include "NaveEnemigaNODRIZA.generated.h"

/**
 * 
 */

UCLASS()
class GALAGA_USFX_LAB02_API ANaveEnemigaNODRIZA : public ANaveEnemiga
{
	GENERATED_BODY()







private:
	ANaveEnemigaNODRIZA();

private:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;	
	virtual void Mover(float DeltaTime);
	
};
