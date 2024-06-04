// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "INaveState.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UINaveState : public UInterface
{
	GENERATED_BODY()
};


class GALAGA_USFX_LAB02_API IINaveState
{
	GENERATED_BODY()

public:
	virtual void Mover(float DeltaTime) = 0;
	virtual void Disparar() = 0;
	virtual void CambiarMalla() = 0;

	virtual void SetAliada(class ANaveEstado* _NaveAliada) = 0;
};
