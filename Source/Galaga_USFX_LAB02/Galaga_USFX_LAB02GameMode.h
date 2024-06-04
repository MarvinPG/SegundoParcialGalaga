// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Galaga_USFX_LAB02GameMode.generated.h"

UCLASS(MinimalAPI)
class AGalaga_USFX_LAB02GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	class AReloj* Reloj;
	class ATorreEifel* TorreEifel;
	class APublicador* Publicador;
	class ANaveEstado* NaveEstado;

public:
	AGalaga_USFX_LAB02GameMode();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, Category = "FacadeNaves")
	class AFacadeNaves* FacadeNaves;

private:
	void TickReloj();

	float DeltaTime;

	UPROPERTY()
	FTimerHandle TimerHandle_Reloj;

public:
	int E_Reloj;
	bool bEstrategiasCambiadas;

private:
	//PUNTERITO A LA NAVE ESTRATEGICA
	class ANaveEstrategica* Estrategica;
	//PUNTERITO A LAS ESTRATEGIAS DE LA NAVE ESTARTEGICAAAA
	class AEstrategiaEspiadora* E_Espiadora;
	class AEstrategiaAyudante* E_Ayudante;
	class AEstrategiaDisparadora* E_Disparadora;
};