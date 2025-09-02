// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentCommands.h"

#define LOCTEXT_NAMESPACE "FEditorExtensionModule"

void FEquipmentCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Test", "Bring up Test window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
