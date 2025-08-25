// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuItem.h"

void UMenuItem::InitMenu(const FString& Path, const FString& Tooltip)
{
	MenuPath = Path;
	MenuToolTip = Tooltip;
	MenuName = FPaths::GetPathLeaf(Path); //截取路径拿到最后一个
}
