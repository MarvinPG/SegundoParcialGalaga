
#include "CAInvisible.h"



UCAInvisible::UCAInvisible()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UCAInvisible::BeginPlay()
{
	Super::BeginPlay();


}



void UCAInvisible::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



}



