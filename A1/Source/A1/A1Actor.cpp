// Fill out your copyright notice in the Description page of Project Settings.


#include "A1Actor.h"
#include "A1Object.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AA1Actor::AA1Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	SetRootComponent(BodyMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshAsset(
		TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Statue.SM_Statue's"));

	if (BodyMeshAsset.Succeeded())
	{
		BodyMesh->SetStaticMesh(BodyMeshAsset.Object);
	}

}

// Called when the game starts or when spawned
void AA1Actor::BeginPlay()
{
	Super::BeginPlay();

	/*Obj = NewObject<UA1Object>();

	GEngine->ForceGarbageCollection(true);*/

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("A1Target"), OUT Actors);

	if (Actors.Num() > 0)
	{
		TargetActor = Actors[0];
	}
	
}

// Called every frame
void AA1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*FVector Location = GetActorLocation();
	FVector NewLocation = Location + FVector::ForwardVector * MovementSpeed * DeltaTime;
	SetActorLocation(NewLocation);*/

	if (TargetActor != nullptr)
	{
		FVector Direction = TargetActor->GetActorLocation() - GetActorLocation();

	
		AddActorWorldOffset(Direction.GetSafeNormal() * MovementSpeed * DeltaTime);
	}


	//FRotator Rotation = GetActorRotation();
	//FRotator NewRotation = FRotator(Rotation.Pitch, Rotation.Yaw * RotationRate * DeltaTime, Rotation.Roll);

	//SetActorRotation(NewRotation);

	AddActorWorldRotation(FRotator(0.0f, RotationRate* DeltaTime, 0.0f));


}

