// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AComponenteMovimiento.h"
#include "HijasNodriza.generated.h"

UCLASS()
class GALAGA_USFX_LAB02_API AHijasNodriza : public AActor
{
	GENERATED_BODY()
	



private:
	UAComponenteMovimiento* MovimientoNavesComponent;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))  
	UStaticMeshComponent* MeshComp;
	// Sets default values for this actor's properties
	AHijasNodriza();

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
	//**********

public:

	void ImpactoProyectilHijas(); // Función para manejar el impacto de un proyectil

private:
	int32 ContadorImpactos; // Contador de impactos de proyectiles

};
