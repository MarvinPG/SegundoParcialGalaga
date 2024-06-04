// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "INaveState.h"
#include "EstadoNokia.generated.h"

UCLASS()
class GALAGA_USFX_LAB02_API AEstadoNokia : public AActor, public IINaveState
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEstadoNokia();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Lista de coordenadas de destino
	TArray<FVector> targetLocations;

	// Índice de la ubicación de destino actual
	int32 currentTargetIndex;

	// Velocidad de movimiento de la nave
	float Speed = 1000.0f;

private:
	float FireRate;
	FTimerHandle FireTimerHandle;

private:
	int32 ProjectileCount; // Contador de proyectiles
	int32 MaxProjectiles;  // Máximo de proyectiles disponibles

public:
	virtual void Mover(float DeltaTime) override;
	virtual void Disparar() override;
	virtual void CambiarMalla() override;
	virtual void SetAliada(class ANaveEstado* _NaveAliada) override;

private:
	class ANaveEstado* NaveAliada1;
};
