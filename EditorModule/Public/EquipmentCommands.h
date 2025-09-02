// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentStyle.h"

/**
 * 
 */
class EDITORMODULE_API FEquipmentCommands : public TCommands<FEquipmentCommands>
{
public:
	FEquipmentCommands(): TCommands<FEquipmentCommands>(TEXT("Test"), NSLOCTEXT("Contexts", "Test", "Test Plugin"),
	                                                    NAME_None, FEquipmentStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> OpenPluginWindow;
};
