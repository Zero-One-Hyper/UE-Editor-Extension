// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MenuItem.generated.h"

/**
 * 所有自定义菜单的父类 后面使用TObjectIterator对象迭代器查找所有对象
 */
UCLASS()
class EDITORMODULE_API UMenuItem : public UObject
{
	GENERATED_BODY()

public:
	virtual ~UMenuItem() override
	{
	}

	virtual void OnMenuClick()
	{
	}

private:
	FString MenuPath; //路径 A/B/C
	FString MenuName; //名称
	FString MenuToolTip; //菜单提示

public:
	FString& GetMenuPath() { return MenuPath; }
	FString& GetMenuName() { return MenuName; }
	FString& GetMenuToolTip() { return MenuToolTip; }

protected:
	void InitMenu(const FString& Path, const FString& Tooltip);
};
