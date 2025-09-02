// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorJsonTool.h"
/**
 * 
 */
class EDITORMODULE_API EditorJsonClasses
{
public:
	EditorJsonClasses()
	{
	};

	~EditorJsonClasses()
	{
	};
};

class FFactoryEquipmentsDataList : public FBaseSerializedJsonObject
{
public:
	FFactoryEquipmentsDataList()
	{
	}

	~FFactoryEquipmentsDataList()
	{
	}

	class FFactoryEquipmentsData : public FBaseSerializedJsonObject
	{
	public:
		FFactoryEquipmentsData()
		{
		}

		~FFactoryEquipmentsData()
		{
		}

		FVector Position;
		FString Name;
		FVector Rotation;
		float ArmLength;

		virtual void SerializeObject(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	};

	TArray<TSharedPtr<FFactoryEquipmentsData>> AllFactoryEquipmentsDatas;

	virtual void SerializeObject(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
};
