// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Galaga_USFX_LAB02Pawn.generated.h"

UCLASS(Blueprintable)
class AGalaga_USFX_LAB02Pawn : public APawn
{
    GENERATED_BODY()

protected:
    // El sonido de Game Over
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    USoundBase* GameOverSound;

    // Componente de audio para el sonido de fondo
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
    UAudioComponent* BackgroundAudioComponent;

    // El sonido de fondo
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    USoundBase* BackgroundSound;

    virtual void BeginPlay() override;

    /* The mesh component */
    UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* ShipMeshComponent;

    /** The camera */
    UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* CameraComponent;

    /** Camera boom positioning the camera above the character */
    UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

public:
    AGalaga_USFX_LAB02Pawn();

    void ActivateSpeedBoost();
    void ResetSpeedAndFireRate();


    /** Offset from the ships location to spawn projectiles */
    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
    FVector GunOffset;

    /* How fast the weapon will fire */
    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
    float FireRate;

    /* The speed our ship moves around the level */
    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
    float MoveSpeed;

    /** Sound to play each time we fire */
    UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
    class USoundBase* FireSound;

    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    FTimerHandle TimerHandle_ShotTimerExpired;
    FTimerHandle TimerHandle_SpeedBoostExpired;
    FTimerHandle TimerHandle_ActivarEstadoPro;

    float OriginalMoveSpeed = 1000.0f;
    float OriginalFireRate = 0.5f;

    /* Fire a shot in the specified direction */
    void FireShot(FVector FireDirection);

    /* Handler for the fire timer expiry */
    void ShotTimerExpired();


private:
    float TasaDisparoOriginal;

    static const FName MoveForwardBinding;
    static const FName MoveRightBinding;
    static const FName FireForwardBinding;
    static const FName FireRightBinding;

private:
    uint32 bCanFire : 1;

public:
    FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
    FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
    int ContImpacto;
public:
    void recibirImpacto();
    void CheckDestroy();
    int VidasRestantes = 5;

    int GetVidasRestantes() const { return VidasRestantes; }

    void ReducirVida()
    {
        if (VidasRestantes > 0)
            VidasRestantes--;
    }

    UFUNCTION()
    void DisplayGameOverMessage();

    void VELOCIDAD();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bImpactReceivedThreeTimes;

protected:
    void PlayGameOverSound();
    void StopBackgroundSound();
};
