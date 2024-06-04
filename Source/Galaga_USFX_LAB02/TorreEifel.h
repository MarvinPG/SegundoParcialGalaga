// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Publicador.h"
#include "ISubscriptor.h"
#include "TorreEifel.generated.h"

UCLASS()
class GALAGA_USFX_LAB02_API ATorreEifel : public AActor, public IISubscriptor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATorreEifel();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MallaTorre;


public:

	FTimerHandle FireTimerHandle;
	FTimerHandle FireDuroTimerHandle;


	float FireRate1 = 1.0f;
	//float FireRateDuro = 3.0f;

private:
	bool disparoDuroActivo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	APublicador* Publicador;
	void SetPublicador(APublicador* _Publicador);
	virtual void Actualizar() override;
	void EliminaSubs();
	void DispararDuro();
	void FireProjectile();
};
