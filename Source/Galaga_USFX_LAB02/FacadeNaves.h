// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FacadeNaves.generated.h"


class ANaveEnemiga; //Mensaje X
UCLASS()
class GALAGA_USFX_LAB02_API AFacadeNaves : public AActor
{

	GENERATED_BODY()




	
public:	
	// Sets default values for this actor's properties
	AFacadeNaves();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//****************************************************************************

public:
	void SPAWN_NAVES_ENEMIGAS();

//****************************************************************************

public:

	TArray<ANaveEnemiga*> TANavesEnemigas;

private:

	//class IBuilderNaveNodriza* NaveNodrizaEscudo;
	UPROPERTY(VisibleAnywhere, Category = "NaveEscudo")
	class ABuilderNaveEscudo* NaveEscudo;
	UPROPERTY(VisibleAnywhere, Category = "Director")
	class ADirector* Director;

	void CollideEnemyProjectile(AActor* OtherActor); //pawn


//***********************************************************************
	
public:
	void SpawnPowerUpVelocidad();
	FTimerHandle SpawnTimerHandle; 
};
