// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "SteamMultiplayerSessionSubsystem.generated.h"

/**
 *	Steam多人会话子系统
 *	用于处理在线多人游戏中的会话(Session)相关功能，包括创建、查找、加入、销毁和启动会话。
 *	继承自UGameInstanceSubsystem，因为会话管理需要在整个游戏生命周期中持续存在。
 */

// 声明委托用于对外广播会话操作的结果

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FMultiPlayerOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroySessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionComplete, bool, bWasSuccessful);

UCLASS()
class EASYSTEAMMULTIPLAYERSESSIONS_API USteamMultiplayerSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USteamMultiplayerSessionSubsystem();
	
	// 提供给外部调用的主要方法：
	/**
	 * 创建一个新的多人游戏会话
	 * @param NumPublicConnections - 最大允许的公开连接数（玩家数）
	 * @param MatchType - 匹配类型，用于过滤和查找特定类型的会话
	 */
	void CreateSession(int32 NumPublicConnections, FString MatchType);

	/**
	 * 查找现有的多人游戏会话
	 * @param MaxSearchResult - 最大搜索结果数量
	 */
	void FindSessions(int32 MaxSearchResult);

	/**
	 * 加入一个现有的多人游戏会话
	 * @param SearchResult - 要加入的会话搜索结果
	 */
	void JoinSession(const FOnlineSessionSearchResult& SearchResult);

	/** 销毁当前的多人游戏会话 */
	void DestroySession();

	/** 启动会话，通常在所有玩家准备就绪后调用 */
	void StartSession();

	//	供外部注册的委托，用于接收会话操作的结果

	FMultiplayerOnCreateSessionComplete MultiplayerOnCreateSessionComplete;
	FMultiplayerOnFindSessionsComplete MultiplayerOnFindSessionsComplete;
	FMultiPlayerOnJoinSessionComplete MultiPlayerOnJoinSessionComplete;
	FMultiplayerOnDestroySessionComplete MultiplayerOnDestroySessionComplete;
	FMultiplayerOnStartSessionComplete MultiplayerOnStartSessionComplete;
	
protected:
	// 内部回调函数，处理会话操作的完成事件
	
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	
private:
	// 核心接口和数据成员
	IOnlineSessionPtr SessionInterface;						// 在线会话接口指针
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;	// 最近的会话设置
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;		// 最近的会话搜索
	
	// 委托和句柄对
	// Delegate: 用于注册回调函数
	// Handle: 用于之后取消注册，避免内存泄漏
	
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;
	
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;

	// 用于处理销毁后重建会话的成员变量
	bool bCreateSessionOnDestroy{ false };	// 标记是否需要在销毁后重建会话
	int32 LastNumPublicConnections;			// 存储重建会话需要的连接数
	FString LastMatchType;					// 存储重建会话需要的匹配类型
};
