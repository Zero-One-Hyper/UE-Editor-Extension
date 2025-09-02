// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLogMenu.h"

#include "MenuManager.h"

UTestLogMenu::UTestLogMenu()
{
	InitMenu("CustomTool/Test", "Test Editor Extension");
}


void UTestLogMenu::OnMenuClick()
{
	UE_LOG(MenuManagerLog, Warning, TEXT("测试编辑器扩展模块点击"));
}
