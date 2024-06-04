// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "INaveState.h"
#include "EstadoAplazado.generated.h"

UCLASS()
class GALAGA_USFX_LAB02_API AEstadoAplazado : public AActor, public IINaveState
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEstadoAplazado();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int32 ProjectileCount; // Contador de proyectiles
	int32 MaxProjectiles;  // Máximo de proyectiles disponibles



private:
	float MovimientoNaves = 4;
	float limiteInferiorY = 1600.0f;
	int DireccionMovimientoHorizontal = 1;
private:

	float FireRate;
	FTimerHandle FireTimerHandle;

	UPROPERTY()
	UStaticMesh* NuevaMalla;


public:
	virtual void Mover(float DeltaTime) override;
	virtual void Disparar() override;
	virtual void CambiarMalla() override;
	virtual void SetAliada(class ANaveEstado* _NaveAliada) override;

private:
	class ANaveEstado* NaveAliada;

};
