// Fill out your copyright notice in the Description page of Project Settings.


#include "UECpp_Sender.h"

// Sets default values
AUECpp_Sender::AUECpp_Sender()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	RootComponent = Sphere;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	if(StaticMeshAsset.Succeeded() && MaterialAsset.Succeeded())
	{
		Sphere->SetStaticMesh(StaticMeshAsset.Object);
		Sphere->SetMaterial(0, MaterialAsset.Object);
	}
}

// Called when the game starts or when spawned
void AUECpp_Sender::BeginPlay()
{
	Super::BeginPlay();
	
	// This lambda function is used to broadcast the event by a timer
	// The parameter type (inside the ()) needs to be the same as the delegate instance
	auto Lambda = [](const FUECpp_BroadcastDeletegate* Ucb)
	{
		// Means "Call XXX Dispatcher" in Blueprint
		// Inside the () is the parameter you want to pass
		Ucb->Broadcast(FMath::RandRange(0, 100));
	};
	
	FTimerHandle TimerHandle;
	// Parameters of CreateLambda: Lambda -> the lambda function, &UECpp_OnBroadcast -> the delegate instance
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda(Lambda, &UECpp_OnBroadcast), 1.f, true);


	
}

// Called every frame
void AUECpp_Sender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUECpp_Sender::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

