// Fill out your copyright notice in the Description page of Project Settings.


#include "SEquipmentSlateWidget.h"

#include "EditorJsonClasses.h"
#include "SlateOptMacros.h"
#include "Editor/EditorWidgets/Public/SAssetDropTarget.h"
#include "EditorJsonClasses.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SEquipmentSlateWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Test Button")) //FText支持本地化
			]
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Center)
			[
				SNew(SButton)
				.Text(FText::FromString("Click"))
				//.OnClicked(this, &SEquipmentSlateWidget::OnTestButtonClicked)
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Test Checkbox"))
			]
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Center)
			[
				SNew(SCheckBox) //一种跟踪用户何时选中和取消选中的控件机制
				.OnCheckStateChanged(
					this, &SEquipmentSlateWidget::OnTestCheckboxStateChange)
				.IsChecked(this, &SEquipmentSlateWidget::IsTestBoxChecked)
			]
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Center)
			[
				SNew(SButton)
				.OnClicked(this, &SEquipmentSlateWidget::OnClickSaveButton)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.Padding(0.0f, 0.0f, 0.0f, 0.0f)
					[
						SNew(SAssetDropTarget)
						.OnAssetsDropped(this, &SEquipmentSlateWidget::OnAssetsDropTarget)
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.Padding(0.0f, 0.0f, 2.0f, 0.0f)
							.AutoWidth()
							[
								SNew(STextBlock)
								.Text(FText::FromString("Test AssetDropTarget"))
							]
						]
					]
					//.OnDrag
				]
			]
		]
	];
}

void SEquipmentSlateWidget::OnAssetsDropTarget(const FDragDropEvent& dropEvent, TArrayView<FAssetData> datas)
{
	AActor* actor = Cast<AActor>(datas[0].GetAsset());
	if (!actor)
	{
		UE_LOG(LogTemp, Error, TEXT("转换失败"));
		return;
	}
	FString name = actor->GetActorLabel();
	UE_LOG(LogTemp, Display, TEXT("Label是：%s"), *name);
	ParentActor = actor;
}

FReply SEquipmentSlateWidget::OnClickSaveButton()
{
	if (ParentActor == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("父对象为空"));
		return FReply::Handled();;
	}
	TArray<AActor*> allActors;
	TArray<FVector> allLocations;
	ParentActor->GetAttachedActors(allActors, true);

	TSharedPtr<FFactoryEquipmentsDataList> DataList = MakeShared<FFactoryEquipmentsDataList>();

	for (AActor* singleActor : allActors)
	{
		FVector actorLocation = singleActor->GetActorLocation(); //绝对位置
		allLocations.Add(actorLocation);
		TSharedPtr<FFactoryEquipmentsDataList::FFactoryEquipmentsData> data = MakeShared<
			FFactoryEquipmentsDataList::FFactoryEquipmentsData>();
		FString ActorName;
		FString Left;
		singleActor->GetActorLabel().Split(TEXT("_"), &Left, &ActorName);
		data->Name = ActorName;
		data->Position = singleActor->GetActorLocation();
		DataList->AllFactoryEquipmentsDatas.Add(data);
	}
	EditorJsonTool::SaveJsonObject(DataList, TEXT("EquipmentsA"));
	UE_LOG(LogTemp, Display, TEXT("数组长度：%d"), allActors.Num());
	return FReply::Handled();
}

void SEquipmentSlateWidget::OnTestCheckboxStateChange(ECheckBoxState NewState)
{
	bIsTestBoxChecked = NewState == ECheckBoxState::Checked ? true : false;
}

ECheckBoxState SEquipmentSlateWidget::IsTestBoxChecked() const
{
	return bIsTestBoxChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
