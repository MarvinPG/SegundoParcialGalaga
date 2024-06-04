#include "Galaga_USFX_LAB02GameMode.h"
#include "Galaga_USFX_LAB02Pawn.h"
#include "Reloj.h"
#include "Publicador.h"
#include "TorreEifel.h"
#include "NaveEstado.h"
//****************************
#include "NaveEstrategica.h"
#include "EstrategiaEspiadora.h"
#include "EstrategiaAyudante.h"
#include "EstrategiaDisparadora.h"
//****************************
#include "FacadeNaves.h"
#include "Engine/World.h"
#include "Engine/Engine.h"


AGalaga_USFX_LAB02GameMode::AGalaga_USFX_LAB02GameMode()
{
    // set default pawn class to our character class

    PrimaryActorTick.bCanEverTick = true;

    DefaultPawnClass = AGalaga_USFX_LAB02Pawn::StaticClass();


    E_Reloj = 0.0f;
    bEstrategiasCambiadas = false;

}

void AGalaga_USFX_LAB02GameMode::BeginPlay()
{
    Super::BeginPlay();

    //************************************  FACADE    *********************************************
    FacadeNaves = GetWorld()->SpawnActor<AFacadeNaves>(AFacadeNaves::StaticClass());

    FacadeNaves->SPAWN_NAVES_ENEMIGAS();
    FacadeNaves->SpawnPowerUpVelocidad();
    //************************************  OBSERVER    *********************************************
    FVector ubicacionReloj = FVector(-1160.0f, -1220.0f, 150.0f);
    FVector ubicacionTorreEifel = FVector(-1200.0f, 1180.0f, 600.0f);
    FRotator rotacionReloj = FRotator(0.0f, 0.0f, 0.0f);
    FRotator rotacionTorreEifel = FRotator(60.0f, -40.0f, 0.0f);

    Reloj = GetWorld()->SpawnActor<AReloj>(ubicacionReloj, rotacionReloj);
    TorreEifel = GetWorld()->SpawnActor<ATorreEifel>(ubicacionTorreEifel, rotacionTorreEifel);

    Publicador = GetWorld()->SpawnActor<APublicador>(APublicador::StaticClass());
    TorreEifel->SetPublicador(Publicador);
    Publicador->SubscriptorReloj(Reloj); 

    //******************************************   STATE    *************************************************
    FVector ubicacionNaveEstado = FVector(-1570.0f, 0.0f, 200.0f);
    FRotator rotacionNaveEstado = FRotator(0.0f, 0.0f, 0.0f);

    NaveEstado = GetWorld()->SpawnActor<ANaveEstado>(ubicacionNaveEstado, rotacionNaveEstado);

    //*******************************************  STRATERGY  ***********************************************

    UE_LOG(LogTemp, Warning, TEXT("Begin called"));


    FVector ubicacionE = FVector(1600.0f, -900.0f, 850.0f);
    FRotator rotacionE = FRotator(0.0f, 180.0f, 0.0f);

    // NAVE PADRIZA EXISTE
    Estrategica = GetWorld()->SpawnActor<ANaveEstrategica>(ubicacionE, rotacionE);

    //ESTRATEGIAS LAS INSTANCIAMOS
    E_Espiadora = GetWorld()->SpawnActor<AEstrategiaEspiadora>(AEstrategiaEspiadora::StaticClass());
    E_Ayudante = GetWorld()->SpawnActor<AEstrategiaAyudante>(AEstrategiaAyudante::StaticClass());
    E_Disparadora = GetWorld()->SpawnActor<AEstrategiaDisparadora>(AEstrategiaDisparadora::StaticClass());

    GetWorldTimerManager().SetTimer(TimerHandle_Reloj, this, &AGalaga_USFX_LAB02GameMode::TickReloj, 1.0f, true);

}


void AGalaga_USFX_LAB02GameMode::TickReloj()
{
    E_Reloj += 1;

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("RELOJ PADRIZA MARCA: %d"), E_Reloj));
    }

    // Agrega aquí la lógica para cambiar las estrategias basándote en el valor de E_Reloj
    if (!bEstrategiasCambiadas)
    {
        if (E_Reloj <= 5.0)
        {
            Estrategica->AlterarEstrategia(E_Espiadora);
            Estrategica->EmplearEstrategia(DeltaTime);
        }
        if (E_Reloj > 5.0 && E_Reloj < 15.0)
        {
            Estrategica->AlterarEstrategia(E_Ayudante);
            Estrategica->EmplearEstrategia(DeltaTime);
        }
        if (E_Reloj > 15.0 && E_Reloj < 25.0)
        {
            Estrategica->AlterarEstrategia(E_Disparadora);
            Estrategica->EmplearEstrategia(DeltaTime);

        }
        if (E_Reloj >= 25.0)
        {
            E_Reloj = 0.0;
            bEstrategiasCambiadas = true; // Marcamos que las estrategias ya han sido cambiadas
        }
    }
}


