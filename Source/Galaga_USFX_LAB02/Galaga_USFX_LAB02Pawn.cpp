// Copyright Epic Games, Inc. All Rights Reserved.

#include "Galaga_USFX_LAB02Pawn.h"
#include "Galaga_USFX_LAB02Projectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"

const FName AGalaga_USFX_LAB02Pawn::MoveForwardBinding("MoveForward");
const FName AGalaga_USFX_LAB02Pawn::MoveRightBinding("MoveRight");
const FName AGalaga_USFX_LAB02Pawn::FireForwardBinding("FireForward");
const FName AGalaga_USFX_LAB02Pawn::FireRightBinding("FireRight");

AGalaga_USFX_LAB02Pawn::AGalaga_USFX_LAB02Pawn()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
    // Create the mesh component
    ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
    RootComponent = ShipMeshComponent;
    ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
    ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
    SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));

    // Cargar el sonido de disparo
    static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("SoundWave'/Game/TwinStick/Audio/TwinStickFire.TwinStickFire'"));
    FireSound = FireAudio.Object;

    // Cargar el sonido de Game Over
    static ConstructorHelpers::FObjectFinder<USoundBase> GameOverAudio(TEXT("SoundWave'/Game/StarterContent/Audio/sound/Game_Over.Game_Over'"));
    GameOverSound = GameOverAudio.Object;

    // Cargar el sonido de fondo
    static ConstructorHelpers::FObjectFinder<USoundBase> BackgroundAudio(TEXT("SoundWave'/Game/StarterContent/Audio/sound/FONDO.FONDO'"));
    BackgroundSound = BackgroundAudio.Object;

    // Crear el componente de audio para el sonido de fondo
    BackgroundAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BackgroundAudioComponent"));
    BackgroundAudioComponent->SetupAttachment(RootComponent);
    BackgroundAudioComponent->SetSound(BackgroundSound);

    // Create a camera boom...
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->SetUsingAbsoluteRotation(true);
    CameraBoom->TargetArmLength = 1200.f;
    CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
    CameraBoom->bDoCollisionTest = false;

    // Create a camera...
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    CameraComponent->bUsePawnControlRotation = false;




    // Movement
    MoveSpeed = 1000.0f;
    // Weapon
    GunOffset = FVector(90.f, 0.f, 0.f);
    FireRate = 0.5f;
    bCanFire = true;
}

void AGalaga_USFX_LAB02Pawn::BeginPlay()
{
    Super::BeginPlay();

    // Reproducir el sonido de fondo
    if (BackgroundAudioComponent && BackgroundSound)
    {
        BackgroundAudioComponent->Play();
    }
}

void AGalaga_USFX_LAB02Pawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);

    // set up gameplay key bindings
    PlayerInputComponent->BindAxis(MoveForwardBinding);
    PlayerInputComponent->BindAxis(MoveRightBinding);
    PlayerInputComponent->BindAxis(FireForwardBinding);
    PlayerInputComponent->BindAxis(FireRightBinding);
}

void AGalaga_USFX_LAB02Pawn::Tick(float DeltaSeconds)
{
    // Find movement direction
    const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
    const float RightValue = GetInputAxisValue(MoveRightBinding);

    // Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
    const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

    // Calculate movement
    const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

    // If non-zero size, move this actor
    if (Movement.SizeSquared() > 0.0f)
    {
        const FRotator NewRotation = Movement.Rotation();
        FHitResult Hit(1.f);
        RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

        if (Hit.IsValidBlockingHit())
        {
            const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
            const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
            RootComponent->MoveComponent(Deflection, NewRotation, true);
        }
    }

    // Create fire direction vector
    const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
    const float FireRightValue = GetInputAxisValue(FireRightBinding);
    const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);

    // Try and fire a shot
    FireShot(FireDirection);
}

void AGalaga_USFX_LAB02Pawn::FireShot(FVector FireDirection)
{
    // If it's ok to fire againe
    if (bCanFire == true)
    {
        // If we are pressing fire stick in a direction
        if (FireDirection.SizeSquared() > 0.0f)
        {
            const FRotator FireRotation = FireDirection.Rotation();
            // Spawn projectile at an offset from this pawn
            const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

            UWorld* const World = GetWorld();
            if (World != nullptr)
            {
                // spawn the projectile
                World->SpawnActor<AGalaga_USFX_LAB02Projectile>(SpawnLocation, FireRotation);
            }

            bCanFire = false;
            World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AGalaga_USFX_LAB02Pawn::ShotTimerExpired, FireRate);

            // try and play the sound if specified
            if (FireSound != nullptr)
            {
                UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
            }

            bCanFire = false;
        }
    }
}

void AGalaga_USFX_LAB02Pawn::ShotTimerExpired()
{
    bCanFire = true;
}

void AGalaga_USFX_LAB02Pawn::recibirImpacto()
{
    ContImpacto++; // Incrementar el contador de impactos

    // Verificar si el pawn debe ser destruido
    CheckDestroy();
}

void AGalaga_USFX_LAB02Pawn::CheckDestroy()
{
    if (ContImpacto >= 5)
    {
        Destroy();

        // Mostrar el mensaje de "GAME OVER"
        DisplayGameOverMessage();
    }
}

void AGalaga_USFX_LAB02Pawn::DisplayGameOverMessage()
{
    FString Message = FString::Printf(TEXT("GAME OVER"));
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, Message, true, FVector2D(19.0f, 19.0f));

    if (BackgroundAudioComponent)
    {
        BackgroundAudioComponent->Stop();
    }

    if (GameOverSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, GameOverSound, GetActorLocation());
    }
}

void AGalaga_USFX_LAB02Pawn::VELOCIDAD()
{
    ActivateSpeedBoost();
}

void AGalaga_USFX_LAB02Pawn::ActivateSpeedBoost()
{
    MoveSpeed = 3000.0f;
    FireRate = 0.1f;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_SpeedBoostExpired, this, &AGalaga_USFX_LAB02Pawn::ResetSpeedAndFireRate, 5.0f, false);
}

void AGalaga_USFX_LAB02Pawn::ResetSpeedAndFireRate()
{
    MoveSpeed = OriginalMoveSpeed;
    FireRate = OriginalFireRate;
}

void AGalaga_USFX_LAB02Pawn::PlayGameOverSound()
{
    if (GameOverSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, GameOverSound, GetActorLocation());
    }
}

void AGalaga_USFX_LAB02Pawn::StopBackgroundSound()
{
    if (BackgroundAudioComponent)
    {
        BackgroundAudioComponent->Stop();
    }
}
