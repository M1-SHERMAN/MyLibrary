// Fill out your copyright notice in the Description page of Project Settings.


#include "UECPP_Receiver_G.h"
#include "UECpp_Sender.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

void AUECPP_Receiver_G::BeginPlay()
{
	Super::BeginPlay();

	AUECpp_Sender* PlayerPawn = CastChecked<AUECpp_Sender>(UGameplayStatics::GetPlayerPawn(this, 0));
	// Bind the event
	// AddUObject Parameter: this -> the object that has the function, &AUECPP_Receiver_R::OnReceived -> the function
	const FDelegateHandle DelegateHandle = PlayerPawn->UECpp_OnBroadcast.AddUObject(this, &AUECPP_Receiver_G::OnReceived); // Need to store the DelegateHandle to remove the event later

	FTimerHandle TimerHandle;
	// Inside the [] is the capture list, means what variables you want to use inside the lambda function
	auto Lambda = [PlayerPawn, DelegateHandle]()
	{
		PlayerPawn->UECpp_OnBroadcast.Remove(DelegateHandle);// Remove the event
		// PlayerPawn->UECpp_OnBroadcast.RemoveAll(this); // Remove all events that are bound to this object
	};
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda(Lambda), 5.f, false);
	
}

void AUECPP_Receiver_G::OnReceived(int Value)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Green, FString::Printf(TEXT("Broadcasting: %d"), Value));
	}
}