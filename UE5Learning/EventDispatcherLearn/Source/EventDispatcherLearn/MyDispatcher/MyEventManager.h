// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyEventManager.generated.h"

/**
 * 
 */
UCLASS()
class EVENTDISPATCHERLEARN_API UMyEventManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
private:
	// FString : EventName(Uniquely identifies the event)
	// TArray<UObject*> : ListenerList(Contains the listeners for the event)
	static TMap<FString, TArray<UObject*>> ListenerList;
public:
	UFUNCTION(BlueprintCallable, Category="EventDispatcher Utility")
	static void AddEventListener(FString EventName, UObject* Listener);

	UFUNCTION(BlueprintCallable, Category="EventDispatcher Utility")
	static void RemoveEventListener(FString EventName, UObject* Listener);

	UFUNCTION(BlueprintCallable, Category="EventDispatcher Utility")
	static FString DispatchEvent(FString EventName, UObject* Data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="EventDispatcher Utility")
	static UObject* CreateNewData(UClass* ClassType);
};
