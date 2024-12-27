// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UECpp_Sender.generated.h"

UCLASS()
class EVENTDISPATCHERLEARN_API AUECpp_Sender : public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Sphere;

	// OneParam means that the delegate has one parameter
	// FUECpp_BroadcastDeletegate is the delegate type
	// int is the parameter type
	DECLARE_MULTICAST_DELEGATE_OneParam(FUECpp_BroadcastDeletegate, int)
	// The delegate instance
	FUECpp_BroadcastDeletegate UECpp_OnBroadcast;	
	
public:
	// Sets default values for this pawn's properties
	AUECpp_Sender();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
