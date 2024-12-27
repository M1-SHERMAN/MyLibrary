// Fill out your copyright notice in the Description page of Project Settings.


#include "UEBPAndCpp_Receiver_R.h"
#include "UEBPAndCpp_Sender.h"
#include "Kismet/GameplayStatics.h"

void AUEBPAndCpp_Receiver_R::BeginPlay()
{
	Super::BeginPlay();
	
	if(AUEBPAndCpp_Sender* Sender = Cast<AUEBPAndCpp_Sender>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		Sender->UEBPAndCpp_Broadcast.AddDynamic(this, &AUEBPAndCpp_Receiver_R::OnReceived);
	}
}

void AUEBPAndCpp_Receiver_R::OnReceived(int Value)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Received Value: %d"), Value));
	}
}
