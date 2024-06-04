// awa
#include "FacadeNaves.h"
#include "NaveEnemiga.h"
#include "NaveEnemigaCaza.h"
#include "NaveEnemigaTransporte.h"
#include "NaveEnemigaEspia.h"
#include "NaveEnemigaHacker.h"
#include "NaveEnemigaUwU.h"
#include "NaveEnemigaRalentizadora.h"
#include "NaveEnemigaFactory.h"
#include "NaveEnemigaNODRIZA.h"
#include "Director.h"
#include "BuilderNaveEscudo.h"
#include "NODRIZA.h"
#include "PowerUp.h"
#include "PowerUpVelocidad.h"
#include "Galaga_USFX_LAB02Pawn.h"
#include "HijasNodriza.h"
#include "EscudoNodriza.h"
#include "MotorNaveNodriza.h"

// Sets default values
AFacadeNaves::AFacadeNaves()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFacadeNaves::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFacadeNaves::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//***********************************************************************************************************************************************************

void AFacadeNaves::SPAWN_NAVES_ENEMIGAS()
{
    // Define la ubicación inicial para spawnear las naves enemigas

    FVector ubicacionInicialNaves1 = FVector(1000.0f, -450.0f, 200.0f);
    FRotator rotacionNave1 = FRotator(0.0f, 180.0f, 0.0f);

    FVector ubicacionInicialNaves2 = FVector(700.0f, -300.0f, 200.0f);
    FRotator rotacionNave2 = FRotator(0.0f, 180.0f, 0.0f);

    FVector ubicacionInicialNaves3 = FVector(700.0f, -550.0f, 200.0f);
    FRotator rotacionNave3 = FRotator(0.0f, 180.0f, 0.0f);

    FVector ubicacionInicialNaves4 = FVector(100.0f, 450.0f, 200.0f);
    FRotator rotacionNave4 = FRotator(0.0f, 180.0f, 0.0f);

    FVector ubicacionInicialNaves5 = FVector(-200.0f, 700.0f, 200.0f);
    FRotator rotacionNave5 = FRotator(0.0f, 180.0f, 0.0f);

    FVector ubicacionInicialNaves6 = FVector(1000.0f, -700.0f, 200.0f);
    FRotator rotacionNave6 = FRotator(0.0f, 180.0f, 0.0f);

 //***********************************************************************************************************************************************************

      // Obtiene el mundo del juego
    UWorld* const World = GetWorld();
    if (World != nullptr)
    {

        //NODRIZA BUILDER
        Director = GetWorld()->SpawnActor<ADirector>(ADirector::StaticClass());
        NaveEscudo = GetWorld()->SpawnActor<ABuilderNaveEscudo>(ABuilderNaveEscudo::StaticClass());
        Director->SetBuilder(NaveEscudo);
        Director->ConstruirNaves();

        ANODRIZA* Nodriza = Director->GetNaveNodriza();

        for (int i = 0; i < 4; i++) {
            FVector ubicacionActual1 = FVector(ubicacionInicialNaves1.X, ubicacionInicialNaves1.Y + 300.0f * (float)i, ubicacionInicialNaves1.Z);
            ANaveEnemiga* NaveEnemigaHacker = ANaveEnemigaFactory::FabricaNaves("Hacker", World, ubicacionActual1, rotacionNave1);
            TANavesEnemigas.Add(NaveEnemigaHacker);
        }
        FVector ubicacionActual2 = FVector(ubicacionInicialNaves1.X - 300.0f, ubicacionInicialNaves2.Y, ubicacionInicialNaves2.Z);
        for (int j = 0; j < 3; j++) {
            ubicacionActual2.Y = ubicacionInicialNaves2.Y + 300.0f * (float)j;
            ANaveEnemiga* NaveEnemigaTransporteActual = ANaveEnemigaFactory::FabricaNaves("Transporte", World, ubicacionActual2, rotacionNave2);
            TANavesEnemigas.Add(NaveEnemigaTransporteActual);
        }
        FVector ubicacionActual3 = FVector(ubicacionInicialNaves1.X - 600.0f, ubicacionInicialNaves3.Y, ubicacionInicialNaves3.Z);
        for (int j = 0; j < 5; j++) {
            ubicacionActual3.Y = ubicacionInicialNaves3.Y + 300.0f * j;
            ANaveEnemiga* NaveEnemigaRalentizadoraActual = ANaveEnemigaFactory::FabricaNaves("Ralentizadora", World, ubicacionActual3, rotacionNave3);
            TANavesEnemigas.Add(NaveEnemigaRalentizadoraActual);
        }
        FVector ubicacionActual4 = FVector(ubicacionInicialNaves1.X - 900.0f, ubicacionInicialNaves4.Y, ubicacionInicialNaves4.Z);
        for (int j = 0; j < 4; j++) {
            ubicacionActual4.Y = ubicacionInicialNaves4.Y - 300.0f * j;
            ANaveEnemiga* NaveEnemigaEspiaActual = ANaveEnemigaFactory::FabricaNaves("Espia", World, ubicacionActual4, rotacionNave4);
            TANavesEnemigas.Add(NaveEnemigaEspiaActual);
        }
        FVector ubicacionActual5 = FVector(ubicacionInicialNaves1.X - 1200.0f, ubicacionInicialNaves5.Y, ubicacionInicialNaves5.Z);
        for (int j = 0; j < 6; j++) {
            ubicacionActual5.Y = ubicacionInicialNaves5.Y - 300.0f * j;
            ANaveEnemiga* NaveEnemigaCazaActual = ANaveEnemigaFactory::FabricaNaves("Caza", World, ubicacionActual5, rotacionNave5);
            TANavesEnemigas.Add(NaveEnemigaCazaActual);
        }
        FVector ubicacionActual6 = FVector(ubicacionInicialNaves1.X, ubicacionInicialNaves6.Y, ubicacionInicialNaves6.Z);
        for (int j = 0; j < 2; j++) {
            ubicacionActual6.Y = ubicacionInicialNaves6.Y + 1450.0f * j;
            ANaveEnemiga* NaveEnemigaUwUActual6 = ANaveEnemigaFactory::FabricaNaves("UwU", World, ubicacionActual6, rotacionNave6);
            TANavesEnemigas.Add(NaveEnemigaUwUActual6);
        }
    }
}
void AFacadeNaves::CollideEnemyProjectile(AActor* OtherActor)
{
}
//***********************************************************************************************************************************************************
void AFacadeNaves::SpawnPowerUpVelocidad()
{
    // Genera una ubicación aleatoria para el PowerUpVelocidad
    FVector SpawnLocation = FVector(FMath::RandRange(-1300.0f, -1600.0f), FMath::RandRange(-1000.0f, 1000.0f), 1600.0f);
    FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

    // Spawnea un PowerUpVelocidad en la ubicación generada
    APowerUpVelocidad* PowerUpVelocidad = GetWorld()->SpawnActor<APowerUpVelocidad>(APowerUpVelocidad::StaticClass(), SpawnLocation, SpawnRotation);

    // Configura un temporizador para llamar a SpawnPowerUpVelocidad nuevamente después de 5 segundos
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AFacadeNaves::SpawnPowerUpVelocidad, 15.0f, false);

}

//***********************************************************************************************************************************************************



