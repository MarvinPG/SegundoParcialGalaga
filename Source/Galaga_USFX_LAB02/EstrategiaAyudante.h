// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IEstrategias.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EstrategiaAyudante.generated.h"

UCLASS()
class GALAGA_USFX_LAB02_API AEstrategiaAyudante : public AActor, public IIEstrategias
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEstrategiaAyudante();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Variable booleana para controlar si el mensaje ya se mostró
	static bool bMensajeMostrado;


private:
	// Lista de coordenadas de destino
	TArray<FVector> targetLocations;

	// Índice de la ubicación de destino actual
	int32 currentTargetIndex;

	// Velocidad de movimiento de la nave
	float speed = 1000.0f;

public:
	void Mover(class ANaveEstrategica* PADRIZA, float DeltaTime) override;

};
