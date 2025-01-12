// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionMenu.h"

#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "SteamMultiplayerSessionSubsystem.h"
#include "OnlineSubsystem.h"

void USessionMenu::MenuSetup(int32 InNumPublicConnections, FString InMatchType, FString InPathToLobby)
{
	NumPublicConnections = InNumPublicConnections;
	MatchType = InMatchType;
	PathToLobby = FString::Printf(TEXT("%s?listen"), *InPathToLobby) ;
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);
	
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PC = World->GetFirstPlayerController())
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			
			PC->SetInputMode(InputModeData);
			PC->SetShowMouseCursor(true);
		}
	}
	
	if (const UGameInstance* GameInstance = GetGameInstance())
	{
		SteamMultiplayerSessionSubsystem = GameInstance->GetSubsystem<USteamMultiplayerSessionSubsystem>();
	}

	if (SteamMultiplayerSessionSubsystem)
	{
		SteamMultiplayerSessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		SteamMultiplayerSessionSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
		SteamMultiplayerSessionSubsystem->MultiPlayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
		SteamMultiplayerSessionSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
		SteamMultiplayerSessionSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSession);
	}
}

bool USessionMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &USessionMenu::HostButtonClicked);
	}

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &USessionMenu::JoinButtonClicked);
	}

	return true;
}

void USessionMenu::NativeDestruct()
{
	MenuTearDown();
	Super::NativeDestruct();
}

void USessionMenu::OnCreateSession(bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		HostButton->SetIsEnabled(true);
		return;
	}
	
	if (UWorld* World= GetWorld())
	{
		World->ServerTravel(PathToLobby);
	}
}

void USessionMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	if (SteamMultiplayerSessionSubsystem == nullptr)
	{
		return;
	}

	for (auto Result : SessionResults)
	{
		FString SettingsValue;
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
		
		Result.Session.SessionSettings.bUseLobbiesIfAvailable = true;
		Result.Session.SessionSettings.bUsesPresence = true;

		if (SettingsValue == MatchType)
		{
			SteamMultiplayerSessionSubsystem->JoinSession(Result);
			return;
		}
		
	}
	if (!bWasSuccessful || SessionResults.Num() == 0)
	{
		JoinButton->SetIsEnabled(true);
	}
}

void USessionMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FString Address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);
			
			if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
			{
				PC->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
	}

	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		JoinButton->SetIsEnabled(true);
	}
}

void USessionMenu::OnDestroySession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		HostButton->SetIsEnabled(true);
	}
}

void USessionMenu::OnStartSession(bool bWasSuccessful)
{
}

void USessionMenu::MenuTearDown()
{
	RemoveFromParent();
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PC = World->GetFirstPlayerController())
		{
			FInputModeGameOnly InputModeData;
			PC->SetInputMode(InputModeData);
			PC->SetShowMouseCursor(false);
		}
	}
}

void USessionMenu::HostButtonClicked()
{
	HostButton->SetIsEnabled(false);
	
	if (SteamMultiplayerSessionSubsystem)
	{
		SteamMultiplayerSessionSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
}

void USessionMenu::JoinButtonClicked()
{
	JoinButton->SetIsEnabled(false);
	
	if (SteamMultiplayerSessionSubsystem)
	{
		SteamMultiplayerSessionSubsystem->FindSessions(10000);
	}
}
