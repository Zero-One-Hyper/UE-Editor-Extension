// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class EDITORMODULE_API SEquipmentSlateWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SEquipmentSlateWidget)
			: _bIsTestBoxChecked(false)
		{
		}

		SLATE_ARGUMENT(bool, bIsTestBoxChecked)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

public:
	FReply OnClickSaveButton();

	void OnTestCheckboxStateChange(ECheckBoxState NewState);
	ECheckBoxState IsTestBoxChecked() const;

private:
	void OnAssetsDropTarget(const FDragDropEvent& dropEvent, TArrayView<FAssetData> datas);

protected:
	bool bIsTestBoxChecked;
	AActor* ParentActor;
};
