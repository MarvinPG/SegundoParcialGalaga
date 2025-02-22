// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAInvisible.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALAGA_USFX_LAB02_API UCAInvisible : public UActorComponent
{
	GENERATED_BODY()


public:	
	UStaticMeshComponent* mallaNave;
	UCAInvisible();
	

protected:

	virtual void BeginPlay() override;


public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
