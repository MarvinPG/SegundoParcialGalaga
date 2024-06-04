// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "INaveState.h"
#include "NaveEstado.generated.h"


UCLASS()
class GALAGA_USFX_LAB02_API ANaveEstado : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reloj, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MallaEstado;
	
public:	
	// Sets default values for this actor's properties
	ANaveEstado();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UStaticMeshComponent* ANaveEstado::GetStaticMeshComponent() const
	{
		return MallaEstado;
	}

	int vida;

public:

	void RecibirDanio();

	IINaveState* EstadoNormal;
	IINaveState* EstadoNokia;
	IINaveState* EstadoAplazado;
	IINaveState* Estado; //ACTUAL

	void InicializarEstados(); //Aqui almaceno cada estado que le doy a la interface IINaveState
	void MoverAliada(float DeltaTime);
	void DispararAliada();
	void CambiarMalla();
	void MostrarEstado(IINaveState* _State);

	IINaveState* GetEstadoNormal(); //Son metodos accesores REFERENCE 1
	IINaveState* GetEstadoNokia();
	IINaveState* GetEstadoAplazado();
	IINaveState* GetEstado();


};
