// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IEstrategias.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EstrategiaEspiadora.generated.h"

UCLASS()
class GALAGA_USFX_LAB02_API AEstrategiaEspiadora : public AActor, public IIEstrategias
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEstrategiaEspiadora();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Variable booleana para controlar si el mensaje ya se mostró
	static bool bMensajeMostrado;

public:
	void Mover(class ANaveEstrategica* PADRIZA, float DeltaTime) override;


public:
	float Radio = 2000.0f;
	float Angulo = 0.0f;
	float Speed = 10.0f;
};
