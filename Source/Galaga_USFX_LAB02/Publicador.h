// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ISubscriptor.h"
#include "Publicador.generated.h"

UCLASS()
class GALAGA_USFX_LAB02_API APublicador : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APublicador();
//private:
	//bool ActualizacionEjecutada;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	class AReloj* Reloj;
private:
	TArray<IISubscriptor*> Subscriptores;
public:
	void AddSubscriptor(IISubscriptor* Subscriptor);
	void RemoveSubscriptor(IISubscriptor* Subscriptor);
	void NotifySubscriptor();
	void SubscriptorReloj(class AReloj* _Reloj);
};
