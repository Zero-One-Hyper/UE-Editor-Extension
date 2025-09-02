// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class EDITORMODULE_API FEquipmentStyle
{
public:
	static void Initialize();

	static void Shutdown();

	/** reloads textures used by slate renderer */
	static void ReloadTextures();

	/** @return The Slate style set for the Shooter game */
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

private:
	static TSharedRef<FSlateStyleSet> Create();

private:
	static TSharedPtr<FSlateStyleSet> EquipmentStyleInstance;
};
