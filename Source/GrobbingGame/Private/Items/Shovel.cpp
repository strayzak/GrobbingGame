// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Shovel.h"
#include "GrobbingGame/GrobbingGameCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AShovel::AShovel()
{
	ShovelBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Shovel Box"));
	ShovelBox->SetupAttachment(GetRootComponent());
	ShovelBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ShovelBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	ShovelBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	BoxTraceStart->SetupAttachment(GetRootComponent());

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void AShovel::BeginPlay()
{
	Super::BeginPlay();

	ShovelBox->OnComponentBeginOverlap.AddDynamic(this, &AShovel::OnBoxOverlap);
}

void AShovel::PickUp(USceneComponent* InParent, FName InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}

void AShovel::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

}

void AShovel::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AShovel::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector Start = BoxTraceStart->GetComponentLocation();
	const FVector End = BoxTraceEnd->GetComponentLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult BoxHit;
	UKismetSystemLibrary::BoxTraceSingle(this, Start, End, FVector(5.f, 5.f, 5.f), BoxTraceStart->GetComponentRotation(), ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, BoxHit, true);
}
