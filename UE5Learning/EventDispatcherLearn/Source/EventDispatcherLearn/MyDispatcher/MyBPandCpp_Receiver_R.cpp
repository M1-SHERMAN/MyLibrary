// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBPandCpp_Receiver_R.h"

#include "MyData.h"
#include "MyEventManager.h"

#include "Engine/Engine.h"

void AMyBPandCpp_Receiver_R::BeginPlay()
{
	Super::BeginPlay();

	UMyEventManager::AddEventListener("MyBPAndCpp_DispatchEvent", this);
}

void AMyBPandCpp_Receiver_R::BeginDestroy()
{
	// Have to Remove the listener when the object is destroyed
	// Otherwise, the listener will still be in the ListenerList and DispatchEvent will try to call the listener's OnReceiveEvent function
	UMyEventManager::RemoveEventListener("MyBPAndCpp_DispatchEvent", this);

	Super::BeginDestroy();
}

void AMyBPandCpp_Receiver_R::OnReceiveEvent_Implementation(UObject* Data)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Received value: %d"), Cast<UMyData>(Data)->Param));
	}
}

