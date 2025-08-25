// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "MenuManager.generated.h"

class UMenuItem;
struct FMenuItemNode;

/**
 * EngineSubSystem是一种特殊的单例 当module被加载时Subsystem会自动创建并初始化
 * 此处将会写菜单栏扩展的核心代码
 */
DECLARE_LOG_CATEGORY_EXTERN(MenuManagerLog, Log, All);

UCLASS()
class EDITORMODULE_API UMenuManager : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

private:
	TArray<FMenuItemNode> RootNodeList; //根节点数组

protected:
	void AddMenuBarExtension(FMenuBarBuilder& MenuBarBuilder);
	void AddMenuItemToNodeList(UMenuItem* MenuItem); //根据MenuItemd的CDO构造树
};

struct FMenuItemNode
{
	FString NodeName;
	UMenuItem* MenuItem = nullptr; //用于叶子节点 存储各种衍圣类的CDO
	TArray<FMenuItemNode> Children; //用于父节点，存储子节点
};
