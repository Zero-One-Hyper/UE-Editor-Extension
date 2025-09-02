// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuItem.h"
#include "EquipmentWindowItem.generated.h"

/**
 * 
 */
UCLASS()
class EDITORMODULE_API UEquipmentWindowItem : public UMenuItem
{
	GENERATED_BODY()
	UEquipmentWindowItem();

public :
	~UEquipmentWindowItem() override;

	virtual void OnMenuClick() override;

	void PluginButtonClicked();

private:
	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
