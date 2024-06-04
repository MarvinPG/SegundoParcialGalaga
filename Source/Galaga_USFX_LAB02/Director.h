// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuilderNaveNodriza.h"
#include "Director.generated.h"


UCLASS()
class GALAGA_USFX_LAB02_API ADirector : public AActor
{
	GENERATED_BODY()
	

private:
	IBuilderNaveNodriza* ShipBuilder;

public:	
	// Sets default values for this actor's properties
	ADirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ConstruirNaves();

	void SetBuilder(AActor* Builder);

	class ANODRIZA* GetNaveNodriza(); 



};
