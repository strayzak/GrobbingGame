// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Coffin.h"
#include "Items/Item.h"
#include "Components/CapsuleComponent.h"
#include "Items/GraveTrinkets.h"

// Sets default values
ACoffin::ACoffin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(GetRootComponent());
	Capsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void ACoffin::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if(World && GraveTrinketsClasses.Num() > 0)
	{
		FVector Location = GetActorLocation();
		Location.Z += 75.f;

		const int32 Selection = FMath::RandRange(0, GraveTrinketsClasses.Num() - 1);
		World->SpawnActor<AGraveTrinkets>(GraveTrinketsClasses[Selection], Location, GetActorRotation());
	}
}

// Called every frame
void ACoffin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

