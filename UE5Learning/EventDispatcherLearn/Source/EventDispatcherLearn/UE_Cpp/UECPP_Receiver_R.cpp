// Fill out your copyright notice in the Description page of Project Settings.


#include "UECPP_Receiver_R.h"
#include "UECpp_Sender.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

void AUECPP_Receiver_R::BeginPlay()
{
	Super::BeginPlay();

	AUECpp_Sender* PlayerPawn = CastChecked<AUECpp_Sender>(UGameplayStatics::GetPlayerPawn(this, 0));
	// Bind the event
	// AddUObject Parameter: this -> the object that has the function, &AUECPP_Receiver_R::OnReceived -> the function
	PlayerPawn->UECpp_OnBroadcast.AddUObject(this, &AUECPP_Receiver_R::OnReceived);
}

void AUECPP_Receiver_R::OnReceived(int Value)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Red, FString::Printf(TEXT("Broadcasting: %d"), Value));
	}
}
