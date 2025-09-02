// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentStyle.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/SlateStyleRegistry.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FEquipmentStyle::EquipmentStyleInstance = nullptr;

void FEquipmentStyle::Initialize()
{
	/*
	if (!EquipmentStyleInstance.IsValid())
	{
		EquipmentStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*EquipmentStyleInstance);
	}
	*/
}

void FEquipmentStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*EquipmentStyleInstance);
	ensure(EquipmentStyleInstance.IsUnique());
	EquipmentStyleInstance.Reset();
}

FName FEquipmentStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("TestStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef<FSlateStyleSet> FEquipmentStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("TestStyle"));
	/*
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("Test")->GetBaseDir() / TEXT("Resources"));

	Style->Set("Test.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	*/
	return Style;
}

void FEquipmentStyle::ReloadTextures()
{
	/*
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
	*/
}

const ISlateStyle& FEquipmentStyle::Get()
{
	return *EquipmentStyleInstance;
}
