// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBPandCpp_Receiver_Parent.h"

// Sets default values
AMyBPandCpp_Receiver_Parent::AMyBPandCpp_Receiver_Parent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	RootComponent = Cube;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	if(CubeMesh.Succeeded() && SphereMaterial.Succeeded())
	{
		Cube->SetStaticMesh(CubeMesh.Object);
		Cube->SetMaterial(0, SphereMaterial.Object);
	}
}

// Called when the game starts or when spawned
void AMyBPandCpp_Receiver_Parent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBPandCpp_Receiver_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

