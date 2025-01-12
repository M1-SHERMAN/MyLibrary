// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SessionMenu.generated.h"

/**
 * 会话管理菜单Widget类
 * 提供创建和加入多人游戏会话的用户界面
 * 继承自UUserWidget以提供UI功能
 */

class UButton;

UCLASS()
class EASYSTEAMMULTIPLAYERSESSIONS_API USessionMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * 设置菜单并初始化会话管理系统
	 * @param InNumPublicConnections - 会话最大玩家数
	 * @param InMatchType - 匹配类型
	 * @param InPathToLobby - 大厅关卡的路径
	 */
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 InNumPublicConnections = 4, FString InMatchType = FString(TEXT("FreeForAll")), FString InPathToLobby = FString(TEXT("/Game/Maps/Lobby")));

protected:
	// UUserWidget接口实现
	virtual bool Initialize() override;		// 初始化UI组件
	virtual void NativeDestruct() override;	// 销毁UI组件，并清理资源

	// 会话操作的回调函数
	
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);
	
private:
	// UI组件：使用meta=(BindWidget)标记以自动绑定到蓝图中创建的对应名称的组件
	
	UPROPERTY(meta=(BindWidget))
	UButton* HostButton;
	
	UPROPERTY(meta=(BindWidget))
	UButton* JoinButton;

	/** 清理菜单并恢复游戏输入模式 */
	void MenuTearDown();

	// 按钮点击事件处理函数
	UFUNCTION()
	void HostButtonClicked();	// 处理创建会话按钮点击
	UFUNCTION()
	void JoinButtonClicked();	// 处理加入会话按钮点击

	// 会话管理系统引用
	class USteamMultiplayerSessionSubsystem* SteamMultiplayerSessionSubsystem;

	// 会话配置参数
	int32 NumPublicConnections{4};				// 最大连接数
	FString MatchType{TEXT("FreeForAll")};	// 匹配类型
	FString PathToLobby{TEXT("")};			// 大厅地图路径
};
