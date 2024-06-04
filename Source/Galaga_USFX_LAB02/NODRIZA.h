// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConstructorNave.h"
#include "NODRIZA.generated.h"

UCLASS()
class GALAGA_USFX_LAB02_API ANODRIZA : public AActor, public IConstructorNave
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANODRIZA();


private:
	class AEscudoNodriza* Escudo;
	class AHijasNodriza* Hijas;
	class AMotorNaveNodriza* Motor;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetHijasNodrizas( AHijasNodriza* hijas) override;
	virtual void SetEscudoNodriza( AEscudoNodriza* escudo) override;
	virtual void SetMotorNaveNodriza( AMotorNaveNodriza* motor) override;

};
