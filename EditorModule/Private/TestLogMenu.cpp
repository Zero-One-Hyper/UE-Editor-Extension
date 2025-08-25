// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLogMenu.h"

UTestLogMenu::UTestLogMenu()
{
	//在构造函数中初始化菜单  路径     ToolTip
	InitMenu("CustomTools/First/Second/Final", "TestLogMenu ToolTip");
}

void UTestLogMenu::OnMenuClick()
{
	UE_LOG(LogTemp, Error, TEXT("OnMenuClick"));
}
