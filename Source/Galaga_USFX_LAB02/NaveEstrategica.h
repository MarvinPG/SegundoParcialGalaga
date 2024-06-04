// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NaveEstrategica.generated.h"

UCLASS()
class GALAGA_USFX_LAB02_API ANaveEstrategica : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANaveEstrategica();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reloj, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MallaPapa;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Puntero a la interfaz estrategia
	class IIEstrategias* Estrategia;
protected:

	void FireProjectile();
	float FireRate;
	FTimerHandle FireTimerHandle;
	//**********


private:
	int32 ProjectileCount; // Contador de proyectiles
	int32 MaxProjectiles;  // Máximo de proyectiles disponibles

public:
	void AlterarEstrategia(AActor* _EstrategiaElegida);
	void EmplearEstrategia(float DeltaTime);

};
