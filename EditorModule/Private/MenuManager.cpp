// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuManager.h"

#include "LevelEditor.h"
#include "MenuItem.h"

DEFINE_LOG_CATEGORY(MenuManagerLog);

void UMenuManager::Initialize(FSubsystemCollectionBase& Collection)
{
	//TObjectIterator对象迭代器 把T带入UClass就可以查找所有UClass
	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* CurrentClass = *It;
		if (CurrentClass->IsChildOf(UMenuItem::StaticClass()) &&
			!(CurrentClass->HasAnyClassFlags(CLASS_Abstract)))
		{
			AddMenuItemToNodeList(Cast<UMenuItem>(CurrentClass->GetDefaultObject()));
		}
	}

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuBarExtension("Help",
		                                  EExtensionHook::After,
		                                  nullptr,
		                                  FMenuBarExtensionDelegate::CreateUObject(
			                                  //不是创建一个UObject而是通过Uobject类的某个方法创建一个委托
			                                  this, &UMenuManager::AddMenuBarExtension)); //FMenuBarBuilder&
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
}

void UMenuManager::Deinitialize()
{
}

static void AddMenuExtension(FMenuBuilder& Builder, TArray<FMenuItemNode>* NodeList)
{
	for (int i = 0; i < NodeList->Num(); i++)
	{
		FMenuItemNode& Node = (*NodeList)[i];
		if (Node.MenuItem != nullptr)
		{
			//有MenuItem，说明是叶子节点
			Builder.AddMenuEntry(FText::FromString(Node.MenuItem->GetMenuName()),
			                     FText::FromString(Node.MenuItem->GetMenuToolTip()),
			                     FSlateIcon(),
			                     FUIAction(FExecuteAction::CreateUObject(Node.MenuItem, &UMenuItem::OnMenuClick)));
		}
		else if (!Node.NodeName.IsEmpty() && Node.Children.Num() > 0) //没有说明是父节点，递归调用自己
		{
			Builder.AddSubMenu(FText::FromString(Node.NodeName),
			                   FText::FromString(TEXT("")),
			                   FNewMenuDelegate::CreateStatic(&AddMenuExtension, &Node.Children));
		}
	}
}

void UMenuManager::AddMenuBarExtension(FMenuBarBuilder& MenuBarBuilder)
{
	for (FMenuItemNode& Node : RootNodeList)
	{
		if (!Node.NodeName.IsEmpty() && Node.Children.Num() > 0)
		{
			MenuBarBuilder.AddPullDownMenu(FText::FromString(Node.NodeName),
			                               FText::FromString(TEXT("")),
			                               FNewMenuDelegate::CreateStatic(&AddMenuExtension, &Node.Children));
		}
	}
}

static FMenuItemNode* FindMenuItemNode(TArray<FMenuItemNode>& MenuNodes, const FString& MenuName)
{
	for (FMenuItemNode& Node : MenuNodes)
	{
		if (Node.NodeName == MenuName)
		{
			return &Node;
		}
	}
	return nullptr;
}

void UMenuManager::AddMenuItemToNodeList(UMenuItem* MenuItem)
{
	if (MenuItem == nullptr)
	{
		return;
	}
	//将路径ABCD分解，按顺序存储数组
	TArray<FString> MenuNames;
	FString Path = MenuItem->GetMenuPath();
	if (Path.IsEmpty())
	{
		return;
	}
	FString Left;
	while (Path.Split("/", &Left, &Path))
	{
		if (Left.IsEmpty())
		{
			continue;
		}
		//添加中间节点
		MenuNames.Add(Left);
	}
	//添加最后的节点
	MenuNames.Add(Path);
	//查找根节点，没有则创建
	FMenuItemNode* RootMenuNode = FindMenuItemNode(RootNodeList, MenuNames[0]);
	if (RootMenuNode == nullptr)
	{
		FMenuItemNode MenuItemNode;
		MenuItemNode.NodeName = MenuNames[0];
		int32 Index = RootNodeList.Add(MenuItemNode);
		RootMenuNode = &RootNodeList[Index];
	}
	//循环查找字符串，没有就创建节点
	FMenuItemNode* ParentNode = RootMenuNode;
	for (int i = 1; i < MenuNames.Num(); ++i)
	{
		FString& ChildName = MenuNames[i];
		FMenuItemNode* ChildNode = FindMenuItemNode(RootNodeList, ChildName);
		if (ChildNode == nullptr)
		{
			FMenuItemNode MenuItemNode;
			MenuItemNode.NodeName = ChildName;
			int32 Index = ParentNode->Children.Add(MenuItemNode);
			ChildNode = &ParentNode->Children[Index];
		}
		ParentNode = ChildNode;
	}
	//最后给叶子节点赋值MenuItem指针
	ParentNode->MenuItem = MenuItem;
}
