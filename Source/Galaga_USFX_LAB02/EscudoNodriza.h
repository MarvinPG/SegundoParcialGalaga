// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AComponenteMovimiento.h"
#include "EscudoNodriza.generated.h"




UCLASS()
class GALAGA_USFX_LAB02_API AEscudoNodriza : public AActor
{
	GENERATED_BODY()
	



private:
	UAComponenteMovimiento* MovimientoNavesComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshEscudo;
public:	
	// Sets default values for this actor's properties
	AEscudoNodriza();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
public:

	void ImpactoProyectil(); // Función para manejar el impacto de un proyectil

private:
	int32 ContadorImpactos; // Contador de impactos de proyectiles

};
