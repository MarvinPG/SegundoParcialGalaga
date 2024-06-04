// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AComponenteMovimiento.h"
#include "MotorNaveNodriza.generated.h"

UCLASS()
class GALAGA_USFX_LAB02_API AMotorNaveNodriza : public AActor
{
	GENERATED_BODY()
	

protected:
	UAComponenteMovimiento* MovimientoNavesComponent;

	UStaticMeshComponent* MeshComponente;
public:

	AMotorNaveNodriza();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



protected:

	void FireProjectile();
	float FireRate;
	FTimerHandle FireTimerHandle;


public:
	void ImpactoProyectilMotor(); // Función para manejar el impacto de un proyectil

protected:
		int32 ContadorImpactos; // Contador de impactos de proyectiles

};
