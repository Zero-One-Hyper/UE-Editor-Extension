// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FBaseSerializedJsonObject;

class EDITORMODULE_API EditorJsonTool
{
public:
	EditorJsonTool();
	~EditorJsonTool();

public:
	static void SaveJsonObject(TSharedPtr<FBaseSerializedJsonObject> SerializedJsonObject, FString JsonName);
};

class FBaseSerializedJsonObject
{
public:
	FBaseSerializedJsonObject()
	{
	}

	virtual ~FBaseSerializedJsonObject()
	{
	}

	virtual void SerializeObject(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
	{
	};
};
