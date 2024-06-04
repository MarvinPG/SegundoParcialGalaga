// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Reloj.generated.h"

UCLASS()
class GALAGA_USFX_LAB02_API AReloj : public AActor
{
	GENERATED_BODY()

public:

	float Hora = 0;
	
public:	
	// Sets default values for this actor's properties
	AReloj();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reloj, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MallaReloj;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetTiempo() { return Hora; }

};
