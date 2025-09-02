// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWindowItem.h"

#include "EquipmentCommands.h"
#include "MenuManager.h"
#include "SEquipmentSlateWidget.h"

UEquipmentWindowItem::UEquipmentWindowItem()
{
	InitMenu("CustomTool/OpenEquipmentMenu", "EquipMent");
}

static const FName TestTabName("Test");

#define LOCTEXT_NAMESPACE "FTestModule"

void UEquipmentWindowItem::OnMenuClick()
{
	UE_LOG(MenuManagerLog, Warning, TEXT("OnMenuClick"));
	//注册Tab页面生成器
	FGlobalTabmanager::Get()->RegisterTabSpawner(FName("EquipmentWindowItem"), FOnSpawnTab::CreateLambda(
		                                             [](const FSpawnTabArgs args)
		                                             {
			                                             return SNew(SDockTab)
				                                             .TabRole(ETabRole::PanelTab)
				                                             [
					                                             SNew(SBox)
					                                             .HAlign(HAlign_Left)
					                                             .VAlign(VAlign_Center)
					                                             [
						                                             SNew(SEquipmentSlateWidget)
					                                             ]
				                                             ];
		                                             }));
	FGlobalTabmanager::Get()->TryInvokeTab(FTabId("EquipmentWindowItem")); //尝试激活Tab页面
	/*
		FEquipmentStyle::Initialize();
		FEquipmentStyle::ReloadTextures();
	
		FEquipmentCommands::Register();
	
		PluginCommands = MakeShareable(new FUICommandList);
	
		PluginCommands->MapAction(
			FEquipmentCommands::Get().OpenPluginWindow,
			FExecuteAction::CreateRaw(this, &UEquipmentWindowItem::PluginButtonClicked),
			FCanExecuteAction());
	
		UToolMenus::RegisterStartupCallback(
			FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &UEquipmentWindowItem::RegisterMenus));
	
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TestTabName,
		                                                  FOnSpawnTab::CreateRaw(
			                                                  this, &UEquipmentWindowItem::OnSpawnPluginTab))
		                        .SetDisplayName(LOCTEXT("FTestTabTitle", "Test"))
		                        .SetMenuType(ETabSpawnerMenuType::Hidden);
		*/
}

UEquipmentWindowItem::~UEquipmentWindowItem()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	/*
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FEquipmentStyle::Shutdown();

	FEquipmentCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TestTabName);
	*/
}

TSharedRef<SDockTab> UEquipmentWindowItem::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FTestModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("Test.cpp"))
	);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void UEquipmentWindowItem::PluginButtonClicked()
{
	//FGlobalTabmanager::Get()->TryInvokeTab(TestTabName);
}

void UEquipmentWindowItem::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	/*
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FEquipmentCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(
					FToolMenuEntry::InitToolBarButton(FEquipmentCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
	*/
}

#undef LOCTEXT_NAMESPACE
