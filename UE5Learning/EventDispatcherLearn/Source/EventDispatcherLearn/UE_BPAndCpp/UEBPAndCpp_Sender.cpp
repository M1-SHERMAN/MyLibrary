// Fill out your copyright notice in the Description page of Project Settings.


#include "UEBPAndCpp_Sender.h"

// Sets default values
AUEBPAndCpp_Sender::AUEBPAndCpp_Sender()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	RootComponent = Sphere;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	if(SphereMesh.Succeeded() && SphereMaterial.Succeeded())
	{
		Sphere->SetStaticMesh(SphereMesh.Object);
		Sphere->SetMaterial(0, SphereMaterial.Object);
	}

	
}

// Called when the game starts or when spawned
void AUEBPAndCpp_Sender::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	auto Lambda = [](const FUEBPAndCpp_BroadcastDelegate* Ubcb)
	{
		Ubcb->Broadcast(FMath::RandRange(0, 100));
	};
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda(Lambda, &UEBPAndCpp_Broadcast), 1.0f, true);
	
}

// Called every frame
void AUEBPAndCpp_Sender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUEBPAndCpp_Sender::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

